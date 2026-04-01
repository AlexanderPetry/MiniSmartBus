#include "controller.hpp"


motor_speeds getMotorDiff(float angle, float speed) {
    // Normalize steering: -1.0 (left) ... 0 (straight) ... +1.0 (right)
    float f = angle / 90.0f;
    f = fmaxf(-1.0f, fminf(1.0f, f));

    // At f = 0, both wheels go at speed
    // At f = +1, right wheel goes faster, left wheel slows; at f = -1, reverse
    float pl = speed * (1.0f - f);
    float pr = speed * (1.0f + f);

    // Optional: scale so maximum motor demand does not exceed |speed| in magnitude
    float max_abs = fmaxf(fabsf(pl), fabsf(pr));
    if (max_abs > 0.0f) {
        float scale = fabsf(speed) / max_abs;
        pl *= scale;
        pr *= scale;
    }

    motor_speeds m;
    m.n_ml = pl;
    m.n_mr = pr;

    return m;
}

int steeringPercentToAngle(int steeringPct, int minAngle = -90, int maxAngle = 90) {
    if (steeringPct < 0)  steeringPct = 0;
    if (steeringPct > 100) steeringPct = 100;

    // Map 0–100 → minAngle–maxAngle
    return (steeringPct * (maxAngle - minAngle)) / 100 + minAngle;
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int constrain(int x, int low, int high) {
    if (x < low) return low;
    if (x > high) return high;
    return x;
}

uint32_t pulseIn_us(gpio_num_t pin, uint32_t max_us = 25000) {
    uint64_t start = esp_timer_get_time();
    uint64_t now = 0;

    // Wait for HIGH
    while (gpio_get_level(pin) == 0) {
        now = esp_timer_get_time();
        if (now - start >= max_us) return 0;
    }

    // Time start of HIGH
    uint64_t high_start = now;

    // Wait for LOW
    while (gpio_get_level(pin) == 1) {
        now = esp_timer_get_time();
        if (now - start >= max_us) return 0;
    }

    uint64_t high_end = now;
    int64_t pulse_us = high_end - high_start;
    if (pulse_us < 0) return 0;

    return (uint32_t)pulse_us;
}

RCInput readRCChannels(gpio_num_t ch1Pin, gpio_num_t ch2Pin) {
    RCInput rc = {
        .steeringPct = 50,
        .throttlePct = 50,
        .valid = false
    };

    gpio_set_direction(ch1Pin, GPIO_MODE_INPUT);
    gpio_set_direction(ch2Pin, GPIO_MODE_INPUT);

    uint32_t ch1_raw = pulseIn_us(ch1Pin, 25000);
    uint32_t ch2_raw = pulseIn_us(ch2Pin, 25000);

    // Basic RC range check (µs)
    if (ch1_raw < 900 || ch1_raw > 2200 ||
        ch2_raw < 900 || ch2_raw > 2200) {
        ESP_LOGW("RC", "Signal lost - STOP");
        return rc;  // 50/50, valid = false
    }

    int ch1_percent = constrain(map(ch1_raw, 960, 1950, 0, 100), 0, 100);
    int ch2_percent = constrain(map(ch2_raw, 1100, 2100, 0, 100), 0, 100);

    return {
        .steeringPct = ch1_percent,
        .throttlePct = ch2_percent,
        .valid = true
    };
}