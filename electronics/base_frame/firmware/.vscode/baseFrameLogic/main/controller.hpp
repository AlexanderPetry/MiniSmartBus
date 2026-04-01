#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"      
#include "esp_timer.h"
#include "driver/gpio.h"  



typedef struct {

    float n_ml; // motor speed left
    float n_mr; // motor speed right

} motor_speeds;


typedef struct {
    int steeringPct;   // 0–100
    int throttlePct;   // 0–100
    bool valid;
} RCInput;

motor_speeds getMotorDiff(float angle, float speed);

