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
 * @return the response data containing the result of the invocation of the targetted device
 */
typedef void driverDataDispatcherTransmitDataFunction(struct DriverDataDispatcher* dispatcher,
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
    int transmitMode;
    /** A name for debug. */
    char* name;
	/** The address as char (for zigbee for example). */
	char* addressString;
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
 * Generalist method to send data from the Driver to the Device
 * Transmit the data to the device (via local or distant call).
 * @param requestBuffer the input buffer (device request)
 * @param responseBuffer the output buffer (device response which can be received locally or via remote 
 * I2C / UART ...)
 * @param dataToTransferCount number of bytes which must be sent
 * @param dataToReceiveCount number of bytes which must be received
 * @return the response data containing the result of the invocation of the targetted device
 */
void transmitDriverData(int transmitMode,
				        int address,
				        Buffer* requestBuffer,
				        Buffer* responseBuffer,
				        int dataToTransferCount,
				        int dataToReceiveCount
				        );

/**
 * Handle data which are notification (and not direct response) from dispatcher.
 * @param dispatcher the dispatcher from which we try to handle notification.
 */
BOOL handleNotificationFromDispatcher(DriverDataDispatcher* dispatcher);

#endif
