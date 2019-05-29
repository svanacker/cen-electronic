#ifndef FAKE_ROBOT_DEVICE_H
#define FAKE_ROBOT_DEVICE_H

#include "../../../common/io/outputStream.h"

#include "../../../device/deviceDescriptor.h"

#include "../../../robot/fake/fakeRobot.h"

/**
 * The descriptor for the Fake Robot 
 * @param fakeRobot the fake Robot structure with all informations.
 */
DeviceDescriptor* getFakeRobotDeviceDescriptor(FakeRobot* fakeRobot);

#endif
