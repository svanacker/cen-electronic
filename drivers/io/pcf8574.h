/**
 * Encapsulates the PCF8574
 * @author svanacker
 * @version 06/05/2007
 */
#ifndef PCF8574_H
#define PCF8574_H

#include "../../common/io/outputStream.h"

// base control address for PCF8574
#define PCF8574_BASE_ADDRESS 0x40

// base control address for PCF8574A
#define PCF8574AP_BASE_ADDRESS 0x70

/**
 * Check for presence of specific PCF8574 device.
 * @param addr either PCF8574_BASE_ADDRESS or PCF8574AP_BASE_ADDRESS
 * @param devAddr between 0 and 7
 * @return True if device exists on bus
 */
char isPCF8574Present(unsigned char addr, unsigned char devAddr );

/**
 * Set PCF8574 outputs (pins masked with dirs value).
 * @param addr either PCF8574_BASE_ADDRESS or PCF8574AP_BASE_ADDRESS
 * @param devAddr between 0 and 7
 * @param outData Data to write to PCF8574 port
 */
void writePCF8574(unsigned char addr, unsigned char devAddr, unsigned char outData, unsigned char dirs);

/**
 * Get PCF8574 inputs (pins masked with dirs value)
 * @param addr either PCF8574_BASE_ADDRESS or PCF8574AP_BASE_ADDRESS
 * @param devAddr between 0 and 7
 * @return Data from PCF8574 inputs
 */
unsigned char readPCF8574(unsigned char addr, unsigned char devAddr, unsigned char dirs);

/**
* Test functions for PCF.
*/
void testPCF8574(OutputStream* outputStream);

#endif
