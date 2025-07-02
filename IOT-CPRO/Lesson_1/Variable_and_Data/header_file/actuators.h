// actuators.h
#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "config.h"

void turn_pump_on();
void turn_pump_off();
PumpState get_pump_state();

void set_led_status(LedStatus status);
void update_led_status(const SystemConfig *config, const SensorData *sensor);

#endif
