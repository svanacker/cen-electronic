#include "mainBoardCommonMotor.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/error/error.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../device/deviceConstants.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"

#include "../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

// Motor
#include "../../device/motor/pwmMotorDeviceInterface.h"

// TEST
#include "../../device/motion/position/codersDeviceInterface.h"
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/extended/extendedMotionDeviceInterface.h"
#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

// TEST
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

#include "../../drivers/dispatcher/uartDriverDataDispatcher.h"
#include "../../drivers/driverStreamListener.h"

// CLIENT
#include "../../client/motion/simple/clientMotion.h"

// serial link Motor
static char motorInputBufferArray[MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH];
static Buffer motorInputBuffer;
static char motorOutputBufferArray[MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH];
static Buffer motorOutputBuffer;
static OutputStream motorOutputStream;
static StreamLink motorSerialStreamLink;


// serial link Motor Notification
static char motorNotifyInputBufferArray[MAIN_BOARD_MOTOR_NOTIFY_INPUT_BUFFER_LENGTH];
static Buffer motorNotifyInputBuffer;
static char motorNotifyOutputBufferArray[MAIN_BOARD_MOTOR_NOTIFY_OUTPUT_BUFFER_LENGTH];
static Buffer motorNotifyOutputBuffer;
static OutputStream motorNotifyOutputStream;
static StreamLink motorNotifySerialStreamLink;

// FORWARD DECLARATION
void mainBoardDeviceHandleMotionDeviceNotification(const Device* device, const char commandHeader, InputStream* inputStream);

void mainBoardCommonMotorAddDevices(unsigned char serialIndex) {
    // MOTOR BOARD -> UART
    addUartRemoteDevice(getTestDeviceInterface(), serialIndex);
    addUartRemoteDevice(getMotorDeviceInterface(), serialIndex);
    addUartRemoteDevice(getCodersDeviceInterface(), serialIndex);
    addUartRemoteDevice(getPidDeviceInterface(), serialIndex);
    addUartRemoteDevice(getExtendedMotionDeviceInterface(), serialIndex);
    addUartRemoteDevice(getRobotKinematicsDeviceInterface(), serialIndex);
    addUartRemoteDeviceWithNotification(getMotionDeviceInterface(), serialIndex, &mainBoardDeviceHandleMotionDeviceNotification);
}

void mainBoardCommonMotorAddDispatcher(void) {
 
    // Uart Stream for motorBoard
    addUartDriverDataDispatcher(
        &motorSerialStreamLink,
        "MOTOR_BOARD_UART_DISPATCHER",
        MAIN_BOARD_SERIAL_PORT_MOTOR);

    // Uart Stream for motorBoard Notification
    addUartDriverDataDispatcher(
        &motorNotifySerialStreamLink,
        "MOTOR_BOARD_NOTIFY_UART_DISPATCHER",
        MAIN_BOARD_SERIAL_PORT_MOTOR_NOTIFY);
}

void clearMotorAndMotorNotifyBuffer(void) {
    clearBuffer(&motorInputBuffer);
    // Send a clear Buffer to the remote board to avoid to keep bad data in the link when rebooting
    append(&motorOutputStream, HEADER_CLEAR_INPUT_STREAM);
    // append(&motorOutputStream, HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER);
    motorOutputStream.flush(&motorOutputStream);
    
    // UART Notification
    clearBuffer(&motorNotifyInputBuffer);
    // Send a clear Buffer to the remote board to avoid to keep bad data in the link when rebooting
    append(&motorNotifyOutputStream, HEADER_CLEAR_INPUT_STREAM);
    // append(&motorNotifyOutputStream, HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER);
    motorNotifyOutputStream.flush(&motorNotifyOutputStream);
    
    delaymSec(100);
}

void mainBoardCommonMotorHandleStreamInstruction(void) {
    // Handle Notification
    while (handleNotificationFromDispatcherList(TRANSMIT_UART, MAIN_BOARD_SERIAL_PORT_MOTOR_NOTIFY)) {
        
    }

    // Listen instruction from motorNotifyStream->Devices
    handleStreamInstruction(
            &motorNotifyInputBuffer,
            &motorNotifyOutputBuffer,
            &motorNotifyOutputStream,
            &filterRemoveCRLF_255,
            NULL);
    
    
    if (getBufferElementsCount(&motorNotifyInputBuffer) > 0) {
        int c = bufferGetCharAtIndex(&motorNotifyInputBuffer, 0);
        if (c == 'ÿ') {
            bufferReadChar(&motorNotifyInputBuffer);
        }
    }
}

void mainBoardCommonMotorOpenSerialLink(void) {
        // Open the serial Link for the Motor Board
    openSerialLink(&motorSerialStreamLink,
                   "SERIAL_MOTOR", 
                   &motorInputBuffer, &motorInputBufferArray, MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH,
                   &motorOutputBuffer, &motorOutputBufferArray, MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH,
                   &motorOutputStream,
                   MAIN_BOARD_SERIAL_PORT_MOTOR,
                   DEFAULT_SERIAL_SPEED);
}

void mainBoardCommonMotorNotifyOpenSerialLink(void) {
        // Open the serial Link for the PC : No Log, only instruction
    openSerialLink(&motorNotifySerialStreamLink,
                   "MOTOR_NOTIFY", 
                    &motorNotifyInputBuffer, &motorNotifyInputBufferArray, MAIN_BOARD_MOTOR_NOTIFY_INPUT_BUFFER_LENGTH,
                    &motorNotifyOutputBuffer, &motorNotifyOutputBufferArray, MAIN_BOARD_MOTOR_NOTIFY_OUTPUT_BUFFER_LENGTH,
                    &motorNotifyOutputStream,
                    MAIN_BOARD_SERIAL_PORT_MOTOR_NOTIFY,
                    DEFAULT_SERIAL_SPEED);
}

/**
 * Initialisation part in the Main Program of MAIN BOARD for the Motor Part.
 */
void mainBoardCommonMotorMainEndInit(void) {
        // MOTOR BOARD
    // UART Device
    /*
    clearBuffer(&motorInputBuffer);
    // Send a clear Buffer to the remote board to avoid to keep bad data in the link when rebooting
    append(&motorOutputStream, HEADER_CLEAR_INPUT_STREAM);
    append(&motorOutputStream, HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER);
    motorOutputStream.flush(&motorOutputStream);
    
    clearMotorAndMotorNotifyBuffer();
    */
    // Maintain the position to avoid that the robot move
    // motionDriverMaintainPosition();
}