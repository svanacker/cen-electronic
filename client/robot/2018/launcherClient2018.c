#include "launcherClient2018.h"

#include "../../../common/commons.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../device/deviceConstants.h"

#include "../../../drivers/driverList.h"
#include "../../../drivers/driverTransmitter.h"

#include "../../../robot/2018/launcherDeviceInterface2018.h"

bool clientGlobalTest(void) {
    // LEFT TEST
    bool result = clientLightOn2018(LAUNCHER_LEFT_INDEX);
    if (!result) {
        return false;
    }
    delaymSec(1000);
    result = clientDistributor2018CleanNext(LAUNCHER_LEFT_INDEX);
    if (!result) {
        return false;
    }
    delaymSec(1000);
    result = clientLaunch2018(LAUNCHER_LEFT_INDEX, LAUNCHER_PREPARE_ON);
    if (!result) {
        return false;
    }
    delaymSec(1000);
    result = clientLaunch2018(LAUNCHER_LEFT_INDEX, LAUNCHER_LAUNCH);
    if (!result) {
        return false;
    }
    delaymSec(1000);

    // RIGHT TEST
    result = clientLightOn2018(LAUNCHER_RIGHT_INDEX);
    if (!result) {
        return false;
    }
    delaymSec(1000);
    result = clientDistributor2018CleanNext(LAUNCHER_RIGHT_INDEX);
    if (!result) {
        return false;
    }
    delaymSec(1000);
    result = clientLaunch2018(LAUNCHER_RIGHT_INDEX, LAUNCHER_PREPARE_ON);
    if (!result) {
        return false;
    }
    delaymSec(1000);
    result = clientLaunch2018(LAUNCHER_RIGHT_INDEX, LAUNCHER_LAUNCH);
    if (!result) {
        return false;
    }
    delaymSec(1000);

    // EJECTOR
    result = clientDistributor2018EjectDirty();
    return result;
}

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

bool clientDistributor2018CleanNext(int direction) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, LAUNCHER_2018_DEVICE_HEADER);
    append(outputStream, DISTRIBUTOR_LOAD_NEXT_BALL_COMMAND);
    appendHex2(outputStream, direction);

    bool result = transmitFromDriverRequestBuffer();

    // Read the distance of detection, but we don't care about
    readHex2(inputStream);

    return result;
}

bool clientDistributor2018EjectDirty(void) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, LAUNCHER_2018_DEVICE_HEADER);
    append(outputStream, DISTRIBUTOR_EJECT_DIRTY_BALL_COMMAND);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}