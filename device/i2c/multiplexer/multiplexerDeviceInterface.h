#ifndef MULTIPLEXER_DEVICE_INTERFACE_H
#define MULTIPLEXER_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

#define COMMAND_MULTIPLEXER_READ_SINGLE_CHANNEL      'r'

#define COMMAND_MULTIPLEXER_READ_CHANNELS_MASK       'R'

#define COMMAND_MULTIPLEXER_WRITE_SINGLE_CHANNEL     'w'

#define COMMAND_MULTIPLEXER_WRITE_CHANNELS_MASK      'W'

#define COMMAND_MULTIPLEXER_DEBUG               'd'

/**
* Interface for Multiplexer Device.
*/
DeviceInterface* getMultiplexerDeviceInterface(void);

#endif

