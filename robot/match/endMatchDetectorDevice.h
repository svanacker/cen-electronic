#ifndef END_MATCH_DETECTOR_DEVICE_H
#define END_MATCH_DETECTOR_DEVICE_H

#include "../../device/device.h"

#include "endMatch.h"
#include "../../robot/config/robotConfig.h"

/**
* Returns the deviceDescriptor of the end Match Detector.
*/
DeviceDescriptor* getEndMatchDetectorDeviceDescriptor(EndMatch* endMatchParam);

#endif


