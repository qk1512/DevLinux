#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stdbool.h>
typedef enum
{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} led_status_t;

void actuators_init(void);
void actuators_pump_on(void);
void actuators_pump_off(void);
void actuators_set_led(led_status_t status);
void actuators_update_led(void);

#endif