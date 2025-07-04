#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
    float soil_moisture; // Percentage (0-100)
    float temperature;   // Celsius
    bool is_valid;       // Sensor data validity
} sensor_data_t;

void sensors_init(void);
void sensors_read(sensor_data_t *data);

#endif