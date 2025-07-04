#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buttons.h"
#include "watering_logic.h"
#include "actuators.h"

static bool auto_button_pressed = false;
static bool manual_button_pressed = false;
static uint32_t manual_watering_start = 0;
static bool manual_watering_active = false;

void button_init(void)
{
    // Khởi tạo seed cho rand() để đảm bảo ngẫu nhiên
    srand(time(NULL));
    printf("Buttons initialized\n");
    printf("Simulating random button presses (1-100): 1-50 (toggle mode, 50%%), 51-75 (manual watering, 25%%), 76-100 (no action, 25%%)\n");
}

void button_cleanup(void)
{
    // Không cần khôi phục terminal vì không dùng termios
}

void button_process(void)
{
    // Mô phỏng nhấn nút ngẫu nhiên
    static uint32_t last_check = 0;
    uint32_t current_time = get_system_time();

    if (current_time - last_check >= 1000)
    { // Kiểm tra mỗi 1 giây
        // Tạo số ngẫu nhiên từ 1 đến 100
        int random_value = rand() % 100 + 1;
        printf("Debug: Random value = %d\n", random_value);

        // Ánh xạ số ngẫu nhiên để kích hoạt nút
        if (random_value <= 50)
        { // 1-50: Nút 1 (50%)
            auto_button_pressed = true;
            printf("Debug: Randomly pressed button 1 (toggle mode)\n");
        }
        else if (random_value <= 75)
        { // 51-75: Nút 2 (25%)
            manual_button_pressed = true;
            printf("Debug: Randomly pressed button 2 (manual watering)\n");
        } // 76-100: Không làm gì (25%)

        last_check = current_time;
    }

    // Xử lý nút chuyển chế độ
    if (auto_button_pressed)
    {
        SystemMode_t new_mode = (get_system_mode() == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        set_system_mode(new_mode);
        printf("Switched to %s mode\n", new_mode == MODE_AUTO ? "AUTO" : "MANUAL");
        auto_button_pressed = false;
    }

    // Xử lý nút tưới thủ công
    if (manual_button_pressed && get_system_mode() == MODE_MANUAL && !manual_watering_active)
    {
        button_trigger_manual_watering();
        manual_button_pressed = false;
    }

    // Kiểm tra thời gian tưới thủ công
    if (manual_watering_active &&
        current_time - manual_watering_start >= MANUAL_WATERING_TIME_MS)
    {
        actuator_set_pump_state(PUMP_OFF);
        manual_watering_active = false;
        actuator_set_led_state(LED_NORMAL);
    }
}

void button_trigger_manual_watering(void)
{
    if (get_system_mode() == MODE_MANUAL)
    {
        actuator_set_pump_state(PUMP_ON);
        manual_watering_start = get_system_time();
        manual_watering_active = true;
        actuator_set_led_state(LED_WATERING);
        printf("Manual watering started\n");
        report_system_status(); // In thông tin khi bắt đầu tưới thủ công
    }
}