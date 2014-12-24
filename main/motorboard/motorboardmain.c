#include <i2c.h>
#include <stdlib.h>

// List of available functionnality

#include "motorBoard.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"
#include "../../common/math/cenMath.h"

#include "../../common/setup/30F/picSetup30F.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/pwm/pwmPic.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/deviceList.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

#include "../../drivers/driverStreamListener.h"

// -> Devices

// Test
// #include "../../device/test/testDevice.h"
// #include "../../device/test/testDeviceInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Motors
#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

// Coders
#include "../../device/motion/position/codersDevice.h"
#include "../../device/motion/position/codersDeviceInterface.h"

// Trajectory
#include "../../device/motion/position/trajectoryDevice.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"

// Motion
#include "../../device/motion/simple/motionDevice.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

// Drivers
#include "../../drivers/motor/motorDriver.h"

// Direct implementation
#include "../../motion/simple/motion.h"
#include "../../motion/position/trajectory.h"
#include "../../motion/position/coders.h"

// #include "../../test/mathTest.h"
#include "../../test/motion/bspline/bsplinetest.h"

// The port for which we debug (we can send instruction too)
#ifndef MPLAB_SIMULATION
    #define SERIAL_PORT_DEBUG     SERIAL_PORT_2
#else
    #define SERIAL_PORT_DEBUG     SERIAL_PORT_1
#endif

// serial DEBUG 
static char debugInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler serialLogHandler;

// i2c Link
static char i2cSlaveInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSlaveStreamLink;

// Timers
static Timer timerListArray[MOTOR_BOARD_TIMER_LENGTH];

#define MOTOR_BOARD_PIC_NAME "MOTOR BOARD"

Buffer* getI2CSlaveOutputBuffer() {
    return &i2cSlaveOutputBuffer;
}

// I2C Debug
/*
static Buffer debugI2cInputBuffer;
static Buffer debugI2cOutputBuffer;
 */

// Devices
static Device deviceListArray[MOTOR_BOARD_DEVICE_LENGTH];

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MOTOR_BOARD_DEVICE_LENGTH);

    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
    addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    // addLocalDevice(&testDevice, getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());

    initDevices();
}

void waitForInstruction() {
    // I2C Stream
    handleStreamInstruction(&i2cSlaveInputBuffer, &i2cSlaveOutputBuffer, NULL, &filterRemoveCRLF, NULL);

    // UART Stream
    handleStreamInstruction(&debugInputBuffer, &debugOutputBuffer, &debugOutputStream, &filterRemoveCRLF, NULL);
}

int runMotorBoard() {
    setPicName(MOTOR_BOARD_PIC_NAME);

    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG,
            0);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
    appendString(getDebugOutputStreamLogger(), getPicName());
    appendCRLF(getDebugOutputStreamLogger());

    initTimerList(&timerListArray, MOTOR_BOARD_TIMER_LENGTH);

    // Debug of I2C : Only if there is problems
    // initI2CDebugBuffers(&debugI2cInputBuffer, &debugI2cOutputBuffer);

    openSlaveI2cStreamLink(&i2cSlaveStreamLink,
            &i2cSlaveInputBuffer,
            &i2cSlaveInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &i2cSlaveOutputBuffer,
            &i2cSlaveOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            MOTOR_BOARD_I2C_ADDRESS
            );

    // init the devices
    initDevicesDescriptor();

    // Init the timers management
    startTimerList();

    while (1) {
        waitForInstruction();
    }
}

int main(void) {
    runMotorBoard();

    return (0);
}
