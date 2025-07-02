#include "logger.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

static LogLevel current_level = LOG_DEBUG;
static FILE *log_file = NULL;
static bool use_file_output = false;

static const char *level_to_string(LogLevel level)
{
    switch (level)
    {
    case LOG_EMERGENCY:
        return "EMERGENCY";
    case LOG_ALERT:
        return "ALERT";
    case LOG_CRITICAL:
        return "CRITICAL";
    case LOG_ERROR:
        return "ERROR";
    case LOG_WARNING:
        return "WARNING";
    case LOG_NOTICE:
        return "NOTICE";
    case LOG_INFO:
        return "INFO";
    case LOG_DEBUG:
        return "DEBUG";
    default:
        return "UNKNOWN";
    }
}

void logger_init(LogLevel level, const char *filepath)
{
    current_level = level;
    if (filepath != NULL)
    {
        log_file = fopen(filepath, "a");
        if (log_file)
        {
            use_file_output = true;
        }
        else
        {
            fprintf(stderr, "[LOGGER] Failed to open log file: %s\n", filepath);
            use_file_output = false;
        }
    }
}

void logger_set_level(LogLevel level)
{
    current_level = level;
}

void logger_close()
{
    if (log_file)
    {
        fclose(log_file);
        log_file = NULL;
        use_file_output = false;
    }
}

void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...)
{
    if (level > current_level)
        return;

    // Get current time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[20]; // "YYYY-MM-DD HH:MM:SS"
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    // Format message
    char message[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

    // Final log line
    char logline[1200];
    snprintf(logline, sizeof(logline), "[%s] [%s] [%s:%d] - %s\n",
             timestamp, level_to_string(level), file, line, message);

    // Output
    FILE *output = (level <= LOG_ERROR) ? stderr : stdout;
    fprintf(output, "%s", logline);
    fflush(output);

    if (use_file_output && log_file)
    {
        fprintf(log_file, "%s", logline);
        fflush(log_file);
    }
}
