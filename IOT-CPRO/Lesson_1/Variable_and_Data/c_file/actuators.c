#include <stdio.h>
#include <stdlib.h>
#include "actuators.h"

static PumpState_t pump_state = PUMP_OFF;
static LedState_t led_state = LED_NORMAL;

void actuator_init(void)
{
    pump_state = PUMP_OFF;
    led_state = LED_NORMAL;
    printf("Actuators initialized\n");
}

void actuator_set_pump_state(PumpState_t state)
{
    pump_state = state;
    printf("Pump %s\n", state == PUMP_ON ? "ON" : "OFF");
}

PumpState_t actuator_get_pump_state(void)
{
    return pump_state;
}

void actuator_set_led_state(LedState_t state)
{
    led_state = state;
}

const char *actuator_get_led_state_string(void)
{
    switch (led_state)
    {
    case LED_NORMAL:
        return "NORMAL";
    case LED_WATERING:
        return "WATERING";
    case LED_LOW_MOISTURE_ALERT:
        return "LOW_MOISTURE";
    case LED_ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

void actuator_update_led(void)
{
    // Mô phỏng cập nhật LED
    //printf("LED State: %s\n", actuator_get_led_state_string());
}