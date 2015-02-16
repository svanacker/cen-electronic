#ifndef I2C_COMMON_H
#define I2C_COMMON_H

// forward declaration
struct I2cBus;
typedef struct I2cBus I2cBus;

/** Define the index of i2c port 1. */
#define I2C_BUS_PORT_1         1

/** Define the index of i2c port 2. */
#define I2C_BUS_PORT_2         2

/** Define the index of i2c port 3. */
#define I2C_BUS_PORT_3         3

/** Define the index of i2c port 4. */
#define I2C_BUS_PORT_4         4

/**
 * Defines the contract for an I2C.
 */
struct I2cBus {
    /** port Index. */
    unsigned portIndex;
};

#define NACK    0

/**
 * Indirection for IdleI2C() used to manage Simulation.
 */
void WaitI2C(I2cBus* i2cBus);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableStartI2C(I2cBus* i2cBus);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableStopI2C(I2cBus* i2cBus);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableAckI2C(I2cBus* i2cBus);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableNackI2C(I2cBus* i2cBus);

#endif

