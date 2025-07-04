#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "config.h"

void actuator_init(void);
void actuator_set_pump_state(PumpState_t state);
PumpState_t actuator_get_pump_state(void);
void actuator_set_led_state(LedState_t state);
const char *actuator_get_led_state_string(void);
void actuator_update_led(void);

#endif