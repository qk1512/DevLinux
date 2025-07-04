#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H

#include "config.h"

void watering_logic_init(void);
void watering_logic_process(void);
void report_system_status(void);
SystemMode_t get_system_mode(void);
void set_system_mode(SystemMode_t mode);

#endif