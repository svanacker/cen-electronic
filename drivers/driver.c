#include "driver.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

BOOL driverInit(const DriverDescriptor* driverDescriptor) {
    BOOL result = driverDescriptor->driverInit();
    const char* driverName = driverDescriptor->driverGetName();
//    unsigned int driverRevision = driverDescriptor->driverGetSoftwareRevision();

    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendString(outputStream, "DRIVER :");
  
	appendString(outputStream, driverName);

	/*
    append(outputStream, '(');
    appendDec(outputStream, driverRevision);
    append(outputStream, ')');
    appendCRLF(outputStream);
	*/

    return result;
}

void driverShutDown(const DriverDescriptor *driverDescriptor) {
    driverDescriptor->driverShutDown();
}
