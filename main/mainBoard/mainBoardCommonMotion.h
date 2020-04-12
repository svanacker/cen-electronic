#ifndef MAIN_BOARD_COMMON_MOTION_H
#define MAIN_BOARD_COMMON_MOTION_H

#include "mainBoardCommon.h"

#include "../../common/io/inputStream.h"

#include "../../device/device.h"

// DEVICES

/**
 * Add the motion devices used by main Board (PID + Robot).
 * @param serialIndex
 */
void mainBoardCommonMotionAddDevices(unsigned char serialIndex);

/**
 * TODO
 */
void mainBoardDeviceHandleMotionDeviceNotification(const Device* device, const unsigned char commandHeader, InputStream* inputStream);

#endif

