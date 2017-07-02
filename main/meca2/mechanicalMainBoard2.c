#define _SUPPRESS_PLIB_WARNING
#include <i2c.h>
#include <p30Fxxxx.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mechanicalBoard2.h"

#include "../../common/setup/30F/picSetup30F.h"

#include "../../common/adc/adcutils.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../common/system/system.h"

#include "../../device/device.h"
#include "../../device/deviceList.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

// -> Devices

// ADC
#include "../../device/adc/adcDevice.h"
#include "../../device/adc/adcDeviceInterface.h"

// I2C Slave
#include "../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

// LOGS
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// Test
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// Servo
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// Infrared detector
#include "../../robot/opponent/robotInfraredDetector.h"
#include "../../robot/opponent/robotInfraredDetectorDevice.h"
#include "../../robot/opponent/robotInfraredDetectorDeviceInterface.h"

// Relay
#include "../../device/relay/relayDevice.h"
#include "../../device/relay/relayDeviceInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Robot 2012
#include "../../robot/2012/armDevice2012.h"
#include "../../robot/2012/armDeviceInterface2012.h"

#include "../../drivers/driverStreamListener.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"
#include "../../drivers/dispatcher/uartDriverDataDispatcher.h"

#include "../../drivers/system/systemDriver.h"

// The port for which we debug (we can send instruction too)
#define SERIAL_PORT_DEBUG     SERIAL_PORT_2

/**
* Device list.
*/
static DeviceList devices;

// logs
static LogHandler logHandlerListArray[MECA_BOARD_2_LOG_HANDLER_LIST_LENGTH];

// serial DEBUG 
static char debugInputBufferArray[MECA_BOARD_2_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MECA_BOARD_2_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// i2c Link
static I2cBus mechanicalBoard2I2cBus;
static I2cBusConnection mechanicalBoard2I2cBusConnection;
static char i2cSlaveInputBufferArray[MECA_BOARD_2_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MECA_BOARD_2_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// Devices
static Device deviceListArray[MECHANICAL_BOARD_2_DEVICE_LENGTH];

// Timers
static Timer timerListArray[MECHANICAL_BOARD_2_TIMER_LENGTH];

// RobotDetector
static RobotInfraredDetector robotInfraredDetector;

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MECA_2_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MECA_2_RESPONSE_DRIVER_BUFFER_LENGTH];

// DISPATCHER I2C
static DriverDataDispatcher driverDataDispatcherListArray[MECHANICAL_BOARD_2_DRIVER_DATA_DISPATCHER_LIST_LENGTH];

/*
Buffer* getMechanicalBoard2I2CSlaveOutputBuffer() {
    return &i2cSlaveOutputBuffer;
}
*/

void initMechanicalBoard2sDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, MECA_2_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, MECA_2_RESPONSE_DRIVER_BUFFER_LENGTH);
}

void initMechanicalBoard2DriverDataDispatcherList(void) {
    // Initializes the DriverDataDispatcherList
    initDriverDataDispatcherList(&driverDataDispatcherListArray, MECHANICAL_BOARD_2_DRIVER_DATA_DISPATCHER_LIST_LENGTH);
    
    // Uart Stream for Notification to the mainBoard
    addUartDriverDataDispatcher(
        &debugSerialStreamLink,
        "MAIN_BOARD_UART_DISPATCHER",
        SERIAL_PORT_DEBUG);
}

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MECHANICAL_BOARD_2_DEVICE_LENGTH);

    // LOCAL
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getI2cSlaveDebugDeviceInterface(), getI2cSlaveDebugDeviceDescriptor(&mechanicalBoard2I2cBusConnection));
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(getADCDeviceInterface(), getADCDeviceDescriptor());
    addLocalDevice(getArm2012DeviceInterface(), getArm2012DeviceDescriptor());
    addLocalDevice(getRobotInfraredDetectorDeviceInterface(), getRobotInfraredDetectorDeviceDescriptor(&robotInfraredDetector));

    // REMOTE
    // addUartRemoteDevice(getSystemDeviceInterface(), SERIAL_PORT_DEBUG);

    initDevices(&devices);
}

void initMechanicalBoard2Pins() {
    // by default, PORTB is as input, do not set it !
    PORTBbits.RB8 = 0;
    PORTBbits.RB9 = 0;
    PORTBbits.RB10 = 0;
    PORTBbits.RB11 = 0;
    PORTBbits.RB12 = 0;

    // PORTB as input
    // TRISB = 0x00FF;
    // TRISB = 0xFFFF;

    // PORT C as output (relay)
    TRISC = 0;
    PORTC = 0;
    TRISC = 0;

    // PORT D as output (relay)
    TRISD = 0;
    PORTD = 0;
    TRISD = 0;
}

int main(void) {
    setBoardName("MECHANICAL 2");

    initMechanicalBoard2Pins();

    openSerialLink( &debugSerialStreamLink,
                    &debugInputBuffer,
                    &debugInputBufferArray,
                    MECA_BOARD_2_DEBUG_INPUT_BUFFER_LENGTH,
                    &debugOutputBuffer,
                    &debugOutputBufferArray,
                    MECA_BOARD_2_DEBUG_OUTPUT_BUFFER_LENGTH,
                    &debugOutputStream,
                    SERIAL_PORT_DEBUG,
                    0);

    // Init the logs
    // initLogs(LOG_LEVEL_ERROR, &logHandlerListArray, MECA_BOARD_2_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    initLogs(DEBUG, &logHandlerListArray, MECA_BOARD_2_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addLogHandler("UART", &debugOutputStream, DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendString(getDebugOutputStreamLogger(), getBoardName());
    println(getDebugOutputStreamLogger());

    initTimerList(&timerListArray, MECHANICAL_BOARD_2_TIMER_LENGTH);

    initI2cBus(&mechanicalBoard2I2cBus, I2C_BUS_TYPE_SLAVE, I2C_BUS_PORT_1);
    initI2cBusConnection(&mechanicalBoard2I2cBusConnection, &mechanicalBoard2I2cBus, MECHANICAL_BOARD_2_I2C_ADDRESS);

    openSlaveI2cStreamLink(&i2cSerialStreamLink,
                            &i2cSlaveInputBuffer,
                            &i2cSlaveInputBufferArray,
                            MECA_BOARD_2_I2C_INPUT_BUFFER_LENGTH,
                            &i2cSlaveOutputBuffer,
                            &i2cSlaveOutputBufferArray,
                            MECA_BOARD_2_I2C_OUTPUT_BUFFER_LENGTH,
                            &mechanicalBoard2I2cBusConnection
                        );

    // init the devices
    initDevicesDescriptor();

    // Drivers
    initMechanicalBoard2sDriversDescriptor();

    // init the Dispatchers
    initMechanicalBoard2DriverDataDispatcherList();


    // Init the timers management
    startTimerList();

    // 2011 : TODO : A regarder
    // ADPCFG = 0xFFFF;

    // upArm(ARM_LEFT);
    // upArm(ARM_RIGHT);

    while (true) {
        /*
        // Forward Obstacle
        // Only if robotDetector has something to notify
        if (mustNotifyRobotInfraredObstacleForward()) {
            resetNotifyRobotInfraredObstacleForward();
            // systemDeviceList();
            appendString(getDebugOutputStreamLogger(), "\nForward Obstacle, wait few seconds For New Notification !\n");
        }
        */

        // Backward Obstacle
        /*
        if (getRobotInfraredObstacleBackward()) {
            notifyInfraredDetectorDetection(DETECTOR_GROUP_TYPE_BACKWARD);
            appendString(getAlwaysOutputStreamLogger(), "\nBackward Obstacle, wait few seconds For New Notification !\n");
        }
        */
        // I2C Stream
        /* TODO : Reactivate when I2C Slave for 30F will be ok !
        handleStreamInstruction(&i2cSlaveInputBuffer,
                                &i2cSlaveOutputBuffer,
                                NULL,
                                &filterRemoveCRLF,
                                NULL);
        */

        // UART Stream
        handleStreamInstruction(&debugInputBuffer,
                                &debugOutputBuffer,
                                &debugOutputStream,
                                &filterRemoveCRLF,
                                NULL);
    }
    return 0;
}
