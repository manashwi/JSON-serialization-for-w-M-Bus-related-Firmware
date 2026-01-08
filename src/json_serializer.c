#include "json_serializer.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* ================= Writer Context ================= */

typedef struct {
    char *buffer;
    size_t size;
    size_t index;
} JsonWriter;

/* ================= Helper Functions ================= */

static json_serializer_status_t jw_write(JsonWriter *jw, const char *str)
{
    size_t len;

    if (!jw || !str)
        return JSON_SERIALIZER_ERR_NULL_PTR;

    len = strlen(str);

    if ((jw->index + len) >= jw->size)
        return JSON_SERIALIZER_ERR_BUFFER_TOO_SMALL;

    memcpy(&jw->buffer[jw->index], str, len);
    jw->index += len;
    jw->buffer[jw->index] = '\0';

    return JSON_SERIALIZER_OK;
}

static json_serializer_status_t jw_write_fmt(
    JsonWriter *jw,
    const char *fmt,
    ...)
{
    int written;
    va_list args;

    if (!jw || !fmt)
        return JSON_SERIALIZER_ERR_NULL_PTR;

    va_start(args, fmt);
    written = vsnprintf(
        &jw->buffer[jw->index],
        jw->size - jw->index,
        fmt,
        args
    );
    va_end(args);

    if (written < 0 || (size_t)written >= (jw->size - jw->index))
        return JSON_SERIALIZER_ERR_BUFFER_TOO_SMALL;

    jw->index += (size_t)written;
    return JSON_SERIALIZER_OK;
}

/* ================= Serialization ================= */

json_serializer_status_t serialize_to_json(
    const GatewayData *input,
    char *output_buf,
    size_t buf_size
)
{
    JsonWriter jw;
    json_serializer_status_t status;

    if (!input || !output_buf || buf_size == 0)
        return JSON_SERIALIZER_ERR_NULL_PTR;

    jw.buffer = output_buf;
    jw.size = buf_size;
    jw.index = 0;

    /* Root array */
    status = jw_write(&jw, "[");
    if (status) return status;

    /* Gateway object */
    status = jw_write(&jw, "{");
    if (status) return status;

    status = jw_write_fmt(&jw,
        "\"gateway_id\":\"%s\","
        "\"date\":\"%s\","
        "\"device_type\":\"%s\","
        "\"interval_minutes\":%u,"
        "\"total_readings\":%u,",
        input->gateway_id,
        input->date,
        input->device_type,
        input->interval_minutes,
        input->total_readings
    );
    if (status) return status;

    /* Values */
    status = jw_write(&jw, "\"values\":{");
    if (status) return status;

    status = jw_write(&jw, "\"readings\":[");
    if (status) return status;

    for (uint8_t i = 0; i < input->values.device_count; i++) {

        DeviceReading *dr = &input->values.readings[i];

        status = jw_write_fmt(&jw,
            "{"
            "\"media\":\"%s\","
            "\"meter\":\"%s\","
            "\"device_id\":\"%s\","
            "\"unit\":\"%s\",",
            dr->media,
            dr->meter,
            dr->device_id,
            dr->unit
        );
        if (status) return status;

        status = jw_write(&jw, "\"data\":[");
        if (status) return status;

        for (uint8_t j = 0; j < dr->data_count; j++) {

            DataPoint *dp = &dr->data[j];

            status = jw_write_fmt(&jw,
                "{"
                "\"timestamp\":\"%s\","
                "\"meter_datetime\":\"%s\","
                "\"total_m3\":%.3f,"
                "\"status\":\"%s\""
                "}",
                dp->timestamp,
                dp->meter_datetime,
                dp->total_m3,
                dp->status
            );
            if (status) return status;

            if (j < dr->data_count - 1)
                jw_write(&jw, ",");
        }

        status = jw_write(&jw, "]}");
        if (status) return status;

        if (i < input->values.device_count - 1)
            jw_write(&jw, ",");
    }

    status = jw_write(&jw, "]}");
    if (status) return status;

    status = jw_write(&jw, "}");
    if (status) return status;

    status = jw_write(&jw, "]");
    if (status) return status;

    return JSON_SERIALIZER_OK;
}
