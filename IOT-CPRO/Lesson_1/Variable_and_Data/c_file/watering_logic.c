// watering_logic.c
#include "watering_logic.h"
#include "actuators.h"
#include <stdio.h>
#include <time.h>

static clock_t last_watering_time = 0;

void process_watering_logic(SystemConfig *config, SensorData *sensor)
{
    clock_t now = clock();
    double time_since_last = (double)(now - last_watering_time) / CLOCKS_PER_SEC * 1000;

    if (get_pump_state() == PUMP_OFF)
    {
        if (sensor->soil_moisture < config->moisture_min_threshold && time_since_last >= config->sensor_check_interval_ms)
        {
            turn_pump_on();
            last_watering_time = clock();
        }
    }
    else
    {
        double watering_duration = (double)(now - last_watering_time) / CLOCKS_PER_SEC * 1000;
        if (sensor->soil_moisture >= config->moisture_max_threshold || watering_duration >= config->max_watering_time_ms)
        {
            turn_pump_off();
        }
    }
}

void report_status(SystemConfig *config, SensorData *sensor)
{
    const char *mode_str = config->mode == MODE_AUTO ? "Auto" : "Manual";
    const char *pump_str = get_pump_state() == PUMP_ON ? "Pump ON" : "Pump OFF";
    printf("[STATUS] Mode: %s | Pump: %s | SoilMoisture: %d%%\n",
           mode_str, pump_str, sensor->soil_moisture);
}
