// main.c
#include "config.h"
#include "sensors.h"
#include "actuators.h"
#include "watering_logic.h"
#include "buttons.h"
#include <stdio.h>
#include <unistd.h> // for sleep (simulate delay)


void init()
{
    
}

int main()
{
    SystemConfig config = {
        .moisture_min_threshold = 30,
        .moisture_max_threshold = 70,
        .max_watering_time_ms = 10000,
        .sensor_check_interval_ms = 5000,
        .mode = MODE_AUTO};

    SensorData sensor = {0};

    //initialize_hardware();
    printf("[INFO] Smart Plant Watering System Started\n");

    while (1)
    {
        handle_buttons(&config);
        read_sensors(&sensor);

        if (config.mode == MODE_AUTO)
        {
            process_watering_logic(&config, &sensor);
        }

        update_led_status(&config, &sensor);
        report_status(&config, &sensor);

        usleep(1000 * 100); // giả lập delay 100ms
    }

    return 0;
}
