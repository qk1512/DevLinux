#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H

#include "sensors.h"
#include "actuators.h"
#include <stdbool.h>
typedef enum
{
    MODE_AUTO,
    MODE_MANUAL
} system_mode_t;

void watering_logic_init(void);
void watering_logic_update(const sensor_data_t *data);
bool watering_logic_is_sensor_check_due(void);
void watering_logic_report_status(void);
void watering_logic_set_mode(system_mode_t mode);
void watering_logic_manual_water(void);
system_mode_t watering_logic_get_mode(void); // Added getter function

#endif