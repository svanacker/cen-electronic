#include "../i2cSlave.h"

#include "../../../../common/setup/32/clockConstants32.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/32/i2cCommon32.h"

#define _SUPPRESS_PLIB_WARNING
#include <plib.h>

void portableSlaveStartI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonStartI2C(i2cBusConnection);
}

void portableSlaveStopI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonStopI2C(i2cBusConnection);
}

void portableSlaveAckI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonAckI2C(i2cBusConnection);
}

void portableSlaveNackI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonNackI2C(i2cBusConnection);
}

unsigned char portableSlaveReadI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        unsigned char result = SlaveReadI2C1();
        return result;
    }
    else {
        unsigned portIndex = i2cBus->port;
        I2C_MODULE i2cModule = getI2C_MODULE(portIndex);
        unsigned char result = I2CGetByte(i2cModule);
        return result;
    }
}

void portableSlaveWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char c) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        SlaveWriteI2C1(c);
    }
    else {
        unsigned portIndex = i2cBus->port;
        if (portIndex == I2C_BUS_PORT_1) {
            I2C1TRN = c;               // data transferred to I2C1TRN reg
            I2C1CONbits.SCLREL = 1;    // Release the clock
        }
    #if defined _I2C2
        else if (portIndex == I2C_BUS_PORT_2) {
            I2C2TRN = c;               // data transferred to I2C1TRN reg
            I2C2CONbits.SCLREL = 1;    // Release the clock
        }
    #endif
    #if defined _I2C3
        else if (portIndex == I2C_BUS_PORT_3) {
            I2C3TRN = c;               // data transferred to I2C1TRN reg
            I2C3CONbits.SCLREL = 1;    // Release the clock
        }
    #endif
    #if defined _I2C4
        else if (portIndex == I2C_BUS_PORT_4) {
            I2C4TRN = c;               // data transferred to I2C1TRN reg
            I2C4CONbits.SCLREL = 1;    // Release the clock
        }
    }
    #endif
}

void portableSlaveClockRelease(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        I2C1CONbits.SCLREL = 1; // release the clock
    }
    else {
        unsigned portIndex = i2cBus->port;
        I2C_MODULE i2cModule = getI2C_MODULE(portIndex);
        I2CSlaveClockRelease(i2cModule);
    }
}