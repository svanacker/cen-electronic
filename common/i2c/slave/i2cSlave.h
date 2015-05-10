#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/streamLink.h"

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableSlaveStartI2C(I2cBusConnection* i2cBusConnection);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableSlaveStopI2C(I2cBusConnection* i2cBusConnection);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableSlaveAckI2C(I2cBusConnection* i2cBusConnection);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableSlaveNackI2C(I2cBusConnection* i2cBusConnection);

/**
 * Store the stream Link for i2c interrupt.
 * @param aStreamLink the pointer on the streamLink which manage input and input on I2C link.
 */
void setI2cStreamLink(StreamLink* aStreamLink);

/**
 * Returns the stream link.
 * @return the stream link
 */
StreamLink* getI2cStreamLink(void);

/**
 * Portable Function which must be used to read the I2C Slave.
 * @return the read data
 */
unsigned char portableSlaveReadI2C(I2cBusConnection* i2cBusConnection);

/**
 * Portable Function which must be used to write from the I2C Slave to the Master.
 * @param c the data to write back to the master
 */
void portableSlaveWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char c);

/**
 * Portable Function which must be used to release a previously-held SCL clock line.
 */
void portableSlaveClockRelease(I2cBusConnection* i2cBusConnection);

#endif

