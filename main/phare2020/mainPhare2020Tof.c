#include "mainPhare2020Tof.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../device/deviceList.h"

#include "../../device/i2c/multiplexer/multiplexerDevice.h"
#include "../../device/i2c/multiplexer/multiplexerDeviceInterface.h"

#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// IO Expander
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"
#include "../../device/ioExpander/ioExpanderDevice.h"

// MULTIPLEXERS
#include "../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../drivers/i2c/multiplexer/multiplexerTca9548A.h"

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
static IOExpander ioExpanderArray[MAIN_PHARE_2020_IO_EXPANDER_LIST_LENGTH];

// Multiplexer
static MultiplexerList multiplexerList;
static Multiplexer multiplexerArray[MAIN_PHARE_2020_MULTIPLEXER_LIST_LENGTH];

// TOF
static TofSensorList tofSensorList;
static TofSensor tofSensorArray[MAIN_PHARE_2020_TOF_SENSOR_LIST_COUNT];
static TofSensorVL53L0X tofSensorVL53L0XArray[MAIN_PHARE_2020_TOF_SENSOR_LIST_COUNT];

void mainLightHouse2020TofAddDevices(void) {
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(&tofSensorList));
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));
    addLocalDevice(getMultiplexerDeviceInterface(), getMultiplexerDeviceDescriptor(&multiplexerList));
}

void mainBoardLightHouse2020IOExpanderListInitDrivers(I2cBus* i2cBus) {
    // IO Expander List
    appendString(getDebugOutputStreamLogger(), "IO Expander List ...");
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) &ioExpanderArray, MAIN_PHARE_2020_IO_EXPANDER_LIST_LENGTH);
    
    // -> IO Button Board
    IOExpander* ioButtonBoardIoExpander = getIOExpanderByIndex(&ioExpanderList, 0);
    I2cBusConnection* ioButtonBoardBusConnection = addI2cBusConnection(i2cBus, PCF8574_ADDRESS_0, true);
    initIOExpanderPCF8574(ioButtonBoardIoExpander, ioButtonBoardBusConnection);

    // End of IOExpanderList
    appendStringLN(getDebugOutputStreamLogger(), "OK");
}

MultiplexerList* mainLightHouse2020MultiplexerListInitDrivers(I2cBus* i2cBus) {
    appendString(getDebugOutputStreamLogger(), "Multiplexer List ...");
    initMultiplexerList(&multiplexerList, (Multiplexer(*)[]) &multiplexerArray, MAIN_PHARE_2020_MULTIPLEXER_LIST_LENGTH);
    
    // -> Multiplexer 0 Board
    Multiplexer* multiplexerExpander0 = getMultiplexerByIndex(&multiplexerList, 0);
    I2cBusConnection* multiplexerBoardBusConnection0 = addI2cBusConnection(i2cBus, TCA9548A_ADDRESS_0, true);
    initMultiplexerTca9548A(multiplexerExpander0, multiplexerBoardBusConnection0, /* Cache Masks */ true);
    
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    
    return &multiplexerList;
}

TofSensorList* mainLightHouse2020TofInitDrivers(I2cBus* i2cBus) {    
    mainLightHouse2020MultiplexerListInitDrivers(i2cBus);
    
    mainBoardLightHouse2020IOExpanderListInitDrivers(i2cBus);
    
    if (MAIN_PHARE_2020_TOF_SENSOR_LIST_COUNT > 0) {
        tofSensorArray[0].name = "TOF LIGHT HOUSE 0";
        tofSensorArray[0].enabled = true;
        tofSensorArray[0].orientationRadian = 0.0f;
        tofSensorArray[0].distanceFromRobotCenter = 0.0f;
        tofSensorArray[0].angleFromRobotCenterRadian = 0.0f;

        tofSensorArray[0].detectionThreshold = 1;
                
        tofSensorArray[0].i2cBusIndex = 1;
        tofSensorArray[0].changeAddress = true;
        tofSensorArray[0].targetAddress = VL530X_ADDRESS_0;
        tofSensorArray[0].multiplexer =  getMultiplexerByIndex(&multiplexerList, 0);
        tofSensorArray[0].multiplexerChannel = MULTIPLEXER_CHANNEL_0;
        
        tofSensorArray[0].hardwareRestartable = false;
        tofSensorArray[0].hardwareRestartIOExpander = NULL;
        tofSensorArray[0].hardwareRestartIOExpanderIoIndex = 0;

    }
    if (MAIN_PHARE_2020_TOF_SENSOR_LIST_COUNT > 1) {   
        tofSensorArray[1].name = "TOF LIGHT HOUSE 1";
        tofSensorArray[1].enabled = true; 
        tofSensorArray[1].orientationRadian = 0.0f;
        tofSensorArray[1].distanceFromRobotCenter = 0.0f;
        tofSensorArray[1].angleFromRobotCenterRadian = 0.0f;

        tofSensorArray[1].detectionThreshold = 1;

        tofSensorArray[1].i2cBusIndex = 1;
        tofSensorArray[1].changeAddress = true;
        tofSensorArray[1].targetAddress = VL530X_ADDRESS_1;
        tofSensorArray[1].multiplexer = getMultiplexerByIndex(&multiplexerList, 0);
        tofSensorArray[1].multiplexerChannel = MULTIPLEXER_CHANNEL_1;
 
        tofSensorArray[1].hardwareRestartable = false;
        tofSensorArray[1].hardwareRestartIOExpander = NULL;
        tofSensorArray[1].hardwareRestartIOExpanderIoIndex = 0;
    }

    appendStringLN(getDebugOutputStreamLogger(), "TOF ...");
    initTofSensorListVL53L0X(&tofSensorList,
                             (TofSensor(*)[]) &tofSensorArray,
                             (TofSensorVL53L0X(*)[]) &tofSensorVL53L0XArray,
                              // Size
                              MAIN_PHARE_2020_TOF_SENSOR_LIST_COUNT,
                              // debug
                              true
            );
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    
    return &tofSensorList;
}
