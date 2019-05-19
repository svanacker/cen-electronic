#include "mainBoardCommonTof.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../device/deviceList.h"

// IO Expander
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"
#include "../../device/ioExpander/ioExpanderDevice.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// -> IO EXPANDER
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/ioExpanderPcf8574.h"
#include "../../drivers/ioExpander/pcf8574.h"

// TOF
#include "../../drivers/tof/vl53l0x/tof_vl53l0x.h"
#include "../../drivers/tof/vl53l0x/tofList_vl53l0x.h"

// IO Expander
static IOExpanderList ioExpanderList;
static IOExpander ioExpanderArray[MAIN_BOARD_IO_EXPANDER_LIST_LENGTH];

// TOF
static TofSensorList tofSensorList;
static TofSensor tofSensorArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];
static TofSensorVL53L0X tofSensorVL53L0XArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];

void mainBoardCommonTofAddDevices(void) {
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(&tofSensorList));
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));
}

void mainBoardCommonTofInitDrivers(I2cBus* i2cBus, I2cBus* i2cBus2, unsigned int tofSensorCount) {
    // IO Expander List
    appendString(getDebugOutputStreamLogger(), "IO Expander List ...");
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) &ioExpanderArray, MAIN_BOARD_IO_EXPANDER_LIST_LENGTH);
    
        // -> IO Button Board
    /*
    ioButtonBoardIoExpander = getIOExpanderByIndex(&ioExpanderList, 2);
    appendString(getDebugOutputStreamLogger(), "IO Button Board ...");
    ioButtonBoardBusConnection = addI2cBusConnection(i2cBus2, PCF8574_ADDRESS_0);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    initIOExpanderPCF8574(ioButtonBoardIoExpander, ioButtonBoardBusConnection);
    */

    // End of IOExpanderList
    appendStringLN(getDebugOutputStreamLogger(), "OK");
        
    // TOF
    if (tofSensorCount > 0) {
        tofSensorArray[0].enabled = true;
        tofSensorArray[0].useMultiplexer = true;
        tofSensorArray[0].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[0].multiplexerChannel = 1;
    }
    if (tofSensorCount > 1) {
        tofSensorArray[1].enabled = true; 
        tofSensorArray[1].useMultiplexer = true;
        tofSensorArray[1].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[1].multiplexerChannel = 2;
    }
    if (tofSensorCount > 2) {
        tofSensorArray[2].enabled = true;
        tofSensorArray[2].useMultiplexer = true;
        tofSensorArray[2].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[2].multiplexerChannel = 4;
    }
    if (tofSensorCount > 3) {
        tofSensorArray[3].enabled = true;
        tofSensorArray[3].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[3].useMultiplexer = true;
        tofSensorArray[3].multiplexerChannel = 8;
    }
    if (tofSensorCount > 4) {
        tofSensorArray[4].enabled = true;
        tofSensorArray[4].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[4].useMultiplexer = true;
        tofSensorArray[4].multiplexerChannel = 16;
    }    
    if (tofSensorCount > 5) {
        tofSensorArray[5].enabled = true;
        tofSensorArray[5].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[5].useMultiplexer = true;
        tofSensorArray[5].multiplexerChannel = 32;
    }
    if (tofSensorCount > 6) {
        tofSensorArray[6].enabled = false;
        tofSensorArray[6].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[6].useMultiplexer = true;
        tofSensorArray[6].multiplexerChannel = 64;

    }
    if (tofSensorCount > 7) {
        tofSensorArray[7].enabled = false;
        tofSensorArray[7].multiplexerAddress = TCA9548A_ADDRESS_1;
        tofSensorArray[7].useMultiplexer = true;
        tofSensorArray[7].multiplexerChannel = 128;
    }
    // TCA9548A_ADDRESS_0 -----------------------------------------
    if (tofSensorCount > 8) {
        tofSensorArray[8].enabled = true;
        tofSensorArray[8].multiplexerAddress = TCA9548A_ADDRESS_0;
        tofSensorArray[8].useMultiplexer = true;
        tofSensorArray[8].multiplexerChannel = 1;
    }
    if (tofSensorCount > 9) {
        tofSensorArray[9].enabled = true;
        tofSensorArray[9].multiplexerAddress = TCA9548A_ADDRESS_0;
        tofSensorArray[9].useMultiplexer = true;
        tofSensorArray[9].multiplexerChannel = 2;
    }
    if (tofSensorCount > 10) {
        tofSensorArray[10].enabled = true;
        tofSensorArray[10].multiplexerAddress = TCA9548A_ADDRESS_0;
        tofSensorArray[10].useMultiplexer = true;
        tofSensorArray[10].multiplexerChannel = 4;
    }
    if (tofSensorCount > 11) {
        tofSensorArray[11].enabled = true;
        tofSensorArray[11].multiplexerAddress = TCA9548A_ADDRESS_0;
        tofSensorArray[11].useMultiplexer = true;
        tofSensorArray[11].multiplexerChannel = 8;
    }
    if (tofSensorCount > 12) {
        tofSensorArray[12].enabled = true;
        tofSensorArray[12].multiplexerAddress = TCA9548A_ADDRESS_0;
        tofSensorArray[12].useMultiplexer = true;
        tofSensorArray[12].multiplexerChannel = 16;
    }
    if (tofSensorCount > 13) {
        tofSensorArray[13].enabled = true;
        tofSensorArray[13].multiplexerAddress = TCA9548A_ADDRESS_0;
        tofSensorArray[13].useMultiplexer = true;
        tofSensorArray[13].multiplexerChannel = 32;
    }
    
    appendStringLN(getDebugOutputStreamLogger(), "TOF ...");
    initTofSensorListVL53L0X(&tofSensorList,
                             (TofSensor(*)[]) &tofSensorArray,
                             (TofSensorVL53L0X(*)[]) &tofSensorVL53L0XArray,
                              // Size
                              tofSensorCount,
                              // debug
                              true,
                              // enabledAllSensors
                              false,
                              // changeAddressAllSensors
                              true
            );

    appendStringLN(getDebugOutputStreamLogger(), "OK");
    /*
    // -> Color : IMPORTANT !!! : Initialize COLOR after TOF because they share the same address
    // And not the same bus, but it uses "getI2cBusConnectionBySlaveAddress" ... which does not distinguish the bus ...
    appendStringLN(getDebugOutputStreamLogger(), "COLOR ...");
    colorBusConnection = addI2cBusConnection(i2cBus4, TCS34725_ADDRESS, true);
    initTcs34725Struct(&tcs34725, colorBusConnection);
    initColorSensorTcs34725(&colorSensor, &colorValue, &colorSensorFindColorType2018, &tcs34725);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    */
}

TofSensorList* mainBoardCommonTofGetTofSensorList(void) {
    return &tofSensorList;
}

void mainBoardCommonTofHandleStreamInstruction(void) {

}