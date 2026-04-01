extern "C" void app_main(void);



#include "controller.cpp"
 
void app_main(void)
{

    const gpio_num_t CH1_PIN = GPIO_NUM_12;  // RC steering
    const gpio_num_t CH2_PIN = GPIO_NUM_13;  // RC throttle

    while (true) {
        RCInput rc = readRCChannels(CH1_PIN, CH2_PIN);

        if (rc.valid) {
            int servo_angle = steeringPercentToAngle(rc.steeringPct, -90, 90);
            printf(" steering angle=%d\n", servo_angle);
            int motor_power = steeringPercentToAngle(rc.throttlePct, 0, 255);
            motor_speeds m = getMotorDiff(servo_angle, motor_power);
            printf(" motor speeds=%f / %f\n", m.n_ml, m.n_mr);
            
        }
        vTaskDelay(pdMS_TO_TICKS(20));  // keep loop light
    }
 
}