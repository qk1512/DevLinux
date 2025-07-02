// sensors.c
#include "sensors.h"
#include <stdio.h>

void read_sensors(SensorData *sensor)
{
    static int counter = 0;
    sensor->soil_moisture = 25 + (counter++ % 30); // giả lập dao động độ ẩm
    sensor->temperature = 25.0;                    // giữ cố định
    printf("[SENSOR] SoilMoisture: %d%%, Temperature: %.1f°C\n", sensor->soil_moisture, sensor->temperature);
}
