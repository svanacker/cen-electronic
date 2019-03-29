#include "INA219.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cConstants.h"
#include "../../../common/i2c/master/i2cMaster.h"
#include "../../../common/io/outputStream.h"

/**
 * Get the internal I2cBusConnection.
 * @param current the current structure (to simulate POO Programming).
 * @private
 */
I2cBusConnection* _INA219_getI2cBusConnection(Current* current) {
    I2cBusConnection* result = (I2cBusConnection*) current->object;

    return result;
}

int _INA219_readSensorValue(Current* current) {
    return 0;
    /*TODO 
    I2cBusConnection* i2cBusConnection = _INA3221_getI2cBusConnection(current);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    int result = 0;
    char msbValue = 0;
    char lsbValue = 0;

    //I2C START 
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    //I2C ADDRESS SELECT Write
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    //I2C REGISTER SELECT
    portableMasterWriteI2C(i2cBusConnection, INA3221_CHANNEL1_SHUNT_VOLTAGE);
    WaitI2C(i2cBus);

    // Restart in read mode
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    //I2C ADDRESS SELECT Read
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2C(i2cBus);

    //I2C DATA READ
    msbValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    //I2C DATA READ
    lsbValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    //I2C STOP
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    if (msbValue & 0x80) {
        //courant negatif
        result = 0x1234;
    } else {
        //courant positif
        result = ((((msbValue << 8) + lsbValue) >> 3) * INA3221_DELTA) / INA3221_SHUNT;
    }

    //result en mA
    return result;
    */
}

void _INA219_writeAlertLimit(Current* current, int currentSensorValue) {
    /* TODO
    I2cBusConnection* i2cBusConnection = _INA219_getI2cBusConnection(current);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, INA3221_OVER_CURRENT_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    unsigned char value = bcd2CharToDec(currentSensorValue);
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
    portableMasterWriteI2C(i2cBusConnection, INA3221_CONFIGURATION_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, INA3221_OS_POLARITY_HIGH);

    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
     * */
}

void initCurrentINA219(Current* current, I2cBusConnection* i2cBusConnection) {
    initCurrent(current, _INA219_readSensorValue, _INA219_writeAlertLimit, i2cBusConnection);
}
