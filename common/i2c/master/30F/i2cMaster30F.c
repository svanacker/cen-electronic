#include <i2c.h>

#include "../i2cMaster.h"
#include "../../../../common/i2c/i2cCommon.h"

unsigned int portableMasterWriteI2C(I2cBus* i2cBus, unsigned char data) {
    return MasterWriteI2C(data);
}

unsigned char portableMasterReadI2C(I2cBus* i2cBus) {
    return MasterReadI2C();
}

void portableCloseI2C(I2cBus* i2cBus) {
    CloseI2C();
}

void portableMasterWaitSendI2C(I2cBus* i2cBus) {
    while (I2CCONbits.SEN) {
    
    }
}
