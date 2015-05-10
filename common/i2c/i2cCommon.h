#ifndef I2C_COMMON_H
#define I2C_COMMON_H

#include <stdbool.h>

// forward declaration
struct I2cBus;
typedef struct I2cBus I2cBus;
struct I2cBusConnection;
typedef struct I2cBusConnection I2cBusConnection;

/** Define the index of i2c port 1. */
#define I2C_BUS_PORT_1         1

/** Define the index of i2c port 2. */
#define I2C_BUS_PORT_2         2

/** Define the index of i2c port 3. */
#define I2C_BUS_PORT_3         3

/** Define the index of i2c port 4. */
#define I2C_BUS_PORT_4         4

/**
 * Defines the contract for an I2C bus.
 * A bus can manage multiple Connection, but we make an unidirectional Link between I2CBus and I2CBusConnection.
 */
struct I2cBus {
    /** port Index. */
    unsigned char portIndex;
    // An untyped object (For example to have a pipe Handle in Windows)
    void* object;
};

/**
 * As an I2C manage several target, we need to encapsulates the information between a
 * master and a client with an object
 */
struct I2cBusConnection {
    // Link to the I2cBus
    I2cBus* i2cBus;
    // Address of the slave
    unsigned char i2cAddress;
    // If the connection is established (useful for Windows Emulation with Pipe)
    bool opened;
    // An untyped object (For example to have a pipe Handle in Windows)
    void* object;
};

#define NACK    0

/**
 * Initializes a wrapping structure around I2cBus.
 * @param portIndex the index of the port.
 */
void initI2cBus(I2cBus* i2cBus, unsigned char portIndex);

/**
 * Initializez a wrapping structure around a connection betweeen a master and a specific address.
 * @param i2cBusConnection the connection to initialize
 * @param i2cBus the underlying bus (shared by multiple connection).
 * @param slaveAddress the address of the slave
 */
void initI2cBusConnection(I2cBusConnection* i2cBusConnection, I2cBus* i2cBus, unsigned char slaveAddress);

/**
 * Indirection for IdleI2C() used to manage Simulation.
 */
void WaitI2C(I2cBus* i2cBus);

#endif

