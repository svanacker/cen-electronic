#include <stdlib.h>
#include <p30Fxxxx.h>

// FIRST INCLUDE !
#include "../../common/setup/30F/picSetup30F.h"

#include "beaconBoard.h"

#include "../../common/commons.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/filter.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/timer/timerList.h"
#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerDebug.h"

#include "../../common/2d/2d.h"

#include "../../common/system/system.h"

#include "../../device/device.h"
#include "../../device/deviceDescriptor.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceList.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

#include "../../drivers/driverStreamListener.h"

// -> Jennic
#include "../../drivers/jennic/jennic5139Driver.h"
#include "../../drivers/jennic/jennic5139EventParser.h"
#include "../../drivers/jennic/jennic5139OutputStream.h"

// Specific
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// servo
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// system
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"
#include "../../device/system/pinDevice.h"
#include "../../device/system/pinDeviceInterface.h"

// common Beacon
#include "../../device/beacon/commonBeaconDevice.h"
#include "../../device/beacon/commonBeaconDeviceInterface.h"

// beacon
#include "../../device/beacon/laserBeacon.h"
#include "../../device/beacon/beaconSystem.h"
#include "../../device/beacon/laserBeaconDevice.h"
#include "../../device/beacon/laserBeaconDeviceInterface.h"

// receiver beacon
#include "../../device/beacon/beaconReceiverDeviceInterface.h"

// drivers
#include "../../drivers/driverList.h"
#include "../../drivers/dispatcher/zigbeeDriverDataDispatcher.h"

#include "../../robot/robotDetector.h"

// BUFFER

// -> serial DEBUG 
static char debugInputBufferArray[JENNIC_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[JENNIC_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// -> serial ZIGBEE 
static char zigbeeInputBufferArray[JENNIC_ZIGBEE_INPUT_BUFFER_LENGTH];
static Buffer zigbeeInputBuffer;
static char zigbeeOutputBufferArray[JENNIC_ZIGBEE_OUTPUT_BUFFER_LENGTH];
static Buffer zigbeeOutputBuffer;
static OutputStream zigbeeOutputStream;
static StreamLink zigbeeSerialStreamLink;

// -> Zigbee Response
#define    RESPONSE_DATA_OUTPUT_BUFFER_LENGTH        20
static Buffer responseDataOutputBuffer;
static char responseDataOutputBufferArray[RESPONSE_DATA_OUTPUT_BUFFER_LENGTH];
static OutputStream responseDataOutputStream; 

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[JENNIC_ZIGBEE_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[JENNIC_ZIGBEE_RESPONSE_DRIVER_BUFFER_LENGTH];

// DISPATCHER

// -> zigbee->Beacon Board Main
static DriverDataDispatcher beaconReceiverDispatcher;
static InputStream beaconReceiverInputStream;
static OutputStream beaconReceiverOutputStream;

// The port for which we debug (we can send instruction too)
#define SERIAL_PORT_DEBUG     SERIAL_PORT_2

// The port for which we dialog with ZIGBEE
#define SERIAL_PORT_ZIGBEE     SERIAL_PORT_1

// logs
static LogHandler logHandlerListArray[BEACON_LOG_HANDLER_LIST_LENGTH];

// Devices
static Device deviceListArray[BEACON_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[BEACON_BOARD_TIMER_LENGTH];

// events
static JennicEvent dataEvent;
static JennicEvent errorEvent;
static JennicEvent networkStartEvent;
static JennicEvent childJoinedEvent;
static JennicEvent childLeaveEvent;

/**
 * @private
 */
int getLaserPin1() {
    // L1
    return PORTBbits.RB0;
}

/**
 * @private
 */
int getLaserPin2() {
    // L3
    return PORTBbits.RB2;
}

/**
 * @private
 */
void initLaserDetectorSettings() {
    // Initialization of laserDetector
    // Laser 1
    initLaserDetectorStruct(getLaser(LASER_INDEX_1),
            LASER_SERVO_INDEX_1,
            &getLaserPin1,
            SERVO_LASER_1_MAX_LEFT_POSITION_DEFAULT_VALUE,
            SERVO_LASER_1_MAX_RIGHT_POSITION_DEFAULT_VALUE,
            SHORT_TRACKING_INTERVAL,
            BEACON_SERVO_1_FACTOR,
            BEACON_SERVO_1_INIT_COMPUTE_VALUE,
            BEACON_SERVO_1_ANGLE_DEGREE
            );
    // Laser 2
    initLaserDetectorStruct(getLaser(LASER_INDEX_2),
            LASER_SERVO_INDEX_2,
            &getLaserPin2,
            SERVO_LASER_2_MAX_LEFT_POSITION_DEFAULT_VALUE,
            SERVO_LASER_2_MAX_RIGHT_POSITION_DEFAULT_VALUE,
            SHORT_TRACKING_INTERVAL,
            BEACON_SERVO_2_FACTOR,
            BEACON_SERVO_2_INIT_COMPUTE_VALUE,
            BEACON_SERVO_2_ANGLE_DEGREE
            );
    setDistanceBetweenBeacon(DISTANCE_BETWEEN_BEACON);
    setCalibrationPoint(BEACON_CALIBRATION_POINT_X, BEACON_CALIBRATION_POINT_Y);
    setObsoleteDetectionTimeThreshold(OBSOLETE_DETECTION_TIME_THRESHOLD);
    setNotifyTimeDelay(NOTIFY_DELAY);
}

/**
 * @private
 */
void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, BEACON_BOARD_DEVICE_LENGTH);

    // Get test device for debug purpose
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getPinDeviceInterface(), getPinDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());

    // Main Device
    addLocalDevice(getCommonBeaconDeviceInterface(), getCommonBeaconDeviceDescriptor());
    addLocalDevice(getLaserBeaconDeviceInterface(), getBeaconDeviceDescriptor());

    // Remote
    addZigbeeRemoteDevice(getBeaconReceiverDeviceInterface(), JENNIC_ROUTER_MAC_ADDRESS);

    initDevices();
}

void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, JENNIC_ZIGBEE_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, JENNIC_ZIGBEE_RESPONSE_DRIVER_BUFFER_LENGTH);
}

void initBeaconIO() {
    // Use All port as digital Port
    ADPCFG = 0xFFFF;
    // PORT B0->B3 as input (laser)
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
}

void onError(JennicEvent* jennicEvent) {
    appendString(getErrorOutputStreamLogger(), "ERROR ! \n");
    onJennicError();
}

/**
 * Called when the network started.
 */ 
void onNetworkStart(JennicEvent* jennicEvent) {
    appendString(getInfoOutputStreamLogger(), "NETWORK START ! \n");
    setJennicNetworkStatus(JENNIC_WAITING_FOR_NODE);
    pwmServo(LASER_SERVO_INDEX_1, 0xFF, 800.0f);
    pwmServo(LASER_SERVO_INDEX_2, 0xFF, 800.0f);
    delaymSec(300.0f);
    pwmServo(LASER_SERVO_INDEX_1, 0xFF, 900.0f);
    pwmServo(LASER_SERVO_INDEX_2, 0xFF, 900.0f);
    delaymSec(300.0f);
    pwmServo(LASER_SERVO_INDEX_1, 0xFF, 800.0f);
    pwmServo(LASER_SERVO_INDEX_2, 0xFF, 800.0f);
}

/**
 * Called when the child joined.
 */ 
void onChildJoined(JennicEvent* jennicEvent) {
    appendString(getInfoOutputStreamLogger(), "CHILD JOINED ! \n");
    setJennicNetworkStatus(JENNIC_LINK_CONNECTED);
    pwmServo(LASER_SERVO_INDEX_1, 0xFF, 1500.0f);
    pwmServo(LASER_SERVO_INDEX_2, 0xFF, 1500.0f);
    delaymSec(500.0f);
    setBeaconSystemEnabled(true);
}

/**
 * Called when the child leave.
 */ 
void onChildLeave(JennicEvent* jennicEvent) {
    appendString(getInfoOutputStreamLogger(), "CHILD LEAVE ! \n");
    setJennicNetworkStatus(JENNIC_WAITING_FOR_NODE);
    setBeaconSystemEnabled(false);
    pwmServo(LASER_SERVO_INDEX_1, 0xFF, 2200.0f);
    pwmServo(LASER_SERVO_INDEX_2, 0xFF, 2200.0f);
    delaymSec(300.0f);
    pwmServo(LASER_SERVO_INDEX_1, 0xFF, 2100.0f);
    pwmServo(LASER_SERVO_INDEX_2, 0xFF, 2100.0f);
    delaymSec(300.0f);
    pwmServo(LASER_SERVO_INDEX_1, 0xFF, 2200.0f);
    pwmServo(LASER_SERVO_INDEX_2, 0xFF, 2200.0f);
}

void onData(JennicEvent* jennicEvent) {
    // Manage real Data into the Jennic Buffer
    Buffer* requestBuffer = getJennicInDataBuffer();
    if (!isBufferEmpty(requestBuffer)) {
        // appendString(&debugOutputStream, "\nDATA !");
        // printBuffer(&debugOutputStream, requestBuffer);
        // println(&debugOutputStream);
        // handle it like other source (UART, I2C ...)
        handleStreamInstruction(requestBuffer, &responseDataOutputBuffer, &responseDataOutputStream, &filterRemoveCRLF, NULL);
        onJennicData();
    }
}

void registerJennicEvents() {
    initJennicEventList();
    addJennicEvent(&networkStartEvent, JENNIC_NETWORK_STARTED, "?", JENNIC_COORDINATER_MAC_ADDRESS, NULL, NO_PAY_LOAD, onNetworkStart);
    addJennicEvent(&childJoinedEvent, JENNIC_CHILD_JOINED, JENNIC_ROUTER_MAC_ADDRESS, NULL, NULL, NO_PAY_LOAD, onChildJoined);
    addJennicEvent(&childLeaveEvent, JENNIC_CHILD_LEAVE, JENNIC_ROUTER_MAC_ADDRESS, NULL, NULL, NO_PAY_LOAD, onChildLeave);
    addJennicEvent(&errorEvent, JENNIC_RESPONSE_ERROR, NULL, NULL, NULL, NO_PAY_LOAD, onError);
    // WARN : Length of data must be > 9 in hexadecimal (because size is on 2 char)
    addJennicEvent(&dataEvent, JENNIC_RECEIVE_DATA, JENNIC_ROUTER_MAC_ADDRESS, "0", "???", 4, onData);
}

void showJennicLinkState() {
    // TODO
}

Buffer* getZigbeeInputBuffer() {
    return &zigbeeInputBuffer;
}

int main(void) {
restart:

    initBeaconIO();

    // zigBee link
    openSerialLink(&zigbeeSerialStreamLink,
            &zigbeeInputBuffer,
            &zigbeeInputBufferArray,
            JENNIC_ZIGBEE_INPUT_BUFFER_LENGTH,
            &zigbeeOutputBuffer,
            &zigbeeOutputBufferArray,
            JENNIC_ZIGBEE_OUTPUT_BUFFER_LENGTH,
            &zigbeeOutputStream,
            SERIAL_PORT_ZIGBEE,
            115200);

    // Debug link
    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            JENNIC_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            JENNIC_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG,
            115200
        );

    initTimerList(&timerListArray, BEACON_BOARD_TIMER_LENGTH);

    // To response data
    initBuffer(&responseDataOutputBuffer, &responseDataOutputBufferArray, RESPONSE_DATA_OUTPUT_BUFFER_LENGTH, "responseDataOutputBuffer", "RESPONSE");
    initZigbeeOutputStream(&responseDataOutputStream, &responseDataOutputBuffer, JENNIC_ROUTER_MAC_ADDRESS);

    // Init the logs
    initLogs(DEBUG, &logHandlerListArray, BEACON_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addLogHandler("UART", &debugOutputStream, DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendString(getInfoOutputStreamLogger(), "BEACON BOARD MAIN \n");
    appendCRLF(getInfoOutputStreamLogger());
    setBoardName("BEACON BOARD MAIN");

    // Init Devices
    initLaserDetectorSettings();
    initDevicesDescriptor();

    // Zigbee Dispatcher
    addZigbeeDriverDataDispatcher(&beaconReceiverDispatcher,
                                    "BEACON_RECEIVER_DISPATCHER",
                                    &beaconReceiverInputStream,
                                    &beaconReceiverOutputStream,
                                    JENNIC_ROUTER_MAC_ADDRESS);

    initDriversDescriptor();

    // Start interruptions
    printTimerList(&debugOutputStream, getTimerList());
    startTimerList();

    // To Avoid Rotation at startup Time. The beacon will be activated as soon the network will be connected
    // to receiver
    setBeaconSystemEnabled(false);

    InputStream* zigbeeInputStream = getInputStream(&zigbeeInputBuffer);
    InputStream* debugInputStream = getInputStream(&debugInputBuffer);

    // Init coordinater streams
    initJennic5139Streams(zigbeeInputStream, &zigbeeOutputStream, &debugOutputStream);
    registerJennicEvents();
    printJennicEventList(&debugOutputStream);

    // Initialisation is done by serial command    
    initJennic5139Coordinater();

    initBeaconIO();

    while (1) {
    
        // Copy data from the Jennic to the debug outputStream
        copyFromZigbeeToDebugRetainingData();

        // Redirect to Devices
        if (isCommandRedirectToDevices()) {
            // Handle debug
            handleStreamInstruction(&debugInputBuffer, &debugOutputBuffer, &debugOutputStream, &filterRemoveCRLF, NULL);
        }
        else {
            if (isBufferEmpty(&debugInputBuffer)) {
                continue;
            }
            // Detects if we want to redirect to devices
            /*
            if (bufferGetFirstChar(&debugInputBuffer) == '@') {
                appendString(getInfoOutputStreamLogger(), "REDIRECT COMMAND TO DEVICES \n");
                // delete the '@' char from the buffer
                bufferReadChar(&debugInputBuffer);
                setCommandRedirectToDevices();
                // Redirect to Jennic and not to the devices
                continue;
            }
            // Copy char entered on debug -> JENNIC
            copyInputToOutputStream(debugInputStream, &zigbeeOutputStream, NULL, COPY_ALL);
            */
        }
        // Try to notify each Time the robot position through the zigbee
        notifyRobotPositionIfNecessary();
    }
    goto restart;
}

