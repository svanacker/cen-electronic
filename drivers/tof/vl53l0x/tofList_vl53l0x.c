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

#include "../../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../../drivers/i2c/multiplexer/tca9548A.h"

#include "../../../device/deviceConstants.h"
#include "i2c/multiplexer/multiplexerTca9548A.h"

void initTofSensorListVL53L0X(TofSensorList* tofSensorList, 
                              TofSensor(*tofSensorArray)[],
                              TofSensorVL53L0X(*tofSensorVL53L0XArray)[],
                              unsigned int size,
                              MultiplexerList* multiplexerList,        
                              bool debug,
                              bool enableAllSensors,
                              bool changeAddressAllSensors) {
    initTofSensorList(tofSensorList,
                      tofSensorArray,
                      size,
                      multiplexerList,
                      debug, 
                      enableAllSensors,
                      changeAddressAllSensors, 
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
            append(getAlwaysOutputStreamLogger(), '_');
            continue;
        }
        Multiplexer* multiplexer = getMultiplexerByIndex(multiplexerList, tofSensor->multiplexerIndex);
        
        appendStringAndDecLN(getDebugOutputStreamLogger(), "  TOF SENSOR->START:", tofIndex);

        // Get the specific structure in the provide array
        TofSensorVL53L0X* tofSensorVL53L0X = (TofSensorVL53L0X*) tofSensorVL53L0XArray;

        // Shift to the right pointer address
        tofSensorVL53L0X += tofIndex;

        if (tofSensor->useMultiplexer) {
            unsigned char channel = tofSensor->multiplexerChannel;
            unsigned int multiplexerIndex = tofSensor->multiplexerIndex;
            appendStringAndDecLN(getDebugOutputStreamLogger(), "    MULTIPLEXER:index=", multiplexerIndex);
            appendStringAndDecLN(getDebugOutputStreamLogger(), ", channel=", channel);
            multiplexer->multiplexerWriteChannelsMask(multiplexer, channel);
            timerDelayMilliSeconds(30);
        }
        appendString(getDebugOutputStreamLogger(), "    INIT VL53");        
        // Initialize the VL53L0X, but with the default address
        unsigned char tofBusAddress = VL530X_ADDRESS_0;
        unsigned char newTofBusAddress = VL530X_ADDRESS_0 + ((tofIndex + 1) << 1);

        I2cBusConnection* multiplexerBusConnection = getMultiplexerI2cBusConnection(multiplexer);
        I2cBusConnection* tofBusConnection = addI2cBusConnection(multiplexerBusConnection->i2cBus, tofBusAddress, true);
        bool successInit = initTofSensorVL53L0X(tofSensor, tofSensorVL53L0X, tofBusConnection, multiplexer);
        if (!successInit) {
            // Maybe the sensor is always connected (by the Uart power) and has not reboot
            // We try to reach it at the new address
            tofBusConnection->i2cAddress = newTofBusAddress;
            successInit = initTofSensorVL53L0X(tofSensor, tofSensorVL53L0X, tofBusConnection, multiplexer);
            
            // If KO
            if (!successInit) {
                append(getAlwaysOutputStreamLogger(), 'X');
                tofSensor->enabled = false;
                continue;
            }
            else {
                append(getAlwaysOutputStreamLogger(), 'x');
                appendStringLN(getDebugOutputStreamLogger(), "...OK");
            }
        }
        // To let the hardware device initialize properly
        timerDelayMilliSeconds(30);
        
        appendStringLN(getDebugOutputStreamLogger(), "OK");
        // If we must change the address and this is not yet done
        if (tofSensor->changeAddress && tofBusConnection->i2cAddress != newTofBusAddress) {
            appendStringAndDec(getDebugOutputStreamLogger(), "    CHANGE ADDRESS FROM ", VL530X_ADDRESS_0);
            appendStringAndDec(getDebugOutputStreamLogger(), " TO ", newTofBusAddress);
            bool succeedToChangeAddress = tofSetAddress(tofSensorVL53L0X, tofBusConnection, newTofBusAddress);
            if (succeedToChangeAddress) {
                append(getAlwaysOutputStreamLogger(), '[');
                appendStringLN(getDebugOutputStreamLogger(), "...OK");
            }
            else {
                append(getAlwaysOutputStreamLogger(), 'X');
                tofSensor->enabled = false;
                appendStringLN(getDebugOutputStreamLogger(), "...KO");
            }
        }
        else {
            append(getAlwaysOutputStreamLogger(), '[');
            appendStringLN(getDebugOutputStreamLogger(), "...OK");
        }
        
        appendStringAndDecLN(getDebugOutputStreamLogger(), "  TOF SENSOR->END:", tofIndex);
        
    }
    appendCRLF(getAlwaysOutputStreamLogger());
}