#include "mainBoardCommonMotion.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/error/error.h"

#include "../../common/log/logger.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/timer/delayTimer.h"

#include "../../device/deviceConstants.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"

// PID
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

#include "../../device/motion/extended/extendedMotionDeviceInterface.h"
#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

#include "../../drivers/dispatcher/uartDriverDataDispatcher.h"
#include "../../drivers/driverStreamListener.h"

// CLIENT
#include "../../client/motion/simple/clientMotion.h"

// FORWARD DECLARATION

void mainBoardCommonMotionAddDevices(unsigned char serialIndex) {
    // PID & Motion & Robot
    addUartRemoteDevice(getPidDeviceInterface(), serialIndex);
    addUartRemoteDevice(getExtendedMotionDeviceInterface(), serialIndex);
    addUartRemoteDevice(getRobotKinematicsDeviceInterface(), serialIndex);
    addUartRemoteDeviceWithNotification(getMotionDeviceInterface(), serialIndex, &mainBoardDeviceHandleMotionDeviceNotification);
}
