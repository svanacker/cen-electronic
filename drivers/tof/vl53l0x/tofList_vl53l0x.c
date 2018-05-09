#include "tofList_vl53l0x.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "tof_vl53l0x.h"
#include "tofDebug_vl53l0x.h"

#include "../tof.h"
#include "../tofList.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/i2c/i2cBusConnectionList.h"
#include "../../../common/i2c/i2cConstants.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../../drivers/ioExpander/ioExpander.h"

#include "../../../device/deviceConstants.h"

void initTofSensorListVL53L0X(TofSensorList* tofSensorList, 
                              TofSensor(*tofSensorArray)[],
                              TofSensorVL53L0X(*tofSensorVL53L0XArray)[],
                              unsigned int size,
                              I2cBus* i2cBus,
                              IOExpander* ioExpander,
                              bool debug,
                              bool enableAllSensors,
                              bool changeAddressAllSensors) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    if (ioExpander == NULL) {
        appendStringLN(getWarningOutputStreamLogger(), "initTofSensorListVL53L0X : IO Expander IS NULL ");
    }
    // Clear to shut all VL53L0X (max 6)
    unsigned int initialValue = ioExpander->ioExpanderReadValue(ioExpander);
    
    // Keep the most significant bits (used for something else)
    // Ex : if (size = 6), 256 - 2^6 = 0b11000000
    if (ioExpander != NULL) {
        appendString(debugOutputStream, "IO EXPANDER WRITE VALUE ...");
        unsigned ioExpanderMask = 256 - (1 << size);
        ioExpander->ioExpanderWriteValue(ioExpander, initialValue & ioExpanderMask);
        delaymSec(1);
        appendStringLN(debugOutputStream, "OK");
    }
    
    initTofSensorList(tofSensorList, tofSensorArray, size, debug, enableAllSensors, changeAddressAllSensors, &printTofSensorTableVL53L0X);
    unsigned int tofIndex;
    I2cBusConnection* initialTofBusConnection = addI2cBusConnection(i2cBus, VL530X_ADDRESS_0, true);
    for (tofIndex = 0; tofIndex < size; tofIndex++) {
        appendStringAndDecLN(debugOutputStream, "TOF SENSOR->START:", tofIndex);
        // Get the abstract tof Sensor structure at the specified index
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        // Get the specific structure in the provide array
        TofSensorVL53L0X* tofSensorVL53L0X = (TofSensorVL53L0X*) tofSensorVL53L0XArray;
        // Shift to the right one
        tofSensorVL53L0X += tofIndex;

        if (ioExpander != NULL && tofSensor->changeAddress) {
            // Activate only a specific TOF
            appendStringAndDec(debugOutputStream, "  IO Expander Write:", tofIndex);
            ioExpander->ioExpanderWriteSingleValue(ioExpander, tofIndex, true);
            // Delay to let the hardware part of the Sensor VL53L0X
            delaymSec(50);
            appendStringLN(debugOutputStream, " ... OK");
        }

        appendString(debugOutputStream, "  INIT VL53");        
        // Initialize the VL53L0X, but with the default address
        initTofSensorVL53L0X(tofSensor, tofSensorVL53L0X, initialTofBusConnection, 0, 0.0f);
        appendStringLN(debugOutputStream, "OK");
        appendStringAndDec(debugOutputStream, "  CHANGE ADDRESS ...", tofIndex);
        unsigned char tofBusAddress = VL530X_ADDRESS_0;
        if (tofSensor->changeAddress) {
            // Change the address to avoid tof I2C Address collision
            tofBusAddress = VL530X_ADDRESS_0 + ((tofIndex + 1) << 1);
        }
        I2cBusConnection* tofBusConnection = addI2cBusConnection(i2cBus, tofBusAddress, true);
        tofSetAddress(tofSensorVL53L0X, tofBusConnection);
        appendStringLN(debugOutputStream, "...OK");
        
        appendStringAndDecLN(debugOutputStream, "TOF SENSOR->END:", tofIndex);
    }
}