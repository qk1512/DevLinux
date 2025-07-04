#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include "watering_logic.h"

typedef struct
{
    float min_moisture;        // Minimum moisture threshold to start watering
    float max_moisture;        // Maximum moisture threshold to stop watering
    int max_watering_duration; // Maximum watering duration in seconds
    int sensor_check_interval; // Sensor check interval in seconds
} system_config_t;

#endif