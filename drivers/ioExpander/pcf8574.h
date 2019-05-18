#ifndef PCF8574_H
#define PCF8574_H

/**
 * Encapsulates the PCF8574
 * @author svanacker
 * @version 06/05/2007
 */

#include "../../common/io/outputStream.h"
#include "../../common/i2c/i2cCommon.h"

/**
 * Check for presence of specific PCF8574 device.
 * @param i2cConnection on I2c bus (Simulates POO Programming)
 * @return True if device exists on bus
 */
unsigned char isPCF8574Present(I2cBusConnection* i2cConnection);

/**
 * Set PCF8574 outputs (pins masked with dirs value).
 * @param pointer on I2c bus (Simulates POO Programming)
 * @param outData Data to write to PCF8574 port
 */
void writePCF8574(I2cBusConnection* i2cConnection, unsigned char outData);

/**
 * Get PCF8574 inputs (pins masked with dirs value)
 * @return Data from PCF8574 inputs
 */
unsigned char readPCF8574(I2cBusConnection* i2cConnection);

#endif
