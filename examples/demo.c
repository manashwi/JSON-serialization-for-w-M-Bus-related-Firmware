#include <stdio.h>
#include "json_serializer.h"

int main(void)
{
    char json_buffer[1024];

    GatewayData gw = {
        .gateway_id = "GW001",
        .date = "2024-01-01",
        .device_type = "water",
        .interval_minutes = 60,
        .total_readings = 2,
        .values.device_count = 1
    };

    DeviceReading *dr = &gw.values.readings[0];
    snprintf(dr->media, MAX_TYPE_LEN, "water");
    snprintf(dr->meter, MAX_TYPE_LEN, "flow");
    snprintf(dr->device_id, MAX_ID_LEN, "DEV001");
    snprintf(dr->unit, MAX_UNIT_LEN, "m3");
    dr->data_count = 2;

    snprintf(dr->data[0].timestamp, MAX_TIMESTAMP_LEN, "2024-01-01T00:00");
    snprintf(dr->data[0].meter_datetime, MAX_TIMESTAMP_LEN, "2024-01-01T00:00");
    dr->data[0].total_m3 = 12.345;
    snprintf(dr->data[0].status, MAX_STATUS_LEN, "OK");

    snprintf(dr->data[1].timestamp, MAX_TIMESTAMP_LEN, "2024-01-01T01:00");
    snprintf(dr->data[1].meter_datetime, MAX_TIMESTAMP_LEN, "2024-01-01T01:00");
    dr->data[1].total_m3 = 13.111;
    snprintf(dr->data[1].status, MAX_STATUS_LEN, "OK");

    if (serialize_to_json(&gw, json_buffer, sizeof(json_buffer)) == 0)
        printf("%s\n", json_buffer);
    else
        printf("Serialization failed\n");

    return 0;
}
