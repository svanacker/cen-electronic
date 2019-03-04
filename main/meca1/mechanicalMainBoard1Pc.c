#include "mechanicalMainBoard1Pc.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../common/clock/clock.h"
#include "../../common/delay/cenDelay.h"
#include "../../common/eeprom/pc/eepromPc.h"
#include "../../common/error/error.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/slave/pc/i2cSlavePc.h"
#include "../../common/i2c/slave/pc/i2cSlaveSetupPc.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/io/pc/consoleInputStream.h"
#include "../../common/io/filter.h"
#include "../../common/io/streamLink.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/pc/consoleLogHandler.h"
#include "../../common/motor/dualHBridgeMotor.h"
#include "../../common/motor/pc/dualHBridgeMotorPc.h"
#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"
#include "../../common/serial/serialLinkList.h"

#include "../../common/system/system.h"

#include "../../common/timer/timerList.h"


#include "../../device/device.h"
#include "../../device/deviceList.h"

// I2C
#include "../../device/i2c/i2cCommonDebugDevice.h"
#include "../../device/i2c/i2cCommonDebugDeviceInterface.h"

// I2C -> Slave
#include "../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

// CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// IO
#include "../../device/ioExpander/ioExpanderDevice.h"
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"

// MD22
#include "../../device/motor/md22Device.h"
#include "../../device/motor/md22DeviceInterface.h"

// LOG
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// RELAY
#include "../../device/relay/relayDevice.h"
#include "../../device/relay/relayDeviceInterface.h"

// TIMERS
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/driverList.h"
#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../drivers/test/testDriver.h"

#include "../../drivers/battery/battery.h"

#include "../../drivers/clock/softClock.h"

#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/pc/ioExpanderPc.h"

#include "../../motion/motion.h"

#include "../../motion/pid/pidMotion.h"

#include "../../drivers/relay/relay.h"
#include "../../drivers/relay/pc/relayPc.h"

#include "../../common/pc/process/processHelper.h"

#include "../../main/mainBoard/mainBoardPc.h"

// Logs
static LogHandlerList logHandlerListArray[MECHANICAL_BOARD_1_PC_LOG_HANDLER_LIST_LENGTH];

// Dispatchers
static DriverDataDispatcher driverDataDispatcherListArray[MECHANICAL_BOARD_1_PC_DATA_DISPATCHER_LIST_LENGTH];

// SERIAL
static SerialLink serialLinkListArray[MECHANICAL_BOARD_1_PC_SERIAL_LINK_LIST_LENGTH];

// I2C
static I2cBus i2cBusListArray[MECHANICAL_BOARD_1_PC_I2C_BUS_LIST_LENGTH];
static I2cBusConnection i2cBusConnectionListArray[MECHANICAL_BOARD_1_PC_I2C_BUS_CONNECTION_LIST_LENGTH];

// Timers
static Timer timerListArray[MECHANICAL_BOARD_1_PC_TIMER_LENGTH];

// Logs

// ConsoleOutputStream
static InputStream consoleInputStream;
static OutputStream consoleOutputStream;
static char consoleInputBufferArray[MECHANICAL_BOARD_1_PC_CONSOLE_INPUT_BUFFER_LENGTH];
static Buffer consoleInputBuffer;
static char consoleOutputBufferArray[MECHANICAL_BOARD_1_PC_CONSOLE_OUTPUT_BUFFER_LENGTH];
static Buffer consoleOutputBuffer;

// i2c Link
static char i2cSlaveInputBufferArray[MECHANICAL_BOARD_1_PC_IN_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MECHANICAL_BOARD_1_PC_OUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSlaveStreamLink;

static char i2cSlaveDebugOutputBufferArray[MECHANICAL_BOARD_1_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH];
static Buffer i2cSlaveDebugOutputBuffer;
static char i2cSlaveDebugInputBufferArray[MECHANICAL_BOARD_1_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH];
static Buffer i2cSlaveDebugInputBuffer;

// Eeprom
static Eeprom eeprom;

// Battery
static Battery battery;

// Clock
static Clock clock;

// IOExpander
static IOExpanderList ioExpanderList;
static IOExpander ioExpanderArray[MECHANICAL_BOARD_1_PC_IO_EXPANDER_LIST_LENGTH];
static int ioExpanderValue0;

// I2C
static I2cBus* mechanical1I2cBus;
static I2cBusConnection* mechanical1I2cBusConnection;
static I2cBusConnectionPc mechanical1I2cBusConnectionPc;

// MD22 Fake Motor
static DualHBridgeMotor md22;

// Relay
static Relay relay;
static int relayValue;

// Devices
static Device deviceListArray[MECHANICAL_BOARD_1_PC_DEVICE_LIST_LENGTH];

static bool singleModeActivated = true;

void mechanicalBoard1PcWaitForInstruction(void) {
    // Analyze data from the Console (Specific to PC)
    while (consoleInputStream.availableData(&consoleInputStream)) {
        unsigned char c = consoleInputStream.readChar(&consoleInputStream);
        consoleInputBuffer.outputStream.writeChar(&(consoleInputBuffer.outputStream), c);
        if (c == 13) {
            appendCRLF(&consoleOutputStream);
        }
        consoleOutputStream.writeChar(&consoleOutputStream, c);
    }

    // Analyse from the ConsoleBuffer
    handleStreamInstruction(
        &consoleInputBuffer,
        &consoleOutputBuffer,
        &consoleOutputStream,
        &filterRemoveCRLF,
        NULL);

    if (!singleModeActivated) {
        // Analyse data from the I2C
        handleStreamInstruction(
            &i2cSlaveInputBuffer,
            &i2cSlaveOutputBuffer,
            NULL,
            &filterRemoveCRLF,
            NULL);
    }
}

void runMechanicalBoard1PC(bool singleMode) {
    singleModeActivated = singleMode;
    setBoardName(MECHANICAL_BOARD_1_PC_NAME);
	setConsoleSizeAndBuffer(CONSOLE_CHARS_WIDTH, CONSOLE_CHARS_HEIGHT, CONSOLE_BUFFER_WIDTH, CONSOLE_BUFFER_HEIGHT);
    moveConsole(HALF_SCREEN_WIDTH, CONSOLE_HEIGHT / 2, HALF_SCREEN_WIDTH, CONSOLE_HEIGHT / 2);

    // We use http://patorjk.com/software/taag/#p=display&v=2&f=Jerusalem&t=MECA%20%20%201%20%20%20PC
    // with Font : Jerusalem
    printf(" __  __ _____  ____    _        _     ____   ____\r\n");
    printf("|  \\/  | ____ / ___|  / \\      / |   |  _ \\ / ___|\r\n");
    printf("| |\\/| |  _|| |      / _ \\     | |   | |_) | |\r\n");
    printf("| |  | | |__| |___  / ___ \\    | |   |  __/| |___\r\n");
    printf("|_|  |_| _____\\____/ _ / \\_\\   |_|   |_|    \\____ |\r\n");

    initLogs(LOG_LEVEL_DEBUG, (LogHandler(*)[]) &logHandlerListArray, MECHANICAL_BOARD_1_PC_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    initConsoleInputStream(&consoleInputStream);
    initConsoleOutputStream(&consoleOutputStream);
    addConsoleLogHandler(LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);

	initSerialLinkList((SerialLink(*)[]) &serialLinkListArray, MECHANICAL_BOARD_1_PC_SERIAL_LINK_LIST_LENGTH);

    initTimerList((Timer(*)[]) &timerListArray, MECHANICAL_BOARD_1_PC_TIMER_LENGTH);

    initBuffer(&consoleInputBuffer, (char(*)[]) &consoleInputBufferArray, MECHANICAL_BOARD_1_PC_CONSOLE_INPUT_BUFFER_LENGTH, "inputConsoleBuffer", "IN");
    initBuffer(&consoleOutputBuffer, (char(*)[]) &consoleOutputBufferArray, MECHANICAL_BOARD_1_PC_CONSOLE_OUTPUT_BUFFER_LENGTH, "outputConsoleBuffer", "IN");

    // Dispatchers
    initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, MECHANICAL_BOARD_1_PC_DATA_DISPATCHER_LIST_LENGTH);
    addLocalDriverDataDispatcher();

    if (!singleModeActivated) {
		// I2c
		initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MECHANICAL_BOARD_1_PC_I2C_BUS_LIST_LENGTH);
		mechanical1I2cBus = addI2cBus(I2C_BUS_TYPE_SLAVE, I2C_BUS_PORT_1);

        initI2cBusConnectionList((I2cBusConnection(*)[]) &i2cBusConnectionListArray, MECHANICAL_BOARD_1_PC_I2C_BUS_CONNECTION_LIST_LENGTH);
        mechanical1I2cBusConnection = addI2cBusConnection(mechanical1I2cBus, MECHANICAL_BOARD_1_I2C_ADDRESS, false);
        mechanical1I2cBusConnection->i2cBus = mechanical1I2cBus;
        mechanical1I2cBusConnectionPc.i2cPipeMasterName = MAIN_BOARD_TO_MECA1_BOARD_PC_PIPE_I2C_MASTER_NAME;
        mechanical1I2cBusConnectionPc.i2cPipeSlaveName = MECHANICAL_BOARD_1_PC_PIPE_I2C_SLAVE_NAME;
        mechanical1I2cBusConnection->object = &mechanical1I2cBusConnectionPc;

		openSlaveI2cStreamLink(&i2cSlaveStreamLink,
            &i2cSlaveInputBuffer,
            (char(*)[]) &i2cSlaveInputBufferArray,
            MECHANICAL_BOARD_1_PC_IN_BUFFER_LENGTH,
            &i2cSlaveOutputBuffer,
            (char(*)[]) &i2cSlaveOutputBufferArray,
            MECHANICAL_BOARD_1_PC_OUT_BUFFER_LENGTH,
            mechanical1I2cBusConnection
        );
        // I2C Debug
        initI2CDebugBuffers(&i2cSlaveDebugInputBuffer,
            (char(*)[]) &i2cSlaveDebugInputBufferArray,
            MECHANICAL_BOARD_1_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH,
            &i2cSlaveDebugOutputBuffer,
            (char(*)[]) &i2cSlaveDebugOutputBufferArray,
            MECHANICAL_BOARD_1_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH);
	}

    // Eeprom
    initEepromPc(&eeprom, "MECHANICAL_BOARD_1_PC_EEPROM");

    // Battery
    initBattery(&battery, getBatteryVoltage);
	
    // Clock
    initSoftClock(&clock);

    // HBridge Fake Motor MD22
    initDualHBridgeMotorPc(&md22);

    // 2018
    //  IO Expander
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) &ioExpanderArray, MECHANICAL_BOARD_1_PC_IO_EXPANDER_LIST_LENGTH);
    initIOExpanderPc(getIOExpanderByIndex(&ioExpanderList, MECHANICAL_BOARD_1_PC_IO_EXPANDER_LAUNCHER_INDEX), &ioExpanderValue0);
    IOExpander* launcherIoExpander = getIOExpanderByIndex(&ioExpanderList, MECHANICAL_BOARD_1_PC_IO_EXPANDER_LAUNCHER_INDEX);

    // TODO : Add tof !
    // initLauncher2018(&launcher2018, launcherIoExpander, &relay, &md22, NULL);
 
    // Relay
    initRelayPc(&relay, &relayValue);

    // Devices
    initDeviceList((Device(*)[]) &deviceListArray, MECHANICAL_BOARD_1_PC_DEVICE_LIST_LENGTH);
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
	addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor());
    addLocalDevice(getI2cSlaveDebugDeviceInterface(), getI2cSlaveDebugDeviceDescriptor(mechanical1I2cBusConnection));
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
	addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());

    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));

    // 2018
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));
    addLocalDevice(getRelayDeviceInterface(), getRelayDeviceDescriptor(&relay));
    addLocalDevice(getMD22DeviceInterface(), getMD22DeviceDescriptor(&md22));

    initDevices();

    startTimerList(true);

    setDebugI2cEnabled(false);
    while (1) {
        mechanicalBoard1PcWaitForInstruction();
    }
}