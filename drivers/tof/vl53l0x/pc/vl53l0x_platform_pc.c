/**
 * PIC 32 PORT of ARDUINO
 * Inspired from : https://github.com/adafruit/Adafruit_VL53L0X/blob/c5a73e09389740752771a67c8de9723b4c0ca477/src/platform/src/vl53l0x_i2c_comms.cpp
 * There is only to implement write multi to the I2C PIC32 library so that it works
 * because write/read on byte/word/dwork are simply mapped to write_multi / read_multi
 */
#include <stdlib.h>
#include <stdbool.h>
#include "../vl53l0x_types.h"
#include "../vl53l0x_api.h"

// PRIMITIVES

int32_t VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t  *pdata, int32_t count) {
    return VL53L0X_ERROR_NONE;
}

int32_t VL53L0X_read_multi(uint8_t deviceAddress,  uint8_t index, uint8_t  *pdata, int32_t count) {
  return VL53L0X_ERROR_NONE;
}
