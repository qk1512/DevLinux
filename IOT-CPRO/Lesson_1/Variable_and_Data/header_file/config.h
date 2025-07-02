// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

// Chế độ hệ thống
typedef enum
{
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

// Trạng thái bơm nước
typedef enum
{
    PUMP_OFF,
    PUMP_ON
} PumpState;

// Trạng thái LED
typedef enum
{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedStatus;

// Dữ liệu cảm biến
typedef struct
{
    uint8_t soil_moisture; // %
    float temperature;     // độ C
} SensorData;

// Cài đặt hệ thống
typedef struct
{
    uint8_t moisture_min_threshold;    // %
    uint8_t moisture_max_threshold;    // %
    uint32_t max_watering_time_ms;     // ms
    uint32_t sensor_check_interval_ms; // ms
    SystemMode mode;
} SystemConfig;

#endif
