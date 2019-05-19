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

#include "../../../common/log/logLevel.h"
#include "../../../common/log/logger.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/ioExpander/ioExpander.h"

#include "../../../drivers/i2c/multiplexer/tca9548A.h"

#include "../../../device/deviceConstants.h"

/**
 * Initializes the IO Expander (if Any)
 * @private
 * @param tofSensorList
 * @param ioExpander
 * @param size
 */
void initIOExpanderForTofSensorList(IOExpander* ioExpander, unsigned int size) {
    if (ioExpander == NULL) {
        appendStringLN(getWarningOutputStreamLogger(), "initTofSensorListVL53L0X : IO Expander IS NULL ");
        return;
    }

    // Clear to shut all VL53L0X (max 6)
    unsigned int initialValue = ioExpander->ioExpanderReadValue(ioExpander);
    
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    // Keep the most significant bits (used for something else)
    // Ex : if (size = 6), 256 - 2^6 = 0b11000000
    if (ioExpander != NULL) {
        appendString(debugOutputStream, "  IO EXPANDER WRITE VALUE : mask=");

        // Mask 
        // unsigned ioExpanderMask = 256 - (1 << size);
        // We put to 0 the value to reset all tofs
        unsigned ioExpanderMask = 0;
        appendHex2(debugOutputStream, ioExpanderMask);

        // Written Value
        bool ioExpanderWrittenValue = initialValue & ioExpanderMask;
        appendStringAndDec(debugOutputStream, "  ioExpander Written Value=", ioExpanderWrittenValue);
        appendString(debugOutputStream, "...");
        ioExpander->ioExpanderWriteValue(ioExpander, ioExpanderWrittenValue);
        delaymSec(1);
        appendStringLN(debugOutputStream, "OK");
    }
}

void initTofSensorListVL53L0X(TofSensorList* tofSensorList, 
                              TofSensor(*tofSensorArray)[],
                              TofSensorVL53L0X(*tofSensorVL53L0XArray)[],
                              unsigned int size,
                              bool debug,
                              bool enableAllSensors,
                              bool changeAddressAllSensors) {
    initTofSensorList(tofSensorList, tofSensorArray, size, debug, enableAllSensors, changeAddressAllSensors, &printTofSensorTableVL53L0X);

    unsigned int tofIndex;
    for (tofIndex = 0; tofIndex < size; tofIndex++) {
        // Get the abstract tof Sensor structure at the specified index
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        
        if (!tofSensor->enabled) {
            appendStringAndDecLN(getWarningOutputStreamLogger(), "TOF SENSOR DISABLED : ", tofIndex);
            append(getAlwaysOutputStreamLogger(), '_');
            continue;
        }
        I2cBusConnection* multiplexerBusConnection = getI2cBusConnectionBySlaveAddress(tofSensor->multiplexerAddress);
        
        appendStringAndDecLN(getDebugOutputStreamLogger(), "  TOF SENSOR->START:", tofIndex);

        // Get the specific structure in the provide array
        TofSensorVL53L0X* tofSensorVL53L0X = (TofSensorVL53L0X*) tofSensorVL53L0XArray;

        // Shift to the right pointer address
        tofSensorVL53L0X += tofIndex;

        if (tofSensor->useMultiplexer) {
            unsigned char channel = tofSensor->multiplexerChannel;
            unsigned char multiplexerAddress = tofSensor->multiplexerAddress;
            appendStringAndDec(getDebugOutputStreamLogger(), "    MULTIPLEXER:addr=", multiplexerAddress);        
            appendStringAndDecLN(getDebugOutputStreamLogger(), ", channel=", channel);        
            tca9548A_setChannel(multiplexerBusConnection, channel);
            timerDelayMilliSeconds(10);
        }
        appendString(getDebugOutputStreamLogger(), "    INIT VL53");        
        // Initialize the VL53L0X, but with the default address
        bool successInit = initTofSensorVL53L0X(tofSensor, tofSensorVL53L0X, multiplexerBusConnection, "", 0, 0.0f);
        if (!successInit) {
            append(getAlwaysOutputStreamLogger(), 'X');
            continue;
        }
        
        appendStringLN(getDebugOutputStreamLogger(), "OK");
        unsigned char tofBusAddress = VL530X_ADDRESS_0;
        if (tofSensor->changeAddress) {
            // Change the address to avoid tof I2C Address collision
            tofBusAddress = VL530X_ADDRESS_0 + ((tofIndex + 1) << 1);
        }
        appendStringAndDec(getDebugOutputStreamLogger(), "    CHANGE ADDRESS FROM ", VL530X_ADDRESS_0);
        appendStringAndDec(getDebugOutputStreamLogger(), " TO ", tofBusAddress);
        I2cBusConnection* tofBusConnection = addI2cBusConnection(multiplexerBusConnection->i2cBus, tofBusAddress, true);
        bool succeedToChangeAddress = tofSetAddress(tofSensorVL53L0X, tofBusConnection);
        if (succeedToChangeAddress) {
            append(getAlwaysOutputStreamLogger(), '[');
            appendStringLN(getDebugOutputStreamLogger(), "...OK");
        }
        else {
            append(getAlwaysOutputStreamLogger(), 'X');
            appendStringLN(getDebugOutputStreamLogger(), "...KO");
        }
        
        appendStringAndDecLN(getDebugOutputStreamLogger(), "  TOF SENSOR->END:", tofIndex);
        
    }
    appendCRLF(getAlwaysOutputStreamLogger());
}