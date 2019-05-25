#ifndef I2C_BUS_LIST_H
#define I2C_BUS_LIST_H

#include <stdbool.h>

#include "i2cCommon.h"

/**
 * The struct defining a list of i2c Bus.
 */
typedef struct {
    /** An array of pointer on i2cBus Descriptor. */
    I2cBus(*busArray)[];
    /** the size of the list. */
    unsigned int size;
    /** the max size of the list. */
    unsigned int maxSize;
} I2cBusList;

/**
 * Initializes a list of I2cBus.
 * @param busArray the array presized with I2cBus
 * @param busListSize the size of the array of I2cBus
 */
void initI2cBusList(I2cBus(*busArray)[], unsigned int busListSize);

/**
 * Return the dispatcher list.
 * @return the dispatcher list.
 */
I2cBusList* getI2cBusList();

/**
 * Add an i2cBus to the list.
 */
I2cBus* addI2cBus(enum I2cBusType i2cBusType, enum I2cPort i2cPort);

/**
 * Get a i2cBus by his index.
 * @param index the index of the i2cBus to get.
 * @return a i2cBus at the right index.
 */
I2cBus* getI2cBusByIndex(unsigned int index);

/**
 * Find the i2cBus by his type in the list.
 * @param i2cPort the port type that we search 
 * @return the i2cBus, NULL if not found.
 */
I2cBus* getI2cBusByPortType(enum I2cPort i2cPort);

/**
 * Get the size of the i2c Bus List.
 * @return the size of the i2c Bus List.
 */
int getI2cBusListCount(void);

#endif
