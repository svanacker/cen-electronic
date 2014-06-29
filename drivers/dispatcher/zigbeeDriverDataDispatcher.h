#ifndef ZIGBEE_DRIVER_DATA_DISPATCHER_H
#define ZIGBEE_DRIVER_DATA_DISPATCHER_H

#include "driverDataDispatcher.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

#define ZIGBEE_DRIVER_BUFFER_LENGTH        16

/**
* Add the zigbee driver data dispatcher to the list
*/
void addZigbeeDriverDataDispatcher(DriverDataDispatcher* dispatcher,
        char* dispatcherName,
        InputStream* zigbeeInputStream,
        OutputStream* zigbeeOutputStream,
        char* addressString
);

#endif
