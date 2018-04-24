#include "launcherClient2018.h"

#include "../../../common/commons.h"
#include "../../../common/io/printWriter.h"

#include "../../../device/deviceConstants.h"

#include "../../../drivers/driverList.h"
#include "../../../drivers/driverTransmitter.h"

#include "../../../robot/2018/launcherDeviceInterface2018.h"

bool clientLightOn2018(int launcherIndex) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, LAUNCHER_2018_DEVICE_HEADER);
    append(outputStream, LAUNCHER_LIGHT_ON_SERVO_MOVE_COMMAND);
    appendHex2(outputStream, launcherIndex);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool clientLaunch2018(int launcherIndex, bool prepare) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, LAUNCHER_2018_DEVICE_HEADER);
    if (prepare) {
        append(outputStream, LAUNCHER_PREPARE_BALL_COMMAND);
        appendHex2(outputStream, launcherIndex);
    }
    else {
        append(outputStream, LAUNCHER_SEND_BALL_COMMAND);
        appendHex2(outputStream, launcherIndex);
    }
    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool clientDistributor2018CleanNext(int launcherIndex) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, LAUNCHER_2018_DEVICE_HEADER);
    append(outputStream, DISTRIBUTOR_NEXT_BALL_COMMAND);
    appendHex2(outputStream, launcherIndex);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool clientDistributor2018EjectDirty(void) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, LAUNCHER_2018_DEVICE_HEADER);
    append(outputStream, DISTRIBUTOR_EJECT_DIRTY_BALL_COMMAND);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}