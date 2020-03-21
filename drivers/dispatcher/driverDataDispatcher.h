#ifndef DRIVER_DATA_DISPATCHER_H
#define DRIVER_DATA_DISPATCHER_H

#include "../../drivers/driver.h"
#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

/**
 * AVAILABLE DOCUMENTATION : dispatcher.vpp
 */

// forward declaration
struct DriverDataDispatcher;

/**
 * Transmits driver data to the device over the specified medium.
 * @param requestBuffer the input buffer (device request)
 * @param responseBuffer the output buffer (device response which can be received locally or via remote 
 * I2C / UART ...)
 * @param dataToTransferCount number of bytes which must be sent
 * @param dataToReceiveCount number of bytes which must be received
 * @return true if the transmitDataFunction was ok, false else
 */
typedef bool driverDataDispatcherTransmitDataFunction(struct DriverDataDispatcher* dispatcher,
        Buffer* requestBuffer,
        Buffer* responseBuffer,
        int dataToTransferCount,
        int dataToReceiveCount
        );

/**
 * Structure defining a driverDataDispatcher with his associated transmitMode.
 */
typedef struct DriverDataDispatcher {
    /** The corresponding Transmit mode */
    TransmitMode transmitMode;
    /** A name for debug. */
    const char* name;
    /** The address as char (for zigbee for example). */
    const char* addressString;
    /** The address (only for remote transmitMode). In case of addressString, address contains a checksum of addressString. */
    int address;
    /** inputStream (can be null). */
    InputStream* inputStream;
    /** outputStream (can be null). */
    OutputStream* outputStream;
    /** the function which is able to transmit the data from the driver to the device. */
    driverDataDispatcherTransmitDataFunction* driverDataDispatcherTransmitData;
} DriverDataDispatcher;

/**
 * Handle data which are notification (and not direct response) from dispatcher.
 * @param dispatcher the dispatcher from which we try to handle notification.
 * @return true if there is a notification, false else
 */
bool handleNotificationFromDispatcher(DriverDataDispatcher* dispatcher);

#endif
