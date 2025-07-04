#include <stdio.h>
#include "actuators.h"

static led_status_t current_led_status = LED_NORMAL;

void actuators_init(void)
{
    // Initialize GPIO for pump and LED (simulated)
    printf("Actuators Initialized\n");
}

void actuators_pump_on(void)
{
    printf("Pump ON\n");
}

void actuators_pump_off(void)
{
    printf("Pump OFF\n");
}

void actuators_set_led(led_status_t status)
{
    current_led_status = status;
}

void actuators_update_led(void)
{
    const char *status_str;
    switch (current_led_status)
    {
    case LED_NORMAL:
        status_str = "Green (Normal)";
        break;
    case LED_WATERING:
        status_str = "Yellow (Watering)";
        break;
    case LED_LOW_MOISTURE_ALERT:
        status_str = "Red (Low Moisture)";
        break;
    case LED_ERROR:
        status_str = "Red (Error)";
        break;
    default:
        status_str = "Unknown";
        break;
    }
    printf("LED Status: %s\n", status_str);
}