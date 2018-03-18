/**
 * PIC 32 PORT of ARDUINO
 * Inspired from : https://github.com/adafruit/Adafruit_VL53L0X/blob/c5a73e09389740752771a67c8de9723b4c0ca477/src/platform/src/vl53l0x_i2c_comms.cpp
 * There is only to implement write multi to the I2C PIC32 library so that it works
 * because write/read on byte/word/dwork are simply mapped to write_multi / read_multi
 */
#include <stdlib.h>
#include <stdbool.h>
#include "vl53l0x_types.h"
#include "vl53l0x_api.h"

#include "../../../common/log/logger.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#define VL53L0X_DEBUG    true

// WRITE

int32_t VL53L0X_write_byte(uint8_t deviceAddress,  uint8_t index, uint8_t   data) {
    return VL53L0X_write_multi(deviceAddress, index, &data, 1);
}


int32_t VL53L0X_write_word(uint8_t deviceAddress,  uint8_t index, uint16_t  data) {
    uint8_t buff[2];
  buff[1] = data & 0xFF;
  buff[0] = data >> 8;
  return VL53L0X_write_multi(deviceAddress, index, buff, 2);
}

int32_t VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t  data) {
    uint8_t buff[4];

  buff[3] = data & 0xFF;
  buff[2] = data >> 8;
  buff[1] = data >> 16;
  buff[0] = data >> 24;

  return VL53L0X_write_multi(deviceAddress, index, buff, 4);
}

// READ

int32_t VL53L0X_read_byte(uint8_t deviceAddress,  uint8_t index, uint8_t  *data) {
    return VL53L0X_read_multi(deviceAddress, index, data, 1);
}

int32_t VL53L0X_read_word(uint8_t deviceAddress,  uint8_t index, uint16_t *data) {
  uint8_t buff[2];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 2);

  uint16_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  *data = tmp;

  return r;
}

int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data) {
  uint8_t buff[4];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 4);

  uint32_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  tmp <<= 8;
  tmp |= buff[2];
  tmp <<= 8;
  tmp |= buff[3];

  *data = tmp;

  return r;
}

