#include <stdlib.h>

#include "localDriverDataDispatcher.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"

// Device
#include "../../drivers/driver.h"
#include "../../drivers/driverStreamListener.h"

#include "../../common/io/buffer.h"
#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/stream.h"

/**
* @private
* Transmit the buffer locally, call the device which write data out to the stream
*/
void _driverDataDispatcherTransmitLocal(DriverDataDispatcher* dispatcher,
                                     Buffer* inputBuffer,
                                     Buffer* outputBuffer,
                                     int dataToTransferCount,
                                     int dataToReceiveCount
    ) {
    handleStreamInstruction(inputBuffer, outputBuffer, NULL, NULL, NULL);
}

/**
* Add the local driver data dispatcher to the list.
*/
DriverDataDispatcher* addLocalDriverDataDispatcher() {
    DriverDataDispatcher* result = addDriverDataDispatcher(
                                    TRANSMIT_LOCAL,
                                    "LOCAL_DISPATCHER",
                                    NULL,
                                    0,
                                    NULL,
                                    NULL,
                                    _driverDataDispatcherTransmitLocal);
    return result;
}

