// actuators.c
#include "actuators.h"
#include <stdio.h>

static PumpState pump_state = PUMP_OFF;
static LedStatus led_status = LED_NORMAL;

void turn_pump_on()
{
    if (pump_state == PUMP_OFF)
    {
        pump_state = PUMP_ON;
        printf("[ACTUATOR] Bơm nước: BẬT\n");
    }
}

void turn_pump_off()
{
    if (pump_state == PUMP_ON)
    {
        pump_state = PUMP_OFF;
        printf("[ACTUATOR] Bơm nước: TẮT\n");
    }
}

PumpState get_pump_state()
{
    return pump_state;
}

void set_led_status(LedStatus status)
{
    if (led_status != status)
    {
        led_status = status;
        const char *msg = "";
        switch (status)
        {
        case LED_NORMAL:
            msg = "Green - Normal";
            break;
        case LED_WATERING:
            msg = "Yellow - Watering";
            break;
        case LED_LOW_MOISTURE_ALERT:
            msg = "Red - SoilMoisture Low";
            break;
        case LED_ERROR:
            msg = "Red Blink - Error";
            break;
        }
        printf("[LED] Status: %s\n", msg);
    }
}

void update_led_status(const SystemConfig *config, const SensorData *sensor)
{
    if (get_pump_state() == PUMP_ON)
    {
        set_led_status(LED_WATERING);
    }
    else if (sensor->soil_moisture < config->moisture_min_threshold)
    {
        set_led_status(LED_LOW_MOISTURE_ALERT);
    }
    else
    {
        set_led_status(LED_NORMAL);
    }
}
