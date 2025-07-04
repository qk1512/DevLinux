#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"

void sensor_init(void);
void sensor_read_data(void);
SensorData_t sensor_get_data(void);

#endif