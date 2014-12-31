#ifndef TRANSMIT_MODE_H
#define TRANSMIT_MODE_H

typedef int TransmitMode;

/**
 * Data will not be transferred, because the driver does not correspond to our communication standard
 * (Ex : For All Devantech Devices)
 */
#define TRANSMIT_NONE     -1

/**
 * Data will be transmitted in local.
 */
#define TRANSMIT_LOCAL     0

/**
 * Data will be transmitted via I2C.
 */
#define TRANSMIT_I2C     1

/**
 * Data will be transmitted via UART.
 */
#define TRANSMIT_UART     2

/**
 * Data will be transmitted via ZIGBEE.
 */
#define TRANSMIT_ZIGBEE   3

/**
 * Returns the transmit Mode as string.
 * @param transmitMode the transmit Mode
 * @return a string describing the transmit Mode
 */
const char* getTransmitModeAsString(TransmitMode transmitMode);

#endif
