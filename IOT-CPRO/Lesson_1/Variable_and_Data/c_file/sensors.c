#include <stdio.h>
#include <stdlib.h>
#include "sensors.h"

static SensorData_t sensor_data = {0};

void sensor_init(void)
{
    sensor_data.soil_moisture = 50; // Giá trị mặc định
    sensor_data.temperature = 25.0;
    sensor_data.is_valid = true;
    printf("Sensors initialized\n");
}

void sensor_read_data(void)
{
    static uint32_t last_read = 0;
    uint32_t current_time = get_system_time();

    if (current_time - last_read >= SENSOR_READ_INTERVAL_MS)
    {
        // Mô phỏng đọc cảm biến
        sensor_data.soil_moisture = sensor_data.soil_moisture > 10 ? sensor_data.soil_moisture - 5 : 10;
        sensor_data.temperature = 25.0 + (rand() % 50) / 10.0;
        sensor_data.is_valid = true;
        last_read = current_time;
    }
}

SensorData_t sensor_get_data(void)
{
    return sensor_data;
}