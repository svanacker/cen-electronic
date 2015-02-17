#include "../i2cSlave.h"

#include "../../../../common/setup/32/clockConstants32.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/32/i2cCommon32.h"

#include <plib.h>
#include <peripheral/i2c.h>

unsigned char portableSlaveReadI2C(I2cBus* i2cBus) {
    if (i2cBus == NULL) {
        unsigned char result = SlaveReadI2C1();
        return result;
    }
    else {
        unsigned portIndex = i2cBus->portIndex;
        I2C_MODULE i2cModule = getI2C_MODULE(portIndex);
        unsigned char result = I2CGetByte(i2cModule);
        return result;
    }
}

void portableSlaveWriteI2C(I2cBus* i2cBus, unsigned char c) {
    if (i2cBus == NULL) {
        SlaveWriteI2C1(c);
    }
    else {
        unsigned portIndex = i2cBus->portIndex;
        if (portIndex == I2C_BUS_PORT_1) {
            I2C1TRN = c;               /* data transferred to I2C1TRN reg */
            I2C1CONbits.SCLREL = 1;    /* Release the clock */
        }
        else if (portIndex == I2C_BUS_PORT_2) {
            // TODO : Throw not Implemented
            // I2C2TRN = c;               /* data transferred to I2C1TRN reg */
            // I2C2CONbits.SCLREL = 1;    /* Release the clock */
        }
        else if (portIndex == I2C_BUS_PORT_3) {
            // TODO : Throw not Implemented
            // I2C3TRN = c;               /* data transferred to I2C1TRN reg */
            // I2C3CONbits.SCLREL = 1;    /* Release the clock */
        }
        else if (portIndex == I2C_BUS_PORT_4) {
            I2C4TRN = c;               /* data transferred to I2C1TRN reg */
            I2C4CONbits.SCLREL = 1;    /* Release the clock */
        }
    }
}

void portableSlaveClockRelease(I2cBus* i2cBus) {
    if (i2cBus == NULL) {
        I2C1CONbits.SCLREL = 1; // release the clock
    }
    else {
        unsigned portIndex = i2cBus->portIndex;
        I2C_MODULE i2cModule = getI2C_MODULE(portIndex);
        I2CSlaveClockRelease(i2cModule);
    }
}