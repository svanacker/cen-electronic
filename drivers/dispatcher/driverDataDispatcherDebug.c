#include "driverDataDispatcherList.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

// DEBUG

void printDriverDataDispatcher(OutputStream* outputStream, DriverDataDispatcher* dispatcher) {
    appendString(outputStream, "dispatcher=");
    appendString(outputStream, dispatcher->name);
    appendString(outputStream, ", transmitMode=");
    appendDec(outputStream, dispatcher->transmitMode);
    appendString(outputStream, ", address=");
    appendDec(outputStream, dispatcher->address);
    appendCRLF(outputStream);
}

void printDriverDataDispatcherList(OutputStream* outputStream, DriverDataDispatcherList* dispatcherList) {
    int i;
    for (i = 0; i < dispatcherList->size; i++) {
        DriverDataDispatcher* dispatcher = dispatcherList->dispatchers[i];    
        printDriverDataDispatcher(outputStream, dispatcher);
    }
}
