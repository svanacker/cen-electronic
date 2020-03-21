#include "mainBoardCommonTof32.h"
#include "mainBoardCommonTof.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

#include "../../device/deviceList.h"

// IO Expander
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"
#include "../../device/ioExpander/ioExpanderDevice.h"

// Multiplexer
#include "../../device/i2c/multiplexer/multiplexerDeviceInterface.h"
#include "../../device/i2c/multiplexer/multiplexerDevice.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// -> IO EXPANDER
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/ioExpanderPcf8574.h"
#include "../../drivers/ioExpander/pcf8574.h"

// MULTIPLEXER
#include "../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../drivers/i2c/multiplexer/multiplexerDebug.h"
#include "../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../drivers/i2c/multiplexer/multiplexerTca9548A.h"
#include "../../drivers/i2c/multiplexer/tca9548A.h"

// TOF
#include "../../drivers/tof/vl53l0x/tof_vl53l0x.h"
#include "../../drivers/tof/vl53l0x/tofList_vl53l0x.h"

// 2019 Specific
#include "../../robot/2019/fork/forkScan2019.h"
#include "../../robot/2019/strategy/strategyConfig2019.h"

// IO Expander
static IOExpanderList ioExpanderList;
static IOExpander ioExpanderArray[MAIN_BOARD_IO_EXPANDER_LIST_LENGTH];

// Multiplexer
static MultiplexerList multiplexerList;
static Multiplexer multiplexerArray[MAIN_BOARD_MULTIPLEXER_LIST_LENGTH];

// SPECIFIC TOF
static TofSensorVL53L0X tofSensorVL53L0XArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];

void mainBoardCommonTofAddDevices32(void) {
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(mainBoardCommonTofGetTofSensorList()));
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));
    addLocalDevice(getMultiplexerDeviceInterface(), getMultiplexerDeviceDescriptor(&multiplexerList));
}

void mainBoardCommonIOExpanderListInitDrivers32(void) {
    I2cBus* ioExpanderBus = getI2cBusByIndex(MAIN_BOARD_TOF_EXPANDER_BUS_INDEX);
    // IO Expander List
    appendString(getDebugOutputStreamLogger(), "IO Expander List ...");
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) & ioExpanderArray, MAIN_BOARD_IO_EXPANDER_LIST_LENGTH);

    // -> IO Expander (either classical or IOButtonBoard)
    IOExpander* ioExpander = getIOExpanderByIndex(&ioExpanderList, 0);
    I2cBusConnection* ioExpanderBusConnection = addI2cBusConnection(ioExpanderBus, PCF8574_ADDRESS_0, true);
    initIOExpanderPCF8574(ioExpander, ioExpanderBusConnection);
    // We need to be sure that the VL530X will not be reseted by the IO Expander
    ioExpander->ioExpanderWriteValue(ioExpander, 0xFF);

    // End of IOExpanderList
    appendStringLN(getDebugOutputStreamLogger(), "OK");
}

MultiplexerList* mainBoardCommonMultiplexerListInitDrivers32(void) {
    I2cBus* multiplexerBus = getI2cBusByIndex(MAIN_BOARD_MULTIPLEXER_BUS_INDEX);
    appendString(getDebugOutputStreamLogger(), "Multiplexer List ...");
    initMultiplexerList(&multiplexerList, (Multiplexer(*)[]) & multiplexerArray, MAIN_BOARD_MULTIPLEXER_LIST_LENGTH);

    // -> Multiplexer 0 Board
    Multiplexer* multiplexerExpander0 = getMultiplexerByIndex(&multiplexerList, 0);
    I2cBusConnection* multiplexerBoardBusConnection0 = addI2cBusConnection(multiplexerBus, TCA9548A_ADDRESS_0, true);
    initMultiplexerTca9548A(multiplexerExpander0, multiplexerBoardBusConnection0, true);

    // -> Multiplexer 1 Board
    Multiplexer* multiplexerExpander1 = getMultiplexerByIndex(&multiplexerList, 1);
    I2cBusConnection* multiplexerBoardBusConnection1 = addI2cBusConnection(multiplexerBus, TCA9548A_ADDRESS_1, true);
    initMultiplexerTca9548A(multiplexerExpander1, multiplexerBoardBusConnection1, true);

    appendStringLN(getDebugOutputStreamLogger(), "OK");

    return &multiplexerList;
}

void mainBoardCommonTofInitDrivers32(RobotConfig* robotConfig) {
    // IO Expander List
    mainBoardCommonIOExpanderListInitDrivers32();

    // Multiplexer List
    mainBoardCommonMultiplexerListInitDrivers32();

    TofSensorList* tofSensorList = mainBoardCommonTofInitDrivers(robotConfig, &multiplexerList, &ioExpanderList);

    // HARDWARE Initialization
    appendStringLN(getDebugOutputStreamLogger(), "TOF ...");
    initTofSensorListVL53L0X(mainBoardCommonTofGetTofSensorList(),
            (TofSensor(*)[]) tofSensorList->tofSensorArray,
            (TofSensorVL53L0X(*)[]) & tofSensorVL53L0XArray,
            // Size
            MAIN_BOARD_TOF_SENSOR_LIST_LENGTH,
            // debug
            true
            );

    // BEEP
    IOExpander* beepIOExpander = getIOExpanderByIndex(&ioExpanderList, MAIN_BOARD_TOF_BEEP_IO_EXPANDER_INDEX);
    initTofSensorListBeep(tofSensorList,
            beepIOExpander,
            MAIN_BOARD_TOF_BEEP_IO_EXPANDER_GROUND_PIN_INDEX,
            MAIN_BOARD_TOF_BEEP_IO_EXPANDER_VCC_PIN_INDEX);

    appendStringLN(getDebugOutputStreamLogger(), "OK");
}
