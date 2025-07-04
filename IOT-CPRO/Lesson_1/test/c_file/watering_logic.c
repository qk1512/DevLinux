#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "watering_logic.h"
#include "config.h"

static system_mode_t current_mode = MODE_AUTO;
static bool pump_active = false;
static time_t last_sensor_check = 0;
static time_t last_watering_start = 0;
static system_config_t config = {
    .min_moisture = 30.0,
    .max_moisture = 70.0,
    .max_watering_duration = 30, // 30 seconds
    .sensor_check_interval = 300 // 5 minutes
};

static void update_pump_and_led(const sensor_data_t *data)
{
    led_status_t led_status = LED_NORMAL;
    bool new_pump_state = pump_active;

    if (!data->is_valid)
    {
        led_status = LED_ERROR;
        new_pump_state = false;
    }
    else if (current_mode == MODE_AUTO)
    {
        if (data->soil_moisture < config.min_moisture && !pump_active &&
            (last_watering_start == 0 || difftime(time(NULL), last_watering_start) >= config.max_watering_duration))
        {
            new_pump_state = true;
            last_watering_start = time(NULL);
            led_status = LED_WATERING;
        }
        else if (pump_active && (data->soil_moisture >= config.max_moisture ||
                                 difftime(time(NULL), last_watering_start) >= config.max_watering_duration))
        {
            new_pump_state = false;
            led_status = LED_NORMAL;
        }
        else if (data->soil_moisture < config.min_moisture)
        {
            led_status = LED_LOW_MOISTURE_ALERT;
        }
    }
    else
    {
        led_status = pump_active ? LED_WATERING : LED_NORMAL;
    }

    if (new_pump_state != pump_active)
    {
        pump_active = new_pump_state;
        if (pump_active)
        {
            actuators_pump_on();
        }
        else
        {
            actuators_pump_off();
        }
    }
    actuators_set_led(led_status);
}

void watering_logic_init(void)
{
    printf("Watering Logic Initialized\n");
}

void watering_logic_update(const sensor_data_t *data)
{
    update_pump_and_led(data);
    last_sensor_check = time(NULL);
}

bool watering_logic_is_sensor_check_due(void)
{
    return difftime(time(NULL), last_sensor_check) >= config.sensor_check_interval;
}

void watering_logic_report_status(void)
{
    static time_t last_report = 0;
    if (difftime(time(NULL), last_report) >= 60)
    { // Report every minute
        printf("System Status: Mode=%s, Pump=%s\n",
               current_mode == MODE_AUTO ? "AUTO" : "MANUAL",
               pump_active ? "ON" : "OFF");
        last_report = time(NULL);
    }
}

void watering_logic_set_mode(system_mode_t mode)
{
    if (mode != current_mode)
    {
        current_mode = mode;
        if (mode == MODE_MANUAL && pump_active)
        {
            pump_active = false;
            actuators_pump_off();
            actuators_set_led(LED_NORMAL);
        }
        printf("Mode Changed to: %s\n", mode == MODE_AUTO ? "AUTO" : "MANUAL");
    }
}

void watering_logic_manual_water(void)
{
    if (current_mode == MODE_MANUAL && !pump_active)
    {
        pump_active = true;
        actuators_pump_on();
        actuators_set_led(LED_WATERING);
        printf("Manual Watering Started for 10 seconds\n");
        // Simulate 10-second watering
        nanosleep(&(struct timespec){.tv_sec = 10, .tv_nsec = 0}, NULL);
        pump_active = false;
        actuators_pump_off();
        actuators_set_led(LED_NORMAL);
        printf("Manual Watering Stopped\n");
    }
}

system_mode_t watering_logic_get_mode(void)
{
    return current_mode;
}