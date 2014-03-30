#include "armDriver2012.h"
#include "armDeviceInterface2012.h"

#include "../../common/commons.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"


bool armDriver2012Up(int index) {
	OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_ARM_2012_UP);
    appendHex2(outputStream, index);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool armDriver2012Down(int index) {
	OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_ARM_2012_DOWN);
    appendHex2(outputStream, index);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}
