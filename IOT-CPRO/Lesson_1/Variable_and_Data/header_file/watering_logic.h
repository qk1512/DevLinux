// watering_logic.h
#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H

#include "config.h"

void process_watering_logic(SystemConfig *config, SensorData *sensor);
void report_status(SystemConfig *config, SensorData *sensor);

#endif
