#include <ESP32Servo.h>

Servo myservo;

const int ENA = 32;
const int IN1 = 33;
const int IN2 = 25;
const int ENB = 14;
const int IN3 = 27;
const int IN4 = 26;
const int SERVO_PIN = 5;
const int CH1_PIN = 13;
const int CH2_PIN = 12;
const int BATT_PIN = 36;

const float DIV_RATIO = 4.0f;
const float ADC_REF = 3.3f;
const int ADC_BITS = 12;
const int ADC_MAX = (1 << ADC_BITS) - 1;

float battVoltage = 0.0f;
float battPct = 0.0f;

const int SERVO_CENTER = 130;
const int SERVO_MIN_DEG = -35;
const int SERVO_MAX_DEG = 35;
const int SERVO_MIN_POS = 80;
const int SERVO_MAX_POS = 180;

const int RC_MIN_US = 1000;
const int RC_MID_US = 1500;
const int RC_MAX_US = 2000;
const int RC_VALID_MIN = 900;
const int RC_VALID_MAX = 2200;
const int RC_DEADZONE_US = 30;

const int PWM_MAX = 255;
const int PWM_MIN_EFFECTIVE = 50;
const float MAX_FWD_KMH = 4.0f;
const float MAX_REV_KMH = 4.0f;

const unsigned long RC_SIGNAL_TIMEOUT_MS = 150;
unsigned long lastValidRcMs = 0;

int rc1Us = 0;
int rc2Us = 0;
int dbgSteeringDeg = 0;
float dbgSpeedKmh = 0.0f;

float serialSpeedKmh = 0.0f;
float serialSteeringDeg = 0.0f;
bool serialCommandValid = false;

enum ControlSource {
  SOURCE_NONE,
  SOURCE_RC,
  SOURCE_SERIAL
};

ControlSource activeSource = SOURCE_NONE;

const int PWM_FREQ = 1000;
const int PWM_RES_BITS = 8;

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO_PIN, 500, 2500);
  pinMode(BATT_PIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(CH1_PIN, INPUT);
  pinMode(CH2_PIN, INPUT);
  ledcAttach(ENA, PWM_FREQ, PWM_RES_BITS);
  ledcAttach(ENB, PWM_FREQ, PWM_RES_BITS);
  stopMotors();
  setSteeringDeg(0);
  Serial.println("Ready.");
  Serial.println("Serial format: [speed=1.5, steering=30]");
}

void loop() {
  readSerialCommands();

  bool rcAvailable = readAndApplyRCIfValid();

  if (rcAvailable) {
    activeSource = SOURCE_RC;
  } else if (serialCommandValid) {
    activeSource = SOURCE_SERIAL;
    applySerialControl();
  } else {
    activeSource = SOURCE_NONE;
    stopMotors();
  }

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 250) {
    printStatus();
    lastPrint = millis();
  }

  static unsigned long lastBattRead = 0;
  if (millis() - lastBattRead > 1000) {
    battVoltage = readBatteryVoltage();
    battPct = batteryVoltageToPercent(battVoltage);
    lastBattRead = millis();
  }

  delay(10);
}

bool readAndApplyRCIfValid() {
  unsigned long ch1_raw = pulseIn(CH1_PIN, HIGH, 25000);
  unsigned long ch2_raw = pulseIn(CH2_PIN, HIGH, 25000);

  bool ch1Valid = (ch1_raw >= RC_VALID_MIN && ch1_raw <= RC_VALID_MAX);
  bool ch2Valid = (ch2_raw >= RC_VALID_MIN && ch2_raw <= RC_VALID_MAX);

  if (!ch1Valid || !ch2Valid) {
    if (millis() - lastValidRcMs > RC_SIGNAL_TIMEOUT_MS) {
      return false;
    }
    return false;
  }

  lastValidRcMs = millis();
  rc1Us = (int)ch1_raw;
  rc2Us = (int)ch2_raw;
  int steeringDeg = rcPulseToSteeringDeg((int)ch1_raw);
  dbgSteeringDeg = steeringDeg;
  float speedKmh = rcPulseToSpeedKmh((int)ch2_raw);
  dbgSpeedKmh = speedKmh;
  setSteeringDeg(steeringDeg);
  setVehicleSpeedKmh(speedKmh);
  return true;
}

void applySerialControl() {
  dbgSteeringDeg = (int)serialSteeringDeg;
  dbgSpeedKmh = serialSpeedKmh;
  setSteeringDeg((int)serialSteeringDeg);
  setVehicleSpeedKmh(serialSpeedKmh);
}

int rcPulseToSteeringDeg(int pulseUs) {
  int delta = pulseUs - RC_MID_US;
  if (abs(delta) <= RC_DEADZONE_US) return 0;
  int steering = map(pulseUs, RC_MIN_US, RC_MAX_US, SERVO_MIN_DEG, SERVO_MAX_DEG);
  return constrain(steering, SERVO_MIN_DEG, SERVO_MAX_DEG);
}

float rcPulseToSpeedKmh(int pulseUs) {
  int delta = pulseUs - RC_MID_US;
  if (abs(delta) <= RC_DEADZONE_US) return 0.0f;

  if (pulseUs > RC_MID_US) {
    float norm = (pulseUs - RC_MID_US) / float(RC_MAX_US - RC_MID_US);
    return norm * MAX_FWD_KMH;
  } else {
    float norm = (RC_MID_US - pulseUs) / float(RC_MID_US - RC_MIN_US);
    return -(norm * MAX_REV_KMH);
  }
}

void readSerialCommands() {
  static String input = "";

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      if (input.length() > 0) {
        parseSerialCommand(input);
        input = "";
      }
    } else {
      if ((unsigned char)c >= 32 && (unsigned char)c <= 126) {
        input += c;
      }
      if (input.length() > 120) {
        input = "";
        Serial.println("ERR: command too long");
      }
    }
  }
}

void parseSerialCommand(String cmd) {
  cmd.trim();

  if (!cmd.startsWith("[") || !cmd.endsWith("]")) {
    Serial.println("ERR: expected [speed=..., steering=...]");
    return;
  }

  cmd.remove(0, 1);
  cmd.remove(cmd.length() - 1);
  cmd.replace(" ", "");

  int speedIdx = cmd.indexOf("speed=");
  int steerIdx = cmd.indexOf("steering=");

  if (speedIdx == -1 || steerIdx == -1) {
    Serial.println("ERR: missing speed or steering");
    return;
  }

  float speedVal = 0.0f;
  float steeringVal = 0.0f;
  int commaIdx = cmd.indexOf(',');

  if (commaIdx == -1) {
    Serial.println("ERR: missing comma");
    return;
  }

  if (speedIdx < steerIdx) {
    String speedStr = cmd.substring(speedIdx + 6, commaIdx);
    String steerStr = cmd.substring(steerIdx + 9);
    speedVal = speedStr.toFloat();
    steeringVal = steerStr.toFloat();
  } else {
    String steerStr = cmd.substring(steerIdx + 9, commaIdx);
    String speedStr = cmd.substring(speedIdx + 6);
    speedVal = speedStr.toFloat();
    steeringVal = steerStr.toFloat();
  }

  steeringVal = constrain(steeringVal, SERVO_MIN_DEG, SERVO_MAX_DEG);
  speedVal = constrain(speedVal, -MAX_REV_KMH, MAX_FWD_KMH);

  serialSpeedKmh = speedVal;
  serialSteeringDeg = steeringVal;
  serialCommandValid = true;

  Serial.printf("OK: serial command accepted -> speed=%.2f km/h steer=%.1f deg\n",
                serialSpeedKmh, serialSteeringDeg);
}

float readBatteryVoltage() {
  int raw = analogRead(BATT_PIN);
  float v_adc = raw * (ADC_REF / ADC_MAX);
  return v_adc * DIV_RATIO;
}

float batteryVoltageToPercent(float v) {
  const float V_FULL = 12.6f;
  const float V_EMPTY = 9.0f;
  float pct = 100.0f * (v - V_EMPTY) / (V_FULL - V_EMPTY);
  return constrain(pct, 0.0f, 100.0f);
}

void setSteeringDeg(int steeringDeg) {
  steeringDeg = constrain(steeringDeg, SERVO_MIN_DEG, SERVO_MAX_DEG);
  int servoPos = map(steeringDeg, SERVO_MIN_DEG, SERVO_MAX_DEG, SERVO_MIN_POS, SERVO_MAX_POS);
  myservo.write(servoPos);
}

void setVehicleSpeedKmh(float speedKmh) {
  if (abs(speedKmh) < 0.05f) {
    stopMotors();
    return;
  }

  if (speedKmh > 0) {
    int pwm = speedKmhToPwm(speedKmh, true);
    motorsForward(pwm);
  } else {
    int pwm = speedKmhToPwm(-speedKmh, false);
    motorsBackward(pwm);
  }
}

int speedKmhToPwm(float speedKmh, bool forward) {
  float maxKmh = forward ? MAX_FWD_KMH : MAX_REV_KMH;
  if (maxKmh <= 0.01f) return 0;

  float normalized = constrain(speedKmh / maxKmh, 0.0f, 1.0f);
  int pwm = PWM_MIN_EFFECTIVE + (int)((PWM_MAX - PWM_MIN_EFFECTIVE) * normalized);
  return constrain(pwm, 0, PWM_MAX);
}

void stopMotors() {
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void motorsBackward(int pwmSpeed) {
  pwmSpeed = constrain(pwmSpeed, 0, PWM_MAX);
  ledcWrite(ENA, pwmSpeed);
  ledcWrite(ENB, pwmSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void motorsForward(int pwmSpeed) {
  pwmSpeed = constrain(pwmSpeed, 0, PWM_MAX);
  ledcWrite(ENA, pwmSpeed);
  ledcWrite(ENB, pwmSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void printStatus() {
  const char* src =
    (activeSource == SOURCE_RC) ? "RC" :
    (activeSource == SOURCE_SERIAL) ? "SERIAL" : "NONE";

  if (activeSource == SOURCE_RC) {
    Serial.printf(
      "SRC=RC | rc1=%dus | rc2=%dus | speed=%.2f km/h | steer=%d deg | serialSpeed=%.2f km/h | serialSteer=%.1f deg | batt=%.2fV (%.1f%%)\n",
      rc1Us,
      rc2Us,
      dbgSpeedKmh,
      dbgSteeringDeg,
      serialSpeedKmh,
      serialSteeringDeg,
      battVoltage,
      battPct
    );
  } else {
    Serial.printf(
      "SRC=%s | speed=%.2f km/h | steer=%d deg | serialSpeed=%.2f km/h | serialSteer=%.1f deg | batt=%.2fV (%.1f%%)\n",
      src,
      dbgSpeedKmh,
      dbgSteeringDeg,
      serialSpeedKmh,
      serialSteeringDeg,
      battVoltage,
      battPct
    );
  }
}