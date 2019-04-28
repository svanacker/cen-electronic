#ifndef REMOTE_DRIVER_DATA_DISPATCHER_H
#define REMOTE_DRIVER_DATA_DISPATCHER_H

#include <stdbool.h>

#include "driverDataDispatcher.h"

#include "../../common/io/buffer.h"

bool remoteDriverDataDispatcherTransmit(DriverDataDispatcher* dispatcher,
                                        Buffer* requestBuffer,
                                        Buffer* responseBuffer,
                                        int dataToTransferCount,
                                        int dataToReceiveCount
                                        );

#endif
