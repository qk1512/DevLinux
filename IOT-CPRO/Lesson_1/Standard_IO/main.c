#include <string.h> // For strcmp
#include <stdlib.h>
#include "logger.h"

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "clean") == 0)
    {
        FILE *f = fopen("log.txt", "w"); // Mở file ở chế độ ghi mới, xóa toàn bộ nội dung
        if (f)
        {
            fclose(f);
            printf("Log file cleaned.\n");
        }
        else
        {
            fprintf(stderr, "Failed to clean log file.\n");
        }
        return 0;
    }

    logger_init(LOG_INFO, "log.txt");

    log_message(LOG_INFO, "System initialized.");
    log_message(LOG_ERROR, "Failed to open configuration file.");
    log_message(LOG_WARNING, "Low disk space.");

    logger_set_level(LOG_DEBUG);
    log_message(LOG_DEBUG, "Debugging enabled.");

    logger_close();
    return 0;
}
