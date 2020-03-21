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

void _INA219_initSensor(Current* current) {
    I2cBusConnection* i2cBusConnection = _INA219_getI2cBusConnection(current);
    ina219_write16(i2cBusConnection, INA219_CONFIGURATION_REGISTER,
            INA219_CONFIGURATION_GAIN_RANGE_40_MV |
            INA219_ADC_MODE_9_BIT |
            INA219_CONFIGURATION_SHUNT_VOLTAGE_CONTINUOUS);
}

void ina219_write16(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned int data) {
    //I2C START 
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    //I2C ADDRESS SELECT Write
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2cBusConnection(i2cBusConnection);
    //I2C REGISTER SELECT
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2cBusConnection(i2cBusConnection);
    // I2C VALUE : MSB
    portableMasterWriteI2C(i2cBusConnection, (unsigned char) ((data & 0xFF00) >> 8));
    WaitI2cBusConnection(i2cBusConnection);
    // I2C VALUE : LSB
    portableMasterWriteI2C(i2cBusConnection, (unsigned char) (data & 0xFF));
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
}

unsigned int ina219_read16(I2cBusConnection* i2cBusConnection, unsigned char reg) {
    unsigned int result = 0;
    unsigned char msbValue = 0;
    unsigned char lsbValue = 0;

    //I2C START 
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    //I2C ADDRESS SELECT Write
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2cBusConnection(i2cBusConnection);
    //I2C REGISTER SELECT
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2cBusConnection(i2cBusConnection);

    // Restart in read mode
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    //I2C ADDRESS SELECT Read
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2cBusConnection(i2cBusConnection);

    //I2C DATA READ
    msbValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    //I2C DATA READ
    lsbValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    //I2C STOP
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    result = (msbValue << 8) | lsbValue;

    return result;
}

int _INA219_readSensorValue(Current* current) {
    //    I2cBusConnection* i2cBusConnection = _INA219_getI2cBusConnection(current);

    return 0;
}

void _INA219_writeAlertLimit(Current* current, int currentSensorValue) {
    /* TODO
    I2cBusConnection* i2cBusConnection = _INA219_getI2cBusConnection(current);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, INA3221_OVER_CURRENT_SENSOR_REGISTER);
    WaitI2cBusConnection(i2cBusConnection);
    unsigned char value = bcd2CharToDec(currentSensorValue);
    portableMasterWriteI2C(i2cBusConnection, value);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, 0x00);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, INA3221_CONFIGURATION_SENSOR_REGISTER);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, INA3221_OS_POLARITY_HIGH);

    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
     * */
}

void initCurrentINA219(Current* current, I2cBusConnection* i2cBusConnection) {
    initCurrent(current, _INA219_readSensorValue, _INA219_writeAlertLimit, i2cBusConnection);
}
