#ifndef I2C_COMMON_H
#define I2C_COMMON_H

// forward declaration
struct I2c;
typedef struct I2c I2c;

/** Define the index of i2c port 1. */
#define I2C_PORT_1         1

/** Define the index of i2c port 2. */
#define I2C_PORT_2         2

/** Define the index of i2c port 3. */
#define I2C_PORT_3         3

/** Define the index of i2c port 4. */
#define I2C_PORT_4         4

/**
 * Defines the contract for an I2C.
 */
struct I2c {
    /** port Index. */
    unsigned portIndex;
};

#define NACK    0

/**
 * Indirection for IdleI2C() used to manage Simulation.
 */
void WaitI2C();

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
// void portableStartI2C(I2c* i2c);
void portableStartI2C();

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableStopI2C();

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableAckI2C();

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableNackI2C();

#endif

