#include "mainExperience2019Tof.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../device/deviceList.h"

#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"


// TOF
#include "../../drivers/tof/vl53l0x/tof_vl53l0x.h"
#include "../../drivers/tof/vl53l0x/tofList_vl53l0x.h"

// TOF
static TofSensorList tofSensorList;
static TofSensor tofSensorArray[MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT];
static TofSensorVL53L0X tofSensorVL53L0XArray[MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT];

void mainExperience2019TofAddDevices(void) {
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(&tofSensorList));
}

TofSensorList* mainExperience2019TofInitDrivers(void) {
    if (MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT > 0) {
        tofSensorArray[0].name = "EXP 2019 LEFT";
        tofSensorArray[0].i2cBusIndex = 0;
        tofSensorArray[0].enabled = true;
        tofSensorArray[0].useMultiplexer = false;
        tofSensorArray[0].multiplexerIndex = 0;
        tofSensorArray[0].multiplexerChannel = 0;
    }
    if (MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT > 1) {   
        tofSensorArray[1].name = "EXP 2019 RIGHT";
        tofSensorArray[0].i2cBusIndex = 1;
        tofSensorArray[1].enabled = true; 
        tofSensorArray[1].useMultiplexer = false;
        tofSensorArray[1].multiplexerIndex = 0;
        tofSensorArray[1].multiplexerChannel = 0;
    }

    appendStringLN(getDebugOutputStreamLogger(), "TOF ...");
    initTofSensorListVL53L0X(&tofSensorList,
                             (TofSensor(*)[]) &tofSensorArray,
                             (TofSensorVL53L0X(*)[]) &tofSensorVL53L0XArray,
                              // Size
                              MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT,
                              // MultiplexerList,
                              NULL,
                              // debug
                              true,
                              // enabledAllSensors
                              false,
                              // changeAddressAllSensors
                              true
            );
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    
    return &tofSensorList;
}
