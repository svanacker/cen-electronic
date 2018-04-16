#include "launcherClient2018.h"
#include "launcherDeviceInterface2018.h"

#include "../../common/commons.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

/*
bool launcherClient2018(int index) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, LAUNCHER_2018_DEVICE_HEADER);
    append(outputStream, LAUNCHER_BALL_COMMAND);
    appendHex2(outputStream, index);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}
*/