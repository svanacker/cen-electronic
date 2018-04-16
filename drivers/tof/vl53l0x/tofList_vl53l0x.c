#include "tofList_vl53l0x.h"

#include <stdbool.h>
#include <stdlib.h>

#include "tof_vl53l0x.h"
#include "tofDebug_vl53l0x.h"

#include "../tof.h"
#include "../tofList.h"

#include "../../common/delay/cenDelay.h"

#include "../../../common/i2c/i2cBusConnectionList.h"
#include "../../../common/i2c/i2cConstants.h"

#include "../../../drivers/ioExpander/ioExpander.h"

#include "../../../device/deviceConstants.h"

void initTofSensorListVL53L0X(TofSensorList* tofSensorList, 
                              TofSensor(*tofSensorArray)[],
                              TofSensorVL53L0X(*tofSensorVL53L0XArray)[],
                              unsigned int size,
                              I2cBus* i2cBus,
                              IOExpander* ioExpander) {
    // Clear to shut all VL53L0X (max 6)
    unsigned int initialValue = ioExpander->ioExpanderReadValue(ioExpander);
    
    // Keep the most significant bits (used for something else)
    ioExpander->ioExpanderWriteValue(ioExpander, initialValue & 0b11000000);
    delaymSec(1);
    
    initTofSensorList(tofSensorList, tofSensorArray, size, &printTofSensorTableVL53L0X);
    unsigned int tofIndex;
    I2cBusConnection* initialTofBusConnection = addI2cBusConnection(i2cBus, VL530X_ADDRESS_0, true);
    for (tofIndex = 0; tofIndex < size; tofIndex++) {
        
        // Get the abstract tof Sensor structure at the specified index
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        
        // Get the specific structure in the provide array
        TofSensorVL53L0X* tofSensorVL53L0X = (TofSensorVL53L0X*) tofSensorVL53L0XArray;
        // Shift to the right one
        tofSensorVL53L0X += tofIndex;

        // Activate only a specific TOF
        ioExpander->ioExpanderWriteSingleValue(ioExpander, tofIndex, true);
        delaymSec(30);
        
        // Initialize the VL53L0X, but with the default address
        initTofSensorVL53L0X(tofSensor, tofSensorVL53L0X, initialTofBusConnection, 0);

        // Change the address to avoid tof I2C Adress collision
        unsigned tofBusAddress = VL530X_ADDRESS_0 + ((tofIndex + 1) << 1);
        I2cBusConnection* tofBusConnection = addI2cBusConnection(i2cBus, tofBusAddress, true);
        tofSetAddress(tofSensorVL53L0X, tofBusConnection);
    }
}