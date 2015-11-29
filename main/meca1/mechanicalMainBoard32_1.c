#include <peripheral/i2c.h>
#include <stdlib.h>

#include "mechanicalBoard32_1.h"

#include "../../common/setup/32/picSetup32.h"

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
// Clock
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// Servo
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Test
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// Serial
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// Timer
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// Drivers
#include "../../drivers/driverStreamListener.h"
#include "../../drivers/eeprom/24c512.h"


/**
* Device list.
*/
static DeviceList devices;

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
static I2cBus mechanicalBoard1I2cBus;
static I2cBusConnection mechanicalBoard1I2cBusConnection;
static char i2cSlaveInputBufferArray[MECA_BOARD_32_1_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MECA_BOARD_32_1_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// I2C Debug
static char i2cMasterDebugOutputBufferArray[MECA_BOARD_32_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MECA_BOARD_32_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// Timers
static Timer timerListArray[MECA_BOARD_32_1_TIMER_LENGTH];

// Devices
static Device deviceListArray[MECA_BOARD_32_1_DEVICE_LENGTH];

// I2C Bus
static I2cBus mainBoardI2cBus;
static I2cBusConnection mainBoardI2cBusConnection;
static I2cBus eepromI2cBus;
static I2cBusConnection eepromI2cBusConnection;

// Eeprom
static Eeprom eeprom_;

// Clock
static Clock clock;

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MECA_BOARD_32_1_DEVICE_LENGTH);
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());

    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());

    initDevices();
}

int main(void) {
    setBoardName(MECA_BOARD_32_1_NAME);

    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // enable interrupts
    INTEnableInterrupts();

    // Open Standard Serial Link
    openSerialLink(&standardSerialStreamLink,
            &standardInputBuffer,
            &standardInputBufferArray,
            MECA_BOARD_32_1_STANDARD_INPUT_BUFFER_LENGTH,
            &standardOutputBuffer,
            &standardOutputBufferArray,
            MECA_BOARD_32_1_STANDARD_OUTPUT_BUFFER_LENGTH,
            &standardOutputStream,
            MECA_BOARD_32_1_SERIAL_PORT_STANDARD,
            DEFAULT_SERIAL_SPEED);

    // Open Serial Link to enable the Serial LOGS !
    openSerialLink( &debugSerialStreamLink,
                    &debugInputBuffer,
                    &debugInputBufferArray,
                    MECA_BOARD_32_1_DEBUG_INPUT_BUFFER_LENGTH,
                    &debugOutputBuffer,
                    &debugOutputBufferArray,
                    MECA_BOARD_32_1_DEBUG_OUTPUT_BUFFER_LENGTH,
                    &debugOutputStream,
                    MECA_BOARD_32_1_SERIAL_PORT_DEBUG,
                    DEFAULT_SERIAL_SPEED);

    // Init the logs
    initLogs(DEBUG, &logHandlerListArray, MECA_BOARD_32_1_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addLogHandler("UART", &debugOutputStream, DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendString(getDebugOutputStreamLogger(), getBoardName());
    appendCRLF(getDebugOutputStreamLogger());

    initTimerList((Timer(*)[]) &timerListArray, MECA_BOARD_32_1_TIMER_LENGTH);
    startTimerList();

    initI2cBus(&mechanicalBoard1I2cBus, I2C_BUS_TYPE_SLAVE, I2C_BUS_PORT_1);
    initI2cBusConnection(&mechanicalBoard1I2cBusConnection, &mechanicalBoard1I2cBus, MECA_BOARD_32_1_I2C_ADDRESS);

    openSlaveI2cStreamLink(&i2cSerialStreamLink,
                            &i2cSlaveInputBuffer,
                            &i2cSlaveInputBufferArray,
                            MECA_BOARD_32_1_I2C_INPUT_BUFFER_LENGTH,
                            &i2cSlaveOutputBuffer,
                            &i2cSlaveOutputBufferArray,
                            MECA_BOARD_32_1_I2C_OUTPUT_BUFFER_LENGTH,
                            &mechanicalBoard1I2cBusConnection
                        );

    // Debug of I2C : Only if there is problems
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
        (char(*)[]) &i2cMasterDebugInputBufferArray,
        MECA_BOARD_32_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
        &i2cMasterDebugOutputBuffer,
        (char(*)[]) &i2cMasterDebugOutputBufferArray,
        MECA_BOARD_32_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    setDebugI2cEnabled(false);

    // Eeprom
    initI2cBus(&eepromI2cBus, I2C_BUS_TYPE_MASTER, MECA_BOARD_32_I2C_MASTER_PORT);
    i2cMasterInitialize(&eepromI2cBus);
    initI2cBusConnection(&eepromI2cBusConnection, &eepromI2cBus, /* TODO */ 0);
    init24C512Eeprom(&eeprom_, &eepromI2cBusConnection);

    // Clock
    initSoftClock(&clock);

    // init the devices
    initDevicesDescriptor();

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
    }
    return (0);
}
