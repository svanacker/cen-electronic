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
static IOExpander* tofIoExpander;
static IOExpander ioExpanderArray[MAIN_BOARD_IO_EXPANDER_LIST_LENGTH];
static I2cBusConnection* tofIoExpanderBusConnection;

// TOF
static TofSensorList tofSensorList;
static TofSensor tofSensorArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];
static TofSensorVL53L0X tofSensorVL53L0XArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];

void mainBoardCommonTofAddDevices(void) {
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(&tofSensorList));
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));
}

void mainBoardCommonTofInitDrivers(I2cBus* i2cBus) {
    // IO Expander
    appendString(getDebugOutputStreamLogger(), "PCF ...");
    tofIoExpanderBusConnection = addI2cBusConnection(i2cBus, PCF8574_ADDRESS_0, true);
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) &ioExpanderArray, MAIN_BOARD_IO_EXPANDER_LIST_LENGTH);
    tofIoExpander = getIOExpanderByIndex(&ioExpanderList, 0);
    initIOExpanderPCF8574(tofIoExpander, tofIoExpanderBusConnection);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
        
    // TOF
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 0) {
        tofSensorArray[0].enabled = true;        
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 1) {
        tofSensorArray[1].enabled = true;        
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 2) {
        tofSensorArray[2].enabled = true;        
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 3) {
        tofSensorArray[3].enabled = true;        
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 4) {
        tofSensorArray[4].enabled = true;        
    }    
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 5) {
        tofSensorArray[5].enabled = true;        
    }
    appendStringLN(getDebugOutputStreamLogger(), "TOF ...");
    initTofSensorListVL53L0X(&tofSensorList,
                             (TofSensor(*)[]) &tofSensorArray,
                             (TofSensorVL53L0X(*)[]) &tofSensorVL53L0XArray,
                              // Size
                              MAIN_BOARD_TOF_SENSOR_LIST_LENGTH,
                              i2cBus,
                              // IO Expander, if null, we will not be able to
                              // Manage several tof
                              // tofIoExpander,
            NULL,
                              // debug
                              true,
                              // enabledAllSensors
                              false,
                              // changeAddressAllSensors
            false
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