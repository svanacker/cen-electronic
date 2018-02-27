#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include <stdlib.h>
#include <stdbool.h>

#include "i2cCommon32.h"

#include "../i2cCommon.h"

I2C_MODULE getI2C_MODULE(unsigned char portIndex) {
    if (portIndex == I2C_BUS_PORT_1) {
        return I2C1;
    }
#if defined _I2C2
    else if (portIndex == I2C_BUS_PORT_2) {
        return I2C2;
    }
#endif
#if defined _I2C3
    else if (portIndex == I2C_BUS_PORT_3) {
        return I2C3;
    }
#endif
#if defined _I2C4
    else if (portIndex == I2C_BUS_PORT_4) {
        return I2C4;
    }
#endif
    // TODO : Check
    return 0;
}

void WaitI2C(I2cBus* i2cBus) {
    if (i2cBus == NULL) {
        IdleI2C1();
    }
    else {
        enum I2cPort portIndex = i2cBus->port;
        if (portIndex == I2C_BUS_PORT_1) {
            while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RSEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
        }
    #if defined _I2C2
        else if (portIndex == I2C_BUS_PORT_2) {
            while(I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RSEN || I2C2CONbits.RCEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);
        }
    #endif
    #if defined _I2C3
        else if (portIndex == I2C_BUS_PORT_3) {
            while(I2C3CONbits.SEN || I2C3CONbits.PEN || I2C3CONbits.RSEN || I2C3CONbits.RCEN || I2C3CONbits.ACKEN || I2C3STATbits.TRSTAT);
        }
    #endif
    #if defined _I2C4
        else if (portIndex == I2C_BUS_PORT_4) {
            while(I2C4CONbits.SEN || I2C4CONbits.PEN || I2C4CONbits.RSEN || I2C4CONbits.RCEN || I2C4CONbits.ACKEN || I2C4STATbits.TRSTAT);
        }
    }
    #endif
}

void portableCommonStartI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    if (i2cBus == NULL) {
        StartI2C1();
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->port);
        I2CStart(i2cModule);
    }
}

void portableCommonStopI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    if (i2cBus == NULL) {
        StopI2C1();
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->port);
        I2CStop(i2cModule);
    }
}

void portableCommonAckI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    if (i2cBus == NULL) {
        AckI2C1();
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->port);
        I2CAcknowledgeByte(i2cModule, true);
    }
}

void portableCommonNackI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        NotAckI2C1();
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->port);
        I2CAcknowledgeByte(i2cModule, false);
    }
}
