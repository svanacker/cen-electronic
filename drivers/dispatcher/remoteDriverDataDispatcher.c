#include "stdlib.h"

#include "driverDataDispatcher.h"

// Device
#include "../../drivers/driver.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

/**
 * @private
 * Transmit the buffer through Remote OutputStream and fill Response Buffer through InputStream
 */
void remoteDriverDataDispatcherTransmit(DriverDataDispatcher* dispatcher,
                                        Buffer* requestBuffer,
                                        Buffer* responseBuffer,
                                        int dataToTransferCount,
                                        int dataToReceiveCount
                                        ) {
    InputStream* requestInputStream = getInputStream(requestBuffer);
    OutputStream* dispatcherOutputStream = dispatcher->outputStream;

    // Copy the buffer to the master outputStream
    copyInputToOutputStream(requestInputStream, dispatcherOutputStream, NULL, dataToTransferCount);

    // Copy the data from the slave
    InputStream* dispatcherInputStream = dispatcher->inputStream;
    OutputStream* responseOutputStream = getOutputStream(responseBuffer);

    // Wait the response : TODO : Have a smaller delay
    int dataReceived = 0;
    int counter = 0;
    delaymSec(2);

	/*
	// Wait as soon as we do not receive all the response
    while (dataReceived < dataToReceiveCount) {
        // TODO : delay100us(1);
		delaymSec(1);
        // Copy received data to the responseOutputStream (-> responseBuffer)
        // limit data reception to 1
        dataReceived += copyInputToOutputStream(dispatcherInputStream, responseOutputStream, NULL, 1);
        counter++;
        // Time out
        if (counter > 100) {
            appendString (getErrorOutputStreamLogger(), "Dispatcher:");
			appendString(getOutputStreamLogger(LOG_LEVEL_ERROR), dispatcher->name);
			appendString(getOutputStreamLogger(LOG_LEVEL_ERROR), "Time out:");
			appendStringAndDec(getOutputStreamLogger(LOG_LEVEL_ERROR), "Not enough Data :wanted=", dataToReceiveCount);
			appendStringAndDec(getOutputStreamLogger(LOG_LEVEL_ERROR), ",received=", getBufferElementsCount(responseBuffer));
            break;
        }
    }
	*/
    // printDebugBuffer(getOutputStreamLogger(ERROR), responseBuffer);
}
