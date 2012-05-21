#include "driver.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

BOOL driverInit(const DriverDescriptor* driverDescriptor) {
    BOOL result = driverDescriptor->driverInit();
    const char* driverName = driverDescriptor->driverGetName();

    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendString(outputStream, "DRIVER :");
  
	appendString(outputStream, driverName);

    return result;
}

void driverShutDown(const DriverDescriptor *driverDescriptor) {
    driverDescriptor->driverShutDown();
}
