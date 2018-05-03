#ifndef STRATEGY_DEVICE_H
#define STRATEGY_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../robot/strategy/gameStrategyContext.h"

/**
* Returns a descriptor on the device for strategy.
*/
DeviceDescriptor* getStrategyDeviceDescriptor(GameStrategyContext* gameStrategyContext);

#endif
