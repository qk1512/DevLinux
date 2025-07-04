#include <stdio.h>
#include <stdlib.h>
#include "sensors.h"

// Simulated sensor reading
void sensors_read(sensor_data_t *data)
{
    // Simulate reading from ADC or other interface
    data->soil_moisture = (float)(rand() % 101);             // Random value 0-100%
    data->temperature = 20.0 + (float)(rand() % 150) / 10.0; // 20.0-34.9°C
    data->is_valid = true;                                   // Assume sensors are working
    printf("Sensor Read: Soil Moisture = %.1f%%, Temperature = %.1f°C\n",
           data->soil_moisture, data->temperature);
}

void sensors_init(void)
{
    // Initialize ADC or sensor interfaces (simulated)
    srand((unsigned int)time(NULL));
    printf("Sensors Initialized\n");
}