#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include "config.h"
#include "sensors.h"
#include "watering_logic.h"
#include "actuators.h"
#include "buttons.h"

void system_init(void)
{
    sensor_init();
    actuator_init();
    button_init();
    watering_logic_init();
    printf("SPWS Initialized - Default MODE_AUTO\n");
}

int main(void)
{
    system_init();

    while (true)
    {
        //printf("Debug: Main loop iteration\n"); // Debug: Xác nhận vòng lặp chạy
        button_process();
        watering_logic_process();
        actuator_update_led();
        sensor_read_data();

        // In trạng thái định kỳ (mô phỏng)
        static uint32_t last_report = 0;
        uint32_t current_time = get_system_time();
        //printf("Debug: current_time = %u, last_report = %u\n", current_time, last_report); // Debug
        if (current_time - last_report >= REPORT_INTERVAL_MS)
        {
            report_system_status();
            last_report = current_time;
        }

        // Độ trễ hệ thống
        delay_ms(SYSTEM_LOOP_DELAY_MS); // Dùng đúng SYSTEM_LOOP_DELAY_MS
    }

    return 0;
}

uint32_t get_system_time(void)
{
    static uint32_t time = 0;
    //printf("Debug: get_system_time = %u\n", time); // Debug
    return time++;
}

void delay_ms(uint32_t ms)
{
    usleep(ms * 1000);                              // Chuyển đổi ms thành micro giây
    //printf("Delayed for %u ms using usleep\n", ms); // Sửa %u để in đúng ms
}