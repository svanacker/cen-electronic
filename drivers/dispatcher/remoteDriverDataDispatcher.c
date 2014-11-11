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
    unsigned int dataReceived = 0;
    int counter = 0;
    delaymSec(2);

    while (dataReceived < dataToReceiveCount) {
        delay100us(1);
        // Copy received data to the responseOutputStream (-> responseBuffer)
        // limit data reception to 1
        dataReceived += copyInputToOutputStream(dispatcherInputStream, responseOutputStream, NULL, 1);
        counter++;
        // Time out
        if (counter > 10000) {
            appendString (getErrorOutputStreamLogger(), "Dispatcher:");
            appendString (getOutputStreamLogger(ERROR), dispatcher->name);
            appendString (getOutputStreamLogger(ERROR), "Time out:");
            appendStringAndDec(getOutputStreamLogger(ERROR), "Not enough Data :wanted=", dataToReceiveCount);
            appendStringAndDec(getOutputStreamLogger(ERROR), ",received=", getBufferElementsCount(responseBuffer));
            break;
        }
    }
    // printDebugBuffer(getOutputStreamLogger(ERROR), responseBuffer);
}
