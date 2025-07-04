#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

// Định nghĩa các hằng số
#define SENSOR_READ_INTERVAL_MS 30 // 5 phút
#define MAX_WATERING_TIME_MS 60000     // 60 giây
#define MANUAL_WATERING_TIME_MS 10000  // 10 giây
#define REPORT_INTERVAL_MS 20       // 1 phút
#define SYSTEM_LOOP_DELAY_MS 1000       // 100ms

// Ngưỡng độ ẩm
#define MOISTURE_THRESHOLD_MIN 30 // 30%
#define MOISTURE_THRESHOLD_MAX 70 // 70%

// Định nghĩa trạng thái
typedef enum
{
    MODE_AUTO,
    MODE_MANUAL
} SystemMode_t;

typedef enum
{
    PUMP_OFF,
    PUMP_ON
} PumpState_t;

typedef enum
{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState_t;

// Cấu trúc dữ liệu cảm biến
typedef struct
{
    uint8_t soil_moisture; // 0-100%
    float temperature;     // Độ C
    bool is_valid;         // Trạng thái cảm biến
} SensorData_t;

// Cấu trúc cài đặt hệ thống
typedef struct
{
    uint8_t moisture_min;       // Ngưỡng độ ẩm tối thiểu
    uint8_t moisture_max;       // Ngưỡng độ ẩm tối đa
    uint32_t max_watering_time; // Thời gian tưới tối đa
    uint32_t sensor_interval;   // Chu kỳ đọc cảm biến
    SystemMode_t mode;          // Chế độ hệ thống
} SystemConfig_t;

// Khai báo prototype các hàm hệ thống
uint32_t get_system_time(void);
void delay_ms(uint32_t ms);

#endif // CONFIG_H