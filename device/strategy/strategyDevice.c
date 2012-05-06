#include "strategyDevice.h"
#include "strategyDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"


// DEVICE INTERFACE

void initStrategy(void) {
    
}

void stopStrategy(void) {

}

unsigned int isStrategyDeviceOk(void) {
    return TRUE;
}

void deviceStrategyHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
	// TODO
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initStrategy,
    .deviceShutDown = &stopStrategy,
    .deviceIsOk = &isStrategyDeviceOk,
    .deviceHandleRawData = &deviceStrategyHandleRawData,
};

DeviceDescriptor* getStrategyDeviceDescriptor() {
    return &descriptor;
}
