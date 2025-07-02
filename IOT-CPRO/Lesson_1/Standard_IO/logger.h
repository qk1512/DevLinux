#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

// Log levels (the lower the number, the more severe)
typedef enum
{
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

void logger_init(LogLevel level, const char *filepath);
void logger_set_level(LogLevel level);
void logger_close();

void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...);

#define log_message(level, ...) \
    logger_log(level, __FILE__, __LINE__, __VA_ARGS__)

#endif // LOGGER_H
