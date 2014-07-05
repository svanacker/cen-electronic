#include <p30Fxxxx.h>
#include <stdlib.h>

#include "airConditioningMain.h"

#include "../../common/setup/30F/picSetup30F.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/master/i2cMasterSetup.h"

#include "../../common/io/compositeOutputStream.h"
#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

// -> Devices
#include "../../device/deviceUsage.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Servo
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// Air Conditioning
#include "../../device/airconditioning/airConditioningDevice.h"
#include "../../device/airconditioning/airConditioningDeviceInterface.h"

// Drivers
#include "../../drivers/driver.h"
#include "../../drivers/driverTransmitter.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverStreamListener.h"

#include "../../drivers/temperature/MCP9804.h"

#ifndef MPLAB_SIMULATION
#define SERIAL_PORT_DEBUG         SERIAL_PORT_2
#else
// We use the same port for both
#define SERIAL_PORT_DEBUG         SERIAL_PORT_1
#endif

#define        SERVO_INDEX                1
#define        SERVO_VALUE_TOUCH          1620
#define        SERVO_VALUE_STAND_BY       1400
#define        SERVO_SPEED                0xFF


// 1000000 ==> 20 seconds
// 5000000 ==> 10000 seconds => 15 minutes

#define        ITERATION_OFF            20000000L
#define        ITERATION_ON             40000000L

/**
 * Device list.
 */
static DeviceList devices;

// serial DEBUG 
static char debugInputBufferArray[AIR_CONDITIONING_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[AIR_CONDITIONING_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// I2C
static char i2cSlaveInputBufferArray[AIR_CONDITIONING_BOARD_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[AIR_CONDITIONING_BOARD_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// logs
static LogHandler serialLogHandler;

// devices
static Device deviceListArray[AIR_CONDITIONING_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[AIR_CONDITIONING_BOARD_TIMER_LENGTH];

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[AIR_CONDITIONING_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[AIR_CONDITIONING_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, AIR_CONDITIONING_BOARD_DEVICE_LENGTH);
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(getAirConditioningDeviceInterface(), getAirConditioningDeviceDescriptor());

    initDevices(&devices);
}

/**
 * @private
 */
void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, AIR_CONDITIONING_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
            &driverResponseBuffer, &driverResponseBufferArray, AIR_CONDITIONING_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);
}

void initStrategyBoardIO() {
    // 2011 : TODO : A regarder
    ADPCFG = 0xFFFF;
}

void clickOnButton() {
    pwmServo(SERVO_INDEX, SERVO_SPEED, SERVO_VALUE_TOUCH);
    delaymSec(500);
    pwmServo(SERVO_INDEX, SERVO_SPEED, SERVO_VALUE_STAND_BY);
}

int main(void) {
    setPicName("AIR_COND_BOARD");

    initStrategyBoardIO();

    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            AIR_CONDITIONING_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            AIR_CONDITIONING_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG, 0);


    initTimerList(&timerListArray, AIR_CONDITIONING_BOARD_TIMER_LENGTH);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
    appendString(getOutputStreamLogger(INFO), getPicName());
    println(getOutputStreamLogger(INFO));

    // Initializes the I2C
    // i2cMasterInitialize();

    openSlaveI2cStreamLink(&i2cSerialStreamLink,
                            &i2cSlaveInputBuffer,
                            &i2cSlaveInputBufferArray,
                            AIR_CONDITIONING_BOARD_I2C_INPUT_BUFFER_LENGTH,
                            &i2cSlaveOutputBuffer,
                            &i2cSlaveOutputBufferArray,
                            AIR_CONDITIONING_BOARD_I2C_OUTPUT_BUFFER_LENGTH,
                            AIR_CONDITIONING_BOARD_I2C_ADDRESS
                        );

    // init the devices
    initDevicesDescriptor();

    initDriversDescriptor();

    // Init the timers management
    startTimerList();

    // Initialize the driver : TODO : Encapsulates into a driver.
    initRegMCP9804(0x00, 0x18, 0x01, 0xE0, 0x01, 0x40, 0x02, 0x40); // 30C, 20C, 34C

    clickOnButton();
    unsigned long timerIndex = 0L;
    bool timerOn = true;
    unsigned long timerMax = ITERATION_ON;

    while (1) {
        timerIndex++;

        if (timerIndex > timerMax) {
            timerIndex = 0;
            timerOn = !timerOn;
            if (timerOn) {
                timerMax = ITERATION_ON;
            } else {
                timerMax = ITERATION_OFF;
            }
            clickOnButton();
        }

        // UART Stream
        handleStreamInstruction(&debugInputBuffer,
                &debugOutputBuffer,
                &debugOutputStream,
                &filterRemoveCRLF,
                NULL);

        // I2C Stream
        handleStreamInstruction(&i2cSlaveInputBuffer,
                                &i2cSlaveOutputBuffer,
                                NULL,
                                &filterRemoveCRLF,
                                NULL);
    }
    return (0);
}
