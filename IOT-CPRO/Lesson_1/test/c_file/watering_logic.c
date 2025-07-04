#include <stdio.h>
#include "watering_logic.h"
#include "sensors.h"
#include "actuators.h"

static SystemConfig_t config = {
    .moisture_min = MOISTURE_THRESHOLD_MIN,
    .moisture_max = MOISTURE_THRESHOLD_MAX,
    .max_watering_time = MAX_WATERING_TIME_MS,
    .sensor_interval = SENSOR_READ_INTERVAL_MS,
    .mode = MODE_AUTO};

static uint32_t last_watering_time = 0;
static uint32_t watering_start_time = 0;
static bool is_watering = false;

void watering_logic_init(void)
{
    printf("Watering logic initialized\n");
}

void watering_logic_process(void)
{
    SensorData_t sensor = sensor_get_data();
    uint32_t current_time = get_system_time();

    if (!sensor.is_valid)
    {
        actuator_set_led_state(LED_ERROR);
        actuator_set_pump_state(PUMP_OFF);
        return;
    }

    if (config.mode == MODE_AUTO)
    {
        if (is_watering)
        {
            // Kiểm tra điều kiện dừng tưới
            if (sensor.soil_moisture >= config.moisture_max ||
                current_time - watering_start_time >= config.max_watering_time)
            {
                actuator_set_pump_state(PUMP_OFF);
                is_watering = false;
                actuator_set_led_state(LED_NORMAL);
            }
            else
            {
                actuator_set_led_state(LED_WATERING);
            }
        }
        else
        {
            // Kiểm tra điều kiện bắt đầu tưới
            if (sensor.soil_moisture < config.moisture_min &&
                current_time - last_watering_time >= config.sensor_interval)
            {
                actuator_set_pump_state(PUMP_ON);
                is_watering = true;
                watering_start_time = current_time;
                last_watering_time = current_time;
                actuator_set_led_state(LED_WATERING);
                report_system_status(); // In thông tin khi bắt đầu tưới
            }
            else if (sensor.soil_moisture < config.moisture_min)
            {
                actuator_set_led_state(LED_LOW_MOISTURE_ALERT);
            }
            else
            {
                actuator_set_led_state(LED_NORMAL);
            }
        }
    }
}

void report_system_status(void)
{
    SensorData_t sensor = sensor_get_data();
    printf("System Status:\n");
    printf("Mode: %s\n", config.mode == MODE_AUTO ? "AUTO" : "MANUAL");
    printf("Soil Moisture: %d%%\n", sensor.soil_moisture);
    printf("Temperature: %.1f°C\n", sensor.temperature);
    printf("Pump: %s\n", actuator_get_pump_state() == PUMP_ON ? "ON" : "OFF");
    printf("LED: %s\n", actuator_get_led_state_string());
}

SystemMode_t get_system_mode(void)
{
    return config.mode;
}

void set_system_mode(SystemMode_t mode)
{
    config.mode = mode;
    if (mode == MODE_MANUAL)
    {
        actuator_set_pump_state(PUMP_OFF);
        is_watering = false;
        actuator_set_led_state(LED_NORMAL);
    }
}