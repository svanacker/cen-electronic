#include <stdlib.h>
#include "systemDriver.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/system/systemDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../drivers/dispatcher/driverDataDispatcher.h"
#include "../../drivers/dispatcher/driverDataDispatcherList.h"

bool pingDriverDataDispatcher(DriverDataDispatcher* dispatcher) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_PING);

    // TODO : PING does only with one BOARD !
    bool result = transmitFromDriverRequestBuffer(/*dispatcher*/);
    return result;
}

void pingDriverDataDispatcherList(OutputStream* debugOutputStream) {
    int i;
    int size = getDriverDataDispatcherCount();
    for (i = 0; i < size; i++) {
        DriverDataDispatcher* dispatcher = getDriverDataDispatcherByIndex(i);
        if (dispatcher == NULL) {
            continue;
        }
        appendString(debugOutputStream, "PING ");
        appendString(debugOutputStream, dispatcher->name);

        bool result = pingDriverDataDispatcher(dispatcher);
        if (result) {
            appendString(debugOutputStream, ":OK");
        } else {
            appendString(debugOutputStream, ":KO");
        }
        appendCRLF(debugOutputStream);
    }
}
