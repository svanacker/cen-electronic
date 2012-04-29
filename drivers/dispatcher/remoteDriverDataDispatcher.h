#ifndef REMOTE_DRIVER_DATA_DISPATCHER_H
#define REMOTE_DRIVER_DATA_DISPATCHER_H

#include "driverDataDispatcher.h"
#include "../../common/io/buffer.h"

void remoteDriverDataDispatcherTransmit(DriverDataDispatcher* dispatcher,
								        Buffer* requestBuffer,
								        Buffer* responseBuffer,
								        int dataToTransferCount,
								        int dataToReceiveCount
								        );

#endif
