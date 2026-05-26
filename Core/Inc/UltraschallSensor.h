#ifndef ULTRASCHALL_SENSOR_H
#define ULTRASCHALL_SENSOR_H

#include <stdint.h>
#include "main.h"

uint16_t Sensor_ReadData(const uint8_t* command);

#endif // ULTRASCHALL_SENSOR_H
