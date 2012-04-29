#include <i2c.h>
#include <p30fxxxx.h>
#include <stdlib.h>

// List of available functionnality

#include "motorBoard.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"
#include "../../common/math/cenMath.h"

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

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
#include "../../device/dispatcher/deviceDataDispatcher.h"

#include "../../drivers/driverStreamListener.h"

// -> Devices

// Test
#include "../../device/test/deviceTest.h"
#include "../../device/test/deviceTestInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Motors
#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

// PID
#include "../../motion/pid/pid.h"
#include "../../motion/pid/pidDebug.h"
#include "../../motion/pid/pidMotionProfileComputer.h"
#include "../../device/motion/pid/pidDevice.h"
#include "../../device/motion/pid/pidDeviceInterface.h"

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
#include "../../motion/extended/singleBSpline.h"
#include "../../motion/simple/motion.h"
#include "../../motion/position/trajectory.h"
#include "../../motion/position/coders.h"

// #include "../../test/mathTest.h"
#include "../../test/motion/bspline/bsplinetest.h"

// The port for which we debug (we can send instruction too)
#ifndef MPBLAB_SIMULATION
#define SERIAL_PORT_DEBUG 	SERIAL_PORT_2
#else
#define SERIAL_PORT_DEBUG 	SERIAL_PORT_1
#endif

/**
 * Device list.
 */
static DeviceList devices;

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
static Device motorDevice;
static Device codersDevice;
static Device pidDevice;
static Device motionDevice;
static Device trajectoryDevice;
// static Device testDevice;
static Device systemDevice;

void initDevicesDescriptor() {
    addLocalDevice(&motorDevice, getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(&codersDevice, getCodersDeviceInterface(), getCodersDeviceDescriptor());
    addLocalDevice(&pidDevice, getPIDDeviceInterface(), getPIDDeviceDescriptor());
    addLocalDevice(&motionDevice, getMotionDeviceInterface(), getMotionDeviceDescriptor());
    addLocalDevice(&trajectoryDevice, getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    // addLocalDevice(&testDevice, getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(&systemDevice, getSystemDeviceInterface(), getSystemDeviceDescriptor());

    initDevices(&devices);
}

void waitForInstruction() {
    // I2C Stream
    handleStreamInstruction(&i2cSlaveInputBuffer, &i2cSlaveOutputBuffer, NULL, &filterRemoveCRLF, NULL);

    // UART Stream
    handleStreamInstruction(&debugInputBuffer, &debugOutputBuffer, &debugOutputStream, &filterRemoveCRLF, NULL);

    // Manage Motion
    handleInstructionAndMotion();
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
            SERIAL_PORT_DEBUG);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
    appendString(getDebugOutputStreamLogger(), getPicName());
    appendCRLF(getDebugOutputStreamLogger());

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

	/*
	BSplineCurve* curve = getSingleBSplineCurve();

	Position* position = getPosition();
	position->pos.x = 400.0f;
	position->pos.y = 100.0f;
	//position->orientation = - PI / 2.0f;
	position->orientation = -PI / 3.0f;
	updateSimpleSplineWithDistance(700.0f, 500.0f, 0.75f * PI, 200.0f, 300.0f, FALSE);
	float maxDerivative = computeBSplineMaxDerivative(curve);
	appendStringAndDecf(&debugOutputStream, "mDerv=", maxDerivative);
	*/
	 /*
	// Test en marche arriere
	Position* position = getPosition();
	position->pos.x = 0.0f;
	position->pos.y = 0.0f;
	//position->orientation = - PI / 2.0f;
	position->orientation = 0.0f;
	updateSimpleSplineWithDistance(-200.0f, 200.0f, - PI / 4, -100.0f, -100.0f, FALSE);

	appendStringAndDecf(&debugOutputStream, "p0x=", curve->p0->x * WHEEL_AVERAGE_LENGTH);
	appendStringAndDecf(&debugOutputStream, ",p0y=", curve->p0->y * WHEEL_AVERAGE_LENGTH);
	appendStringAndDecf(&debugOutputStream, ",p1x=", curve->p1->x * WHEEL_AVERAGE_LENGTH);
	appendStringAndDecf(&debugOutputStream, ",p1y=", curve->p1->y * WHEEL_AVERAGE_LENGTH);
	appendStringAndDecf(&debugOutputStream, ",p2x=", curve->p2->x * WHEEL_AVERAGE_LENGTH);
	appendStringAndDecf(&debugOutputStream, ",p2y=", curve->p2->y * WHEEL_AVERAGE_LENGTH);
	appendStringAndDecf(&debugOutputStream, ",p3x=", curve->p3->x * WHEEL_AVERAGE_LENGTH);
	appendStringAndDecf(&debugOutputStream, ",p3y=", curve->p3->y * WHEEL_AVERAGE_LENGTH);
	println(&debugOutputStream);
	*/

	/*
	MotionInstruction instruction;
	instruction.a = 0.5f;
	instruction.initialSpeed = 3;
	instruction.speed = 7;
	instruction.endSpeed = 4;
	computeMotionInstruction(&instruction);
	printInst(getDebugOutputStreamLogger(), &instruction);
	printTrajectory(getDebugOutputStreamLogger(),  &instruction, 20.0f);
	*/
    while (1) {
        waitForInstruction();
    }
}

int main(void) {
    runMotorBoard();

    return (0);
}
