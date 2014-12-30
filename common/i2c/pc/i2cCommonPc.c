#include "../../../common/commons.h"

#include "../i2cCommon.h"
#include "../master/pc/i2cMasterPc.h"
#include "../master/pc/i2cMasterSetupPc.h"
#include "../../../common/pc/pipe/pipeServerHelper.h"
#include "../../../common/pc/pipe/pipeClientHelper.h"

#include <Windows.h>

void WaitI2C() {
    // Nothing to do
}

void portableStartI2C() {
    // TODO : Check whether it's the master or the client which talks
    // Send STX special code (see ASCII table)
    HANDLE pipe = getMasterPipeHandle();
    writeCharToPipe(pipe, ASCII_STX);
}

void portableStopI2C() {
    // TODO : Check whether it's the master or the client which talks
    // Send ETX special code (see ASCII table)
    HANDLE pipe = getMasterPipeHandle();
    writeCharToPipe(pipe, ASCII_ETX);
}

void portableAckI2C() {
    // TODO : Check whether it's the master or the client which talks
    // Send ACK special code (see ASCII table)
    HANDLE pipe = getMasterPipeHandle();
    // writeCharToPipe(pipe, ASCII_ACK);
}

void portableNackI2C() {
   
}