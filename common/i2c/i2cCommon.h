#ifndef I2C_COMMON_H
#define I2C_COMMON_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"

#define I2C_MAX_INSTRUCTION_COUNT_WHILE              10000

// forward declaration
struct I2cBus;
typedef struct I2cBus I2cBus;
struct I2cBusConnection;
typedef struct I2cBusConnection I2cBusConnection;

/**
 * Encapsulate which I2C Port we use (4 on PIC32)
 */
enum I2cPort {
    /** To avoid to have a bad value. */
    I2C_BUS_PORT_UNKOWN = 0,

    /** Define the index of i2c port 1. */
    I2C_BUS_PORT_1 = 1,

    /** Define the index of i2c port 2. */
    I2C_BUS_PORT_2 = 2,

    /** Define the index of i2c port 3. */
    I2C_BUS_PORT_3 = 3,

    /** Define the index of i2c port 4. */
    I2C_BUS_PORT_4 = 4
};

/** 
 * Defines if the Bus is a MASTER or SLAVE Type !
 */
enum I2cBusType {
    /** Indicates that we don't know the type of I2C. */
    I2C_BUS_TYPE_UNKNOWN = 0,

    /** The enum which indicates that the I2C Bus is a Master Bus ! */
    I2C_BUS_TYPE_MASTER = 1,

    /** The enum which indicates that the I2C Bus is a Slave Bus ! */
    I2C_BUS_TYPE_SLAVE = 2
};

/**
 * Defines the contract for an I2C bus.
 * A bus can manage multiple Connection, but we make an unidirectional Link between I2CBus and I2CBusConnection.
 */
struct I2cBus {
    /** Master or Slave Bus. */
    enum I2cBusType busType;
    /** port Index. */
    enum I2cPort port;
    /** Indicates if the Port is already initialized. */
    bool initialized;
    /** Indicates the error if any on the i2cBus */
    unsigned int error;
    // Configuration (PIC Internal use)
    unsigned int config;
    // An untyped object (For example to store a structure referencing the pipe Handle in Windows)
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
    // The first error on connection if any, useful to get information after 
    // a troubleshoot
    unsigned int error;
    // An untyped object (to store for PC : I2cSlaveBusConnectionPc)
    void* object;
};

#define NACK    0

/**
 * Initializes a wrapping structure around I2cBus.
 * @param portIndex the index of the port.
 */
void initI2cBus(I2cBus* i2cBus, enum I2cBusType i2cBusType, enum I2cPort i2cPort);

/**
 * Initialize a wrapping structure around a connection betweeen a master and a specific address.
 * @param i2cBusConnection the connection to initialize
 * @param i2cBus the underlying bus (shared by multiple connection).
 * @param slaveAddress the address of the slave
 */
void initI2cBusConnection(I2cBusConnection* i2cBusConnection, I2cBus* i2cBus, unsigned char slaveAddress);

// COMMON FUNCTION (SLAVE / MASTER)

/**
 * Indirection for IdleI2C() used to manage Simulation.
 */
void WaitI2C(I2cBus* i2cBus);

/**
 * Indirection for WaitI2CBus but with more detailled information (I2C Address)
 * to detect the problems.
 * @param i2cBusConnection
 */
void WaitI2cBusConnection(I2cBusConnection* i2cBusConnection);

// CHECK FUNCTIONS
bool checkI2cBusConnectionNotNull(I2cBusConnection* i2cBusConnection);
bool checkI2cBusNotNull(I2cBus* i2cBus);
bool checkI2cBus(I2cBus* i2cBus);

#endif

