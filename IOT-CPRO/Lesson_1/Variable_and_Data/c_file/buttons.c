// buttons.c
#include "buttons.h"
#include "actuators.h"
#include <stdio.h>
#include <time.h>

static clock_t manual_pump_start = 0;
static bool manual_pump_active = false;

void handle_buttons(SystemConfig *config)
{
    // Giả lập nút nhấn
    char input;
    printf("[INPUT] Press 'm' for change mode, 'w' for manual mode: ");
    input = getchar();
    while (getchar() != '\n')
        ; // clear buffer

    if (input == 'm')
    {
        config->mode = (config->mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        printf("[BUTTON] Switched to mode: %s\n", config->mode == MODE_AUTO ? "Auto" : "Manual");
        if (config->mode == MODE_MANUAL)
            turn_pump_off();
    }

    if (input == 'w' && config->mode == MODE_MANUAL)
    {
        turn_pump_on();
        manual_pump_start = clock();
        manual_pump_active = true;
    }

    if (manual_pump_active)
    {
        double elapsed = (double)(clock() - manual_pump_start) / CLOCKS_PER_SEC * 1000;
        if (elapsed >= 10000)
        {
            turn_pump_off();
            manual_pump_active = false;
        }
    }
}
