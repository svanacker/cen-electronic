#ifndef I2C_BUS_CONNECTION_LIST_H
#define I2C_BUS_CONNECTION_LIST_H

#include <stdbool.h>

#include "i2cCommon.h"

/**
 * The struct defining a list of i2c Bus Connection.
 */
typedef struct {
    /** An array of pointer on i2cBusConnection Descriptor. */
    I2cBusConnection(*busConnectionArray)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;
} I2cBusConnectionList;

/**
 * Initializes a list of I2cBusConnection.
 * @param busConnectionArray the array presized with I2cBusConnection
 * @param busConnectionListSize the size of the array of I2cBusConnection
 */
void initI2cBusConnectionList(I2cBusConnection(*busConnectionArray)[], unsigned char busConnectionListSize);

/**
 * Return the dispatcher list.
 * @return the dispatcher list.
 */
I2cBusConnectionList* getI2cBusConnectionList();

/**
 * Add an i2cBusConnection to the list.
 * @param i2cBus the i2cBus linked to the connection
 * @param slaveAddress the address corresponding to the connection
 * @param defaultInitConnection if we call the default connection method or NOT. If not, you will must call explicitely an init method to the connection
 */
I2cBusConnection* addI2cBusConnection(I2cBus* i2cBus, unsigned char slaveAddress, bool defaultInitConnection);

/**
 * Retrieve an existing i2cBusConnection, and if none, create it and returns it.
 * @param i2cBus
 * @param i2cSlaveAddress
 * @param defaultInitConnection
 * @return 
 */
I2cBusConnection* getOrCreateI2cBusConnection(I2cBus* i2cBus, unsigned char i2cSlaveAddress, bool defaultInitConnection);

/**
 * Get a i2cBusConnection by his index.
 * @param index the index of the i2cBusConnection to get.
 * @return a i2cBusConnection at the right index.
 */
I2cBusConnection* getI2cBusConnectionByIndex(int index);

/**
 * Find the i2cBusConnection by his type in the list.
 * @param slaveAddress the address corresponding to the busConnectionAddress 
 * @return the i2cBusConnection, NULL if not found.
 */
I2cBusConnection* getI2cBusConnectionBySlaveAddress(unsigned char slaveAddress);

/**
 * Get the size of the i2c Bus Connection List.
 * @return the size of the i2c Bus Connection List.
 */
int getI2cBusConnectionListCount(void);

#endif
