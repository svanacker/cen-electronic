#include "LM75A.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cConstants.h"
#include "../../../common/i2c/master/i2cMaster.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/math/bcdUtils.h"

/**
 * Get the internal I2cBusConnection.
 * @param temperature the temperature structure (to simulate POO Programming).
 * @private
 */
I2cBusConnection* _LM75A_getI2cBusConnection(Temperature* temperature) {
    I2cBusConnection* result = (I2cBusConnection*) temperature->object;
    
    return result;
}

int _LM75A_readSensorValue(Temperature* temperature) {
    I2cBusConnection* i2cBusConnection = _LM75A_getI2cBusConnection(temperature);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    int result = 0;
    unsigned char lm75aMsb = 0;
    // unsigned char lm75aLsb;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, LM75A_READ_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    //I2C read Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2C(i2cBus);
    lm75aMsb = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // lm75aLsb = 
    portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    result = lm75aMsb;
    return result;
}

void _LM75A_writeAlertLimit(Temperature* temperature, int temperatureSensorAlertValue) {
    I2cBusConnection* i2cBusConnection = _LM75A_getI2cBusConnection(temperature);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, LM75A_OVER_TEMPERATURE_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    unsigned char value = bcd2CharToDec(temperatureSensorAlertValue);
    portableMasterWriteI2C(i2cBusConnection, value);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, 0x00);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, LM75A_CONFIGURATION_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, OS_POLARITY_HIGH);

    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void initTemperatureLM75A(Temperature* temperature, I2cBusConnection* i2cBusConnection) {
    initTemperature(temperature, _LM75A_readSensorValue, _LM75A_writeAlertLimit, i2cBusConnection);
}
