#include "stdlib.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"
#include "zigbeeDriverDataDispatcher.h"
#include "remoteDriverDataDispatcher.h"

// Device
#include "../../drivers/driver.h"
#include "../../drivers/jennic/jennic5139Driver.h"
#include "../../drivers/jennic/jennic5139EventParser.h"
#include "../../drivers/jennic/jennic5139OutputStream.h"
#include "../../drivers/jennic/jennic5139InputStream.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

/** Contains the buffer used to build data which will be included in the commandBuffer. */
static char asciiDataBufferArray[ZIGBEE_DRIVER_BUFFER_LENGTH];
static Buffer asciiDataBuffer;

/**
 * Add the i2c driver data dispatcher to the list.
 */
void addZigbeeDriverDataDispatcher(DriverDataDispatcher* dispatcher,
							        char* dispatcherName,
									InputStream* zigbeeInputStream,
							        OutputStream* zigbeeOutputStream,
									char* addressString) {
    dispatcher->transmitMode = TRANSMIT_ZIGBEE;
    dispatcher->name = dispatcherName;
	int address = stringChecksum(addressString);
    dispatcher->address = address;
	dispatcher->addressString = addressString;
    dispatcher->driverDataDispatcherTransmitData = remoteDriverDataDispatcherTransmit;

	// Init a buffer containing ascii Data to send to the command
	// Request : Zigbee Client -> Zigbee Server
	initBuffer(&asciiDataBuffer, &asciiDataBufferArray, ZIGBEE_DRIVER_BUFFER_LENGTH, "jennicAsciiDataToSendBuffer", "ASCII_DATA_TO_SEND");
	initZigbeeOutputStream(zigbeeOutputStream, &asciiDataBuffer, addressString);

	// Response : Zigbee Sender <- Zigbee Server
	initZigbeeInputStream(zigbeeInputStream, addressString);

    dispatcher->inputStream = zigbeeInputStream;
	dispatcher->outputStream = zigbeeOutputStream;

    // add the dispatcher to the list
    addDriverDataDispatcher(dispatcher);
}

