#include "i2cMasterPc.h"

#include "i2cMasterSetupPc.h"
#include "../i2cMaster.h"

#include "../../../../common/i2c/i2cCommon.h"

#include "../../../../common/pc/pipe/pipeServerHelper.h"

unsigned int portableMasterWriteI2C(I2cBus* i2cBus, unsigned char data) {

    HANDLE pipe = getMasterPipeHandle();
    writeCharToPipe(pipe, data);
    return data;
}

unsigned char portableMasterReadI2C(I2cBus* i2cBus) {
    // TODO : Find the right Address
    HANDLE pipe = getSlavePipeHandle(0x00);
    
    unsigned char result = readCharFromPipe(pipe);
    
    return result;
}

void portableMasterWaitSendI2C(I2cBus* i2cBus) {
    // No Wait
}

void portableCloseI2C(I2cBus* i2cBus) {

}
