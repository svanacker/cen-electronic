#include <i2c.h>

#include "../i2cMaster.h"
#include "../../../../common/i2c/i2cCommon.h"

unsigned int portableMasterWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char data) {
    return MasterWriteI2C(data);
}

unsigned char portableMasterReadI2C(I2cBusConnection* i2cBusConnection) {
    return MasterReadI2C();
}

void portableMasterCloseI2C(I2cBus* i2cBus) {
    CloseI2C();
}

void portableMasterWaitSendI2C(I2cBusConnection* i2cBusConnection) {
    while (I2CCONbits.SEN) {
    
    }
}
