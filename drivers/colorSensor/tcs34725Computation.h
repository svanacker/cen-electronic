#ifndef TCS34725_COMPUTATION_SENSOR_H
#define TCS34725_COMPUTATION_SENSOR_H

#include <stdint.h>

// COMPUTATION

uint16_t tcs34725_calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b);

uint16_t tcs34725_calculateLux(uint16_t r, uint16_t g, uint16_t b);

#endif