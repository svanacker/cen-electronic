#include "stdlib.h"
#include "stdbool.h"

#include "driverDataDispatcher.h"

// Device
#include "../../drivers/driver.h"

#include "../../common/error/error.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

/**
 * @private
 * Transmit the buffer through Remote OutputStream and fill Response Buffer through InputStream
 */
bool remoteDriverDataDispatcherTransmit(DriverDataDispatcher* dispatcher,
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
    delayMilliSecs(2);

    // Wait as soon as we do not receive all the response
    while (dataReceived < dataToReceiveCount) {
        // Copy received data to the responseOutputStream (-> responseBuffer)
        // limit data reception to 1
        dataReceived += copyInputToOutputStream(dispatcherInputStream, responseOutputStream, NULL, 1);
        counter++;
        delayMicroSecs(200);

        // With a counter of 10000 * 200 (delayMicroSecs), it let 4 secs to have 
        // a response !
        if (counter > 20000) {
            writeError(DISPATCHER_LINK_ERROR);
            appendString(getErrorOutputStreamLogger(), "Dispatcher:");
            appendString(getErrorOutputStreamLogger(), dispatcher->name);
            appendString(getErrorOutputStreamLogger(), "Time out:");
            appendStringAndDec(getErrorOutputStreamLogger(), "Not enough Data :wanted=", dataToReceiveCount);
            appendStringAndDec(getErrorOutputStreamLogger(), ",received=", getBufferElementsCount(responseBuffer));
            return false;
        }
    }
    return true;
    // printDebugBuffer(getOutputStreamLogger(ERROR), responseBuffer);
}
