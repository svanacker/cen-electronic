#include "tofNetwork_vl53l0x.h"
#include "tof_vl53l0x.h"

#include "../tof.h"

#include "vl53l0x_api.h"
#include "vl53l0x_def.h"
#include "vl53l0x_platform.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/delay/cenDelay.h"

#include "../../../common/error/error.h"

#include "../../../common/i2c/i2cConstants.h"
#include "../../../common/i2c/i2cBusList.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../../drivers/i2c/multiplexer/multiplexerTca9548A.h"

I2cBusConnection* getTofSensorVL53L0XI2cBusConnection(TofSensor* tofSensor) {
    TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
    if (tofSensorVL53L0X == NULL) {
        writeError(TOF_SENSOR_OBJECT_NULL);
        return NULL;
    }
    return tofSensorVL53L0X->i2cBusConnection;
}

bool tofSetAddress(TofSensorVL53L0X* tofSensorVL53L0X, I2cBusConnection* i2cBusConnection, unsigned int newAddress) {
    tofSensorVL53L0X->status = VL53L0X_ERROR_NONE;
    VL53L0X_Dev_t* tofDevice = &(tofSensorVL53L0X->device);

    if (newAddress != VL530X_ADDRESS_BASE_ADDRESS) {
        tofSensorVL53L0X->status = VL53L0X_SetDeviceAddress(tofDevice, newAddress);
        timerDelayMilliSeconds(30);
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofDevice->I2cDevAddr = newAddress;
        i2cBusConnection->i2cAddress = newAddress;
        return true;
    }
    return false;
}

bool tofSensorChangeAddressIfNeeded(TofSensor* tofSensor) {
    TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
    I2cBusConnection* tofBusConnection = getTofSensorVL53L0XI2cBusConnection(tofSensor);
    // If we must change the address and this is not yet done
    if (tofSensor->changeAddress && tofBusConnection->i2cAddress != tofSensor->targetAddress) {
        appendStringAndDec(getDebugOutputStreamLogger(), "    CHANGE ADDRESS FROM ", tofBusConnection->i2cAddress);
        appendStringAndDec(getDebugOutputStreamLogger(), " TO ", tofSensor->targetAddress);
        return tofSetAddress(tofSensorVL53L0X, tofBusConnection, tofSensor->targetAddress);
    }
    return true;
}

/**
 * @private
 * @param tofSensor
 * @param multiplexerList
 * @param tofI2cSlaveAddress
 * @param debug
 * @return 
 */
I2cBusConnection* tofSensorSelectRightI2cBusConnection(TofSensor* tofSensor,
        unsigned char tofI2cSlaveAddress,
        bool debug) {
    if (tofSensor->multiplexer != NULL) {
        Multiplexer* multiplexer = tofSensor->multiplexer;
        unsigned char channel = tofSensor->multiplexerChannel;
        if (debug) {
            appendStringAndDecLN(getDebugOutputStreamLogger(), ", channel=", channel);
        }
        multiplexerEnableOnly(multiplexer, channel);
        timerDelayMilliSeconds(10);
        I2cBusConnection* multiplexerBusConnection = getMultiplexerI2cBusConnection(multiplexer);

        return getOrCreateI2cBusConnection(multiplexerBusConnection->i2cBus, tofI2cSlaveAddress, true);
    }
    // If we do not use the multiplexer, we get the bus
    I2cBus* i2cBus = getI2cBusByIndex(tofSensor->i2cBusIndex);
    // Then we retrieve or create a bus connection with the specified address
    return getOrCreateI2cBusConnection(i2cBus, tofI2cSlaveAddress, true);
}
