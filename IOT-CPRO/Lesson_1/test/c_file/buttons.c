#include <stdio.h>
#include <stdbool.h>
#include "buttons.h"
#include "watering_logic.h"

static bool button_auto_pressed = false;
static bool button_manual_pressed = false;

void buttons_init(void)
{
    printf("Buttons Initialized\n");
}

void buttons_check(void)
{
    static bool prev_auto_state = false;
    static bool prev_manual_state = false;
    char input;

    printf("Press 'a' to toggle Auto/Manual, 'm' for Manual watering, or Enter to continue: ");
    input = getchar();
    while (getchar() != '\n')
        ; // Clear input buffer

    button_auto_pressed = (input == 'a');
    button_manual_pressed = (input == 'm');

    if (button_auto_pressed && !prev_auto_state)
    {
        watering_logic_set_mode(watering_logic_get_mode() == MODE_AUTO ? MODE_MANUAL : MODE_AUTO);
    }
    if (button_manual_pressed && !prev_manual_state)
    {
        watering_logic_manual_water();
    }

    prev_auto_state = button_auto_pressed;
    prev_manual_state = button_manual_pressed;
}