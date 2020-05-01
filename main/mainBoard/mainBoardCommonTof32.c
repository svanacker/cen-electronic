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

// Multiplexer
#include "../../device/i2c/multiplexer/multiplexerDeviceInterface.h"
#include "../../device/i2c/multiplexer/multiplexerDevice.h"

// LED
#include "../../device/led/ledDevice.h"
#include "../../device/led/ledDeviceInterface.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// MULTIPLEXER
#include "../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../drivers/i2c/multiplexer/multiplexerDebug.h"
#include "../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../drivers/i2c/multiplexer/multiplexerTca9548A.h"
#include "../../drivers/i2c/multiplexer/tca9548A.h"

// -> LED
#include "../../drivers/led/led.h"
#include "../../drivers/led/pca9685/ledPca9685.h"

// TOF
#include "../../drivers/tof/vl53l0x/tof_vl53l0x.h"
#include "../../drivers/tof/vl53l0x/tofList_vl53l0x.h"

// 2019 Specific
#include "../../robot/2019/fork/forkScan2019.h"
#include "../../robot/2019/strategy/strategyConfig2019.h"

// Multiplexer
static MultiplexerList multiplexerList;
static Multiplexer multiplexerArray[MAIN_BOARD_MULTIPLEXER_LIST_LENGTH];

// SPECIFIC TOF
static TofSensorVL53L0X tofSensorVL53L0XArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];

// DISTANCE LED
static LedArray ledArray0;
static LedArray ledArray1;
static I2cBusConnection* ledArrayBusConnection0;
static I2cBusConnection* ledArrayBusConnection1;

void mainBoardCommonTofAddDevices32(void) {
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(mainBoardCommonTofGetTofSensorList()));
    addLocalDevice(getMultiplexerDeviceInterface(), getMultiplexerDeviceDescriptor(&multiplexerList));
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

void mainBoardCommonTofInitDrivers32(RobotConfig* robotConfig, IOExpander* beepIOExpander) {
    // Multiplexer List
    mainBoardCommonMultiplexerListInitDrivers32();

    TofSensorList* tofSensorList = mainBoardCommonTofInitDrivers(robotConfig, &multiplexerList);

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
    initTofSensorListBeep(tofSensorList,
            beepIOExpander,
            MAIN_BOARD_TOF_BEEP_IO_EXPANDER_GROUND_PIN_INDEX,
            MAIN_BOARD_TOF_BEEP_IO_EXPANDER_VCC_PIN_INDEX);
     
    // LED ARRAY
    I2cBus* i2cBus = getI2cBusByIndex(MAIN_BOARD_TOF_SENSOR_LIST_BUS_INDEX);
    
    ledArrayBusConnection0 = addI2cBusConnection(i2cBus, PCA9685_ADDRESS_2, true);
    initLedArrayPca9685(&ledArray0, ledArrayBusConnection0);
    
    ledArrayBusConnection1 = addI2cBusConnection(i2cBus, PCA9685_ADDRESS_3, true);
    initLedArrayPca9685(&ledArray1, ledArrayBusConnection1);
    
    initTofSensorListLedArrays(tofSensorList, &ledArray0, &ledArray1);
}
