#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "header_file/sensors.h"
#include "header_file/watering_logic.h"
#include "header_file/actuators.h"
#include "header_file/buttons.h"
#include "header_file/config.h"

int main()
{
    // Initialize system
    sensors_init();
    actuators_init();
    buttons_init();
    watering_logic_init();

    printf("SPWS Initialized. Starting in MODE_AUTO.\n");

    while (true)
    {
        // Handle button events
        buttons_check();

        // Update sensor data periodically
        if (watering_logic_is_sensor_check_due())
        {
            sensor_data_t sensor_data;
            sensors_read(&sensor_data);
            watering_logic_update(&sensor_data);
        }

        // Update LED status
        actuators_update_led();

        // Send periodic status report
        watering_logic_report_status();

        // Simulate delay for power efficiency (e.g., 100ms)
        nanosleep(&(struct timespec){.tv_sec = 0, .tv_nsec = 100000000}, NULL);
    }

    return 0;
}