#define _SUPPRESS_PLIB_WARNING
#include <peripheral/i2c.h>
#include <stdlib.h>
#include <stdint.h>

#include "mechanicalMainBoard32_1.h"

#include "../../common/setup/32/picSetup32.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"

#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"

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

// DEVICES
// -> Clock
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// -> Eeprom
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// IO Expander
#include "../../device/ioExpander/ioExpanderDevice.h"
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"

// -> Motors (MD22)
#include "../../device/motor/md22Device.h"
#include "../../device/motor/md22DeviceInterface.h"

// -> Servo
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// -> System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// -> Test
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// -> Serial
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// -> Relay
#include "../../device/relay/relayDevice.h"
#include "../../device/relay/relayDeviceInterface.h"

// -> Timer
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// -> 2018
#include "../../robot/2018/launcherDevice2018.h"
#include "../../robot/2018/launcherDeviceInterface2018.h"

// DRIVERS
#include "../../drivers/driverStreamListener.h"

// Eeprom
#include "../../drivers/eeprom/24c512.h"

// -> IO Expander
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/ioExpanderPcf8574.h"
#include "../../drivers/ioExpander/pcf8574.h"

// -> MOTOR
#include "../../drivers/motor/dualHBridgeMotorMd22.h"
#include "../../drivers/motor/md22.h"

// -> Relay
#include "../../drivers/relay/rly08.h"

// TOF
#include "../../drivers/tof/vl53l0x/tof_vl53l0x.h"
#include "../../drivers/tof/vl53l0x/tofList_vl53l0x.h"

/**
* Device list.
*/
static DeviceList devices;

// SERIAL
static SerialLink serialLinkListArray[MECA_BOARD_32_1_SERIAL_LINK_LIST_LENGTH];

// I2C
static I2cBus i2cBusListArray[MECA_BOARD_32_1_I2C_BUS_LIST_LENGTH];
static I2cBusConnection i2cBusConnectionListArray[MECA_BOARD_32_1_I2C_BUS_CONNECTION_LIST_LENGTH];

// serial STANDARD
static char standardInputBufferArray[MECA_BOARD_32_1_STANDARD_INPUT_BUFFER_LENGTH];
static Buffer standardInputBuffer;
static char standardOutputBufferArray[MECA_BOARD_32_1_STANDARD_OUTPUT_BUFFER_LENGTH];
static Buffer standardOutputBuffer;
static OutputStream standardOutputStream;
static StreamLink standardSerialStreamLink;

// serial DEBUG 
static char debugInputBufferArray[MECA_BOARD_32_1_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MECA_BOARD_32_1_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler logHandlerListArray[MECA_BOARD_32_1_LOG_HANDLER_LIST_LENGTH];

// i2c Link
static I2cBus* mechanicalBoard1SlaveI2cBus;
static I2cBusConnection* mechanicalBoard1SlaveI2cBusConnection;
static char i2cSlaveInputBufferArray[MECA_BOARD_32_1_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MECA_BOARD_32_1_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSlaveStreamLink;

// I2C Debug
static char i2cMasterDebugOutputBufferArray[MECA_BOARD_32_1_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MECA_BOARD_32_1_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// MOTOR (for MD22)
static DualHBridgeMotor md22;
static bool manualSwitchLeft;
static bool manualSwitchRight;

// Timers
static Timer timerListArray[MECA_BOARD_32_1_TIMER_LENGTH];

// Devices
static Device deviceListArray[MECA_BOARD_32_1_DEVICE_LENGTH];

// Master I2C Bus
static I2cBus* masterI2cBus;
static I2cBusConnection* eepromI2cBusConnection;
static I2cBusConnection* relayBusConnection;
static I2cBusConnection* ioExpanderBusConnection;
static I2cBusConnection* md22BusConnection;

// Clock
static Clock clock;

// IO Expander
static IOExpanderList ioExpanderList;
static IOExpander ioExpanderArray[MECA_BOARD_32_1_IO_EXPANDER_LIST_LENGTH];

// Eeprom
static Eeprom eeprom_;

// Relay
static Relay relay;

// TOF
static TofSensorList tofSensorList;
static TofSensor tofSensorArray[MECA_BOARD_32_1_TOF_SENSOR_LIST_LENGTH];
static TofSensorVL53L0X tofSensorVL53L0XArray[MECA_BOARD_32_1_TOF_SENSOR_LIST_LENGTH];

// 2018 Specific
static Launcher2018 launcher2018;

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MECA_BOARD_32_1_DEVICE_LENGTH);
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor(PWM_SERVO_ENABLED_MASK_SERVO_ALL));

    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom_));
    
    // 2018 Specific
    addLocalDevice(getRelayDeviceInterface(), getRelayDeviceDescriptor(&relay));
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));
    addLocalDevice(getLauncher2018DeviceInterface(), getLauncher2018DeviceDescriptor(&launcher2018));
    addLocalDevice(getMD22DeviceInterface(), getMD22DeviceDescriptor(&md22));
    
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(&tofSensorList));

    initDevices();
}

void handleGrabber(void) {
    IOExpander* ioExpander = getIOExpanderByIndex(&ioExpanderList, MECA_BOARD_32_1_IO_EXPANDER_LAUNCHER_INDEX);
    bool newManualSwitchLeft = ioExpander->ioExpanderReadSingleValue(ioExpander, DISTRIBUTOR_ROTATE_LEFT_IO_EXPANDER_INDEX);
    bool newManualSwitchRight = ioExpander->ioExpanderReadSingleValue(ioExpander, DISTRIBUTOR_ROTATE_RIGHT_IO_EXPANDER_INDEX);
    if (newManualSwitchLeft == 0) {
        setMotorSpeeds(&md22, LAUNCHER_2018_DEFAULT_SPEED, 0);
    }
    if (newManualSwitchRight == 0) {
        setMotorSpeeds(&md22, -LAUNCHER_2018_DEFAULT_SPEED, 0);
    }
    else {
        // Stop Motors only if we have a change to avoid to stop Motors because of the continuous call to this method
        if ((manualSwitchLeft !=  newManualSwitchLeft) || (manualSwitchRight != newManualSwitchRight)) {
            stopMotors(&md22);
        }
    }
    manualSwitchLeft = newManualSwitchLeft;
    manualSwitchRight = newManualSwitchRight;
    
}

int main(void) {
    setBoardName(MECA_BOARD_32_1_NAME);

    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // enable interrupts
    INTEnableInterrupts();
    
    // Init the serial List
    initSerialLinkList(&serialLinkListArray, MECA_BOARD_32_1_SERIAL_LINK_LIST_LENGTH);

    // Open Standard Serial Link
    openSerialLink(&standardSerialStreamLink,
		    "SERIAL_MAIN",
            &standardInputBuffer, &standardInputBufferArray, MECA_BOARD_32_1_STANDARD_INPUT_BUFFER_LENGTH,
            &standardOutputBuffer, &standardOutputBufferArray, MECA_BOARD_32_1_STANDARD_OUTPUT_BUFFER_LENGTH,
            &standardOutputStream,
            MECA_BOARD_32_1_SERIAL_PORT_STANDARD,
            DEFAULT_SERIAL_SPEED);

    // Open Serial Link to enable the Serial LOGS !
    openSerialLink( &debugSerialStreamLink,
                    "SERIAL_DEBUG",
                    &debugInputBuffer, &debugInputBufferArray, MECA_BOARD_32_1_DEBUG_INPUT_BUFFER_LENGTH,
                    &debugOutputBuffer, &debugOutputBufferArray, MECA_BOARD_32_1_DEBUG_OUTPUT_BUFFER_LENGTH,
                    &debugOutputStream,
                    MECA_BOARD_32_1_SERIAL_PORT_DEBUG,
                    DEFAULT_SERIAL_SPEED);

    // Init the logs
    initLogs(LOG_LEVEL_DEBUG, &logHandlerListArray, MECA_BOARD_32_1_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addLogHandler("UART", &debugOutputStream, LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendString(getDebugOutputStreamLogger(), getBoardName());
    appendCRLF(getDebugOutputStreamLogger());

    initTimerList((Timer(*)[]) &timerListArray, MECA_BOARD_32_1_TIMER_LENGTH);

    // I2c
	initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MECA_BOARD_32_1_I2C_BUS_LIST_LENGTH);
	initI2cBusConnectionList((I2cBusConnection(*)[]) &i2cBusConnectionListArray, MECA_BOARD_32_1_I2C_BUS_CONNECTION_LIST_LENGTH);
    
    // I2C Slave (to connect with MainBoard32)
    mechanicalBoard1SlaveI2cBus = addI2cBus(I2C_BUS_TYPE_SLAVE, I2C_BUS_PORT_1);
    mechanicalBoard1SlaveI2cBusConnection = addI2cBusConnection(mechanicalBoard1SlaveI2cBus, MECHANICAL_BOARD_1_I2C_ADDRESS, true);
    openSlaveI2cStreamLink(&i2cSlaveStreamLink,
            &i2cSlaveInputBuffer,
            &i2cSlaveInputBufferArray,
            MECA_BOARD_32_1_I2C_INPUT_BUFFER_LENGTH,
            &i2cSlaveOutputBuffer,
            &i2cSlaveOutputBufferArray,
            MECA_BOARD_32_1_I2C_OUTPUT_BUFFER_LENGTH,
            // NULL, 
            mechanicalBoard1SlaveI2cBusConnection
            );

    // Debug of I2C : Only if there is problems
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
        (char(*)[]) &i2cMasterDebugInputBufferArray,
        MECA_BOARD_32_1_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
        &i2cMasterDebugOutputBuffer,
        (char(*)[]) &i2cMasterDebugOutputBufferArray,
        MECA_BOARD_32_1_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    setDebugI2cEnabled(false);

    // Clock
    initSoftClock(&clock);
    
    // I2C Master
    masterI2cBus = addI2cBus(I2C_BUS_TYPE_MASTER, MECA_BOARD_32_1_I2C_MASTER_PORT);
    i2cMasterInitialize(masterI2cBus);

    // Eeprom
    eepromI2cBusConnection = addI2cBusConnection(masterI2cBus, ST24C512_ADDRESS_0, true);
    init24C512Eeprom(&eeprom_, eepromI2cBusConnection);
    
    // IO Expander
    ioExpanderBusConnection = addI2cBusConnection(masterI2cBus, PCF8574_ADDRESS_1, true);
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) &ioExpanderArray, MECA_BOARD_32_1_IO_EXPANDER_LIST_LENGTH);
    IOExpander* launcherIoExpander = getIOExpanderByIndex(&ioExpanderList, MECA_BOARD_32_1_IO_EXPANDER_LAUNCHER_INDEX);
    initIOExpanderPCF8574(launcherIoExpander, ioExpanderBusConnection);
    
    // Motor
    md22BusConnection = addI2cBusConnection(masterI2cBus, MD22_ADDRESS_0, true);
    initDualHBridgeMotorMD22(&md22, md22BusConnection);

    // Relay
    relayBusConnection = addI2cBusConnection(masterI2cBus, RLY08_ADDRESS_0, true);
    initRelayRLY08(&relay, relayBusConnection);

    // TOF
    initTofSensorListVL53L0X(&tofSensorList,
                             (TofSensor(*)[]) &tofSensorArray,
                             (TofSensorVL53L0X(*)[]) &tofSensorVL53L0XArray,
                              MECA_BOARD_32_1_TOF_SENSOR_LIST_LENGTH,
                              masterI2cBus,
                              launcherIoExpander);
    
    // 2018
    initLauncher2018(&launcher2018, launcherIoExpander, &relay, &md22, &tofSensorList);

    // init the devices
    initDevicesDescriptor();
    
    // Init the timers management
    startTimerList(true);

    while (1) {

        // I2C Stream
        handleStreamInstruction(&i2cSlaveInputBuffer,
                                &i2cSlaveOutputBuffer,
                                NULL,
                                &filterRemoveCRLF,
                                NULL);

        // UART Stream
        handleStreamInstruction(&standardInputBuffer,
                                &standardOutputBuffer,
                                &standardOutputStream,
                                &filterRemoveCRLF,
                                NULL);

        // UART Stream
        handleStreamInstruction(&debugInputBuffer,
                                &debugOutputBuffer,
                                &debugOutputStream,
                                &filterRemoveCRLF,
                                NULL);
        
        // HANDLE IO Expander
        handleGrabber();
    }
    return (0);
}
