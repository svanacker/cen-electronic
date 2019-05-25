#include "tofList_vl53l0x.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "tof_vl53l0x.h"
#include "tofDebug_vl53l0x.h"

#include "../tof.h"
#include "../tofList.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/i2c/i2cBusList.h"
#include "../../../common/i2c/i2cBusConnectionList.h"
#include "../../../common/i2c/i2cConstants.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logLevel.h"
#include "../../../common/log/logger.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/ioExpander/ioExpander.h"

#include "../../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../../drivers/i2c/multiplexer/tca9548A.h"

#include "../../../device/deviceConstants.h"
#include "i2c/multiplexer/multiplexerTca9548A.h"
#include "tof/tofDebug.h"

void initTofSensorListVL53L0X(TofSensorList* tofSensorList,
        TofSensor(*tofSensorArray)[],
        TofSensorVL53L0X(*tofSensorVL53L0XArray)[],
        unsigned int size,
        bool debug) {
    // Init the list and the call backs
    initTofSensorList(tofSensorList,
            tofSensorArray,
            size,
            debug,
            &printTofSensorConfigTableVL53L0X,
            &printTofSensorNetworkTableVL53L0X,
            &printTofSensorDetectionTableVL53L0X
            );
    unsigned int tofIndex;
    for (tofIndex = 0; tofIndex < size; tofIndex++) {
        // Get the abstract tof Sensor structure at the specified index
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        if (!tofSensor->enabled) {
            appendStringAndDecLN(getWarningOutputStreamLogger(), "TOF SENSOR DISABLED : ", tofIndex);
            tofSensor->startResult = TOF_SENSOR_START_RESULT_DISABLED;
        }
        else {
            appendStringAndDecLN(getDebugOutputStreamLogger(), "  TOF SENSOR->START:", tofIndex);

            // Get the specific structure in the provide array
            TofSensorVL53L0X* tofSensorVL53L0X = (TofSensorVL53L0X*) tofSensorVL53L0XArray;

            // Shift to the right pointer address
            tofSensorVL53L0X += tofIndex;
            
            // Initialization of the specific Hardware Structure attached to the tofSensor
            initTofSensorVL53L0X(tofSensor, tofSensorVL53L0X);

            // Start for the first time the Tof Sensor
            tofStart(tofSensor);

            // Debug
            appendStringAndDecLN(getDebugOutputStreamLogger(), "  TOF SENSOR->END:", tofIndex);
        }
        // In all cases, show the result as a single char on initialisation lcd panel
        appendTofSensorStartResultAsShortString(getAlwaysOutputStreamLogger(), tofSensor->startResult);
    }
    appendCRLF(getAlwaysOutputStreamLogger());
}