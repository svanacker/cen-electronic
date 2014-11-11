#include "driverDataDispatcherList.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

// DEBUG

/**
 * Returns the transmit Mode as string.
 * @param transmitMode the transmit Mode
 * @return a string describing the transmit Mode
 */
char* getDispatcherTransmitModeAsString(int transmitMode) {
    switch (transmitMode) {
        case TRANSMIT_LOCAL : return "TRANSMIT_LOCAL";
        case TRANSMIT_UART : return "TRANSMIT_UART";
        case TRANSMIT_I2C : return "TRANSMIT_I2C";
        case TRANSMIT_ZIGBEE : return "TRANSMIT_ZIGBEE";
        default : return "TRANSMIT_???";
    }
}

void printDriverDataDispatcher(OutputStream* outputStream, DriverDataDispatcher* dispatcher) {
    appendString(outputStream, "dispatcher=");
    appendString(outputStream, dispatcher->name);
    appendString(outputStream, ", transmitMode=");
    int transmitMode = dispatcher->transmitMode;
    appendString(outputStream, getDispatcherTransmitModeAsString(transmitMode));
    appendString(outputStream, ", address=0x");
    appendHex2(outputStream, dispatcher->address);
    appendCRLF(outputStream);
}

void printDriverDataDispatcherList(OutputStream* outputStream, DriverDataDispatcherList* dispatcherList) {
    int i;
    for (i = 0; i < dispatcherList->size; i++) {
        DriverDataDispatcher* dispatcher = dispatcherList->dispatchers[i];    
        printDriverDataDispatcher(outputStream, dispatcher);
    }
}
