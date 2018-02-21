#include "launcherDevice2018.h"

#include "launcherDeviceInterface2018.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../main/meca1/mechanicalBoard1.h"


void launcher2018(int launcherIndex) {
    // TODO : launch motors
}

void deviceLauncher2018Init(void) {

}

void deviceLauncher2018ShutDown(void) {

}

bool deviceLauncher2018IsOk(void) {
    return true;
}

void deviceLauncher2018HandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == LAUNCHER_BALL_COMMAND) {
        int launcherIndex = readHex2(inputStream);
        launcher2018(launcherIndex);
        appendAck(outputStream);
        append(outputStream, LAUNCHER_BALL_COMMAND);
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLauncher2018Init,
    .deviceShutDown = &deviceLauncher2018ShutDown,
    .deviceIsOk = &deviceLauncher2018IsOk,
    .deviceHandleRawData = &deviceLauncher2018HandleRawData,
};

DeviceDescriptor* getLauncher2018DeviceDescriptor() {
    return &descriptor;
}
