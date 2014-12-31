#include <i2c.h>

#include "../i2cMaster.h"
#include "../../../../common/i2c/i2cCommon.h"

unsigned int portableMasterWriteI2C(unsigned char data) {
    return MasterWriteI2C(data);
}

unsigned char portableMasterReadI2C() {
    return MasterReadI2C();
}

void portableCloseI2C() {
    CloseI2C();
}

void portableMasterWaitSendI2C( void ) {
    while (I2CCONbits.SEN) {
    
    }
}
