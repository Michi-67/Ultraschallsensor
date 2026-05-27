#ifndef ULTRASCHALL_SENSOR_H
#define ULTRASCHALL_SENSOR_H

#include <stdint.h>
#include "main.h"

extern const uint8_t CMD_DISTANCE[4];
extern const uint8_t CMD_TEMP[4];

uint16_t Sensor_ReadData(const uint8_t* command);

#endif // ULTRASCHALL_SENSOR_H
