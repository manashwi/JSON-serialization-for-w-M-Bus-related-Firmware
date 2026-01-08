#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>
#include <stdint.h>

/* ================= Configuration ================= */

#define MAX_DEVICES         4
#define MAX_READINGS        4
#define MAX_DATA_POINTS     4

#define MAX_ID_LEN          32
#define MAX_TYPE_LEN        16
#define MAX_UNIT_LEN        8
#define MAX_STATUS_LEN      8
#define MAX_TIMESTAMP_LEN  20
#define MAX_DATE_LEN        11

/* ================= Error Codes ================= */

typedef enum {
    JSON_SERIALIZER_OK = 0,
    JSON_SERIALIZER_ERR_NULL_PTR = -1,
    JSON_SERIALIZER_ERR_BUFFER_TOO_SMALL = -2,
    JSON_SERIALIZER_ERR_INVALID_DATA = -3
} json_serializer_status_t;

/* ================= Data Structures ================= */

typedef struct {
    char timestamp[MAX_TIMESTAMP_LEN];
    char meter_datetime[MAX_TIMESTAMP_LEN];
    double total_m3;
    char status[MAX_STATUS_LEN];
} DataPoint;

typedef struct {
    char media[MAX_TYPE_LEN];
    char meter[MAX_TYPE_LEN];
    char device_id[MAX_ID_LEN];
    char unit[MAX_UNIT_LEN];

    DataPoint data[MAX_DATA_POINTS];
    uint8_t data_count;
} DeviceReading;

typedef struct {
    uint8_t device_count;
    DeviceReading readings[MAX_READINGS];
} Values;

typedef struct {
    char gateway_id[MAX_ID_LEN];
    char date[MAX_DATE_LEN];
    char device_type[MAX_TYPE_LEN];
    uint16_t interval_minutes;
    uint16_t total_readings;

    Values values;
} GatewayData;

/* ================= Public API ================= */

json_serializer_status_t serialize_to_json(
    const GatewayData *input,
    char *output_buf,
    size_t buf_size
);

#endif /* JSON_SERIALIZER_H */
