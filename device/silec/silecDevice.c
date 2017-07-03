#include <stdbool.h>
#include <stdlib.h>

#include "silecDevice.h"
#include "silecDeviceInterface.h"

#include "../../common/silec/silec.h"
#include "../../common/error/error.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/math/bcdUtils.h"

#include "../../device/device.h"

static Silec* silec;

void _deviceSilecCheckInitialized() {
    if (silec == NULL) {
        writeError(SILEC_NULL);
    }
    if (!isSilecInitialized(silec)) {
        writeError(SILEC_NOT_INITIALIZED);
    }
}

void deviceSilecInit(void) {
    _deviceSilecCheckInitialized();
    silec->initSILEC(silec);
}

void deviceSilecShutDown(void) {
}

bool isSilecDeviceOk(void) {
    return true;
}

void deviceSilecHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    _deviceSilecCheckInitialized();
    if (header == WRITE_FREQUENCY_SILEC) {     
        SilecData* silecData = &(silec->silecData);
        ackCommand(outputStream, SILEC_DEVICE_HEADER, WRITE_FREQUENCY_SILEC);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSilecInit,
    .deviceShutDown = &deviceSilecShutDown,
    .deviceIsOk = &isSilecDeviceOk,
    .deviceHandleRawData = &deviceSilecHandleRawData,
};

DeviceDescriptor* getSilecDeviceDescriptor(Silec* silecParam) {
    silec = silecParam;
    return &descriptor;
}

