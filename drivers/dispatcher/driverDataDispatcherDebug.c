#include "driverDataDispatcherList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../device/transmitMode.h"

// DEBUG

void printDriverDataDispatcher(OutputStream* outputStream, DriverDataDispatcher* dispatcher) {
    appendString(outputStream, "dispatcher=");
    appendString(outputStream, dispatcher->name);
    appendString(outputStream, ", transmitMode=");
    TransmitMode transmitMode = dispatcher->transmitMode;
	appendDec(outputStream, transmitMode);
    append(outputStream, '(');
    appendString(outputStream, getTransmitModeAsString(transmitMode));
    append(outputStream, ')');
    appendString(outputStream, ", address=0x");
    appendHex2(outputStream, dispatcher->address);
    appendCRLF(outputStream);
}

void printDriverDataDispatcherList(OutputStream* outputStream, DriverDataDispatcherList* dispatcherList) {
    int i;
    for (i = 0; i < dispatcherList->size; i++) {
        DriverDataDispatcher* dispatcher = getDriverDataDispatcherByIndex(i);    
        printDriverDataDispatcher(outputStream, dispatcher);
    }
}
