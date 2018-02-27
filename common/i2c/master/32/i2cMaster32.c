// FOR MPLAB.X
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "../i2cMaster.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/32/i2cCommon32.h"

void portableMasterStartI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonStartI2C(i2cBusConnection);
}

void portableMasterStopI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonStopI2C(i2cBusConnection);
}

void portableMasterAckI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonAckI2C(i2cBusConnection);
}

void portableMasterNackI2C(I2cBusConnection* i2cBusConnection) {
    portableCommonNackI2C(i2cBusConnection);
}

unsigned int portableMasterWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char data) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        return MasterWriteI2C1(data);
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->port);
        return I2CSendByte(i2cModule, data);
    }
}

unsigned char portableMasterReadI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        return MasterReadI2C1();
    }
    else {
        unsigned portIndex = i2cBus->port;
        if (portIndex == I2C_BUS_PORT_1) {
            I2C1CONbits.RCEN = 1;
            while (I2C1CONbits.RCEN);
            I2C1STATbits.I2COV = 0;
            return(I2C1RCV);
        }
    #if defined _I2C2
        else if (portIndex == I2C_BUS_PORT_2) {
            TODO : Throw Not Implemented
            I2C2CONbits.RCEN = 1;
            while (I2C2CONbits.RCEN);
            I2C2STATbits.I2COV = 0;
            return (I2C2RCV);
        }
    #endif
    #if defined _I2C3
        else if (portIndex == I2C_BUS_PORT_3) {
            I2C3CONbits.RCEN = 1;
            while(I2C3CONbits.RCEN);
            I2C3STATbits.I2COV = 0;
            return (I2C3RCV);
        }
    #endif
    #if defined _I2C4
        else if (portIndex == I2C_BUS_PORT_4) {
            I2C4CONbits.RCEN = 1;
            while(I2C4CONbits.RCEN);
            I2C4STATbits.I2COV = 0;
            return (I2C4RCV);
        }
    #endif
    }
    return 0;
}

void portableMasterCloseI2C(I2cBus* i2cBus) {
    if (i2cBus == NULL) {
        CloseI2C1();
    }
    else {
        unsigned portIndex = i2cBus->port;
        if (portIndex == I2C_BUS_PORT_1) {
            CloseI2C1();
        }
    #if defined _I2C2
        else if (portIndex == I2C_BUS_PORT_2) {
            CloseI2C2();
        }
    #endif
    #if defined _I2C3
        else if (portIndex == I2C_BUS_PORT_3) {
            // TODO : Throw Not Implemented
            // I2C3CONCLR = _I2C3CON_ON_MASK,
            // DisableIntSI2C3,
            // DisableIntMI2C3,
            // DisableIntBI2C3
        }
    #endif
    #if defined _I2C4
        else if (portIndex == I2C_BUS_PORT_4) {
            // TODO : Throw Not Implemented
            // I2C4CONCLR = _I2C4CON_ON_MASK,
            // mI2C4SIntEnable(0),
            // mI2C4MIntEnable(0),
            // mI2C1BIntEnable(0)
        }
    }
    #endif
}

void portableMasterWaitSendI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        while (I2C1CONbits.SEN) {
        }
        return;
    }
    else {
        unsigned portIndex = i2cBus->port;

            if (portIndex == I2C_BUS_PORT_1) {
                while (I2C1CONbits.SEN) {
                }
            }
        #if defined _I2C2
            else if (portIndex == I2C_BUS_PORT_2) {
                while (I2C2CONbits.SEN) {
                }
            }
        #endif
        #if defined _I2C3
            else if (portIndex == I2C_BUS_PORT_3) {
                while (I2C3CONbits.SEN) {
                }
            }
        #endif
        #if defined _I2C4
            else if (portIndex == I2C_BUS_PORT_4) {
                while (I2C4CONbits.SEN) {
                }
                return;
            }
        #endif
    }
}
