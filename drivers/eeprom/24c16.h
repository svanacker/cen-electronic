#ifndef ST24C16_H
#define ST24C16_H

#include "../../common/eeprom/eeprom.h"
#include "../../common/i2c/i2cCommon.h"

/**
 * Initialize a type of eeprom : 24C16
 * @param eeprom a pointer of eeprom type.
 * @param i2cBusConnection the I2C bus connection for the eeprom
 */
void init24C16Eeprom(Eeprom* eeprom_, I2cBusConnection* i2cBusConnection);

#endif
