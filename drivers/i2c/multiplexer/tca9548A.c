#include "tca9548A.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/delay/cenDelay.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/master/i2cMaster.h"

#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

void tca9548A_setChannel(I2cBusConnection* i2cBusConnection, unsigned char channels) {
    portableMasterWaitSendI2C(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, channels);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStopI2C(i2cBusConnection);
}

unsigned char tca9548A_getChannel(I2cBusConnection* i2cBusConnection) {
    portableMasterWaitSendI2C(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    
    // send read address (bit zero is set)
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 1);
    WaitI2cBusConnection(i2cBusConnection);

    // Read the register
    unsigned char raw = portableMasterReadI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterNackI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    
    return raw;
}
