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
* The instance of the dispatcher dedicated to local dispatching.
*/
static DriverDataDispatcher localDispatcher;

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
    // localStreamLink = aLocalStreamLink;
    localDispatcher.transmitMode = TRANSMIT_LOCAL;
    localDispatcher.name = "LOCAL_DISPATCHER";
    localDispatcher.address = 0;
    localDispatcher.driverDataDispatcherTransmitData = _driverDataDispatcherTransmitLocal;
    addDriverDataDispatcher(&localDispatcher);
    return &localDispatcher;
}

