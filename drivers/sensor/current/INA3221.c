#include "INA3221.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cConstants.h"
#include "../../../common/i2c/master/i2cMaster.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/math/bcdUtils.h"

/**
 * Get the internal I2cBusConnection.
 * @param current the current structure (to simulate POO Programming).
 * @private
 */
I2cBusConnection* _INA3221_getI2cBusConnection(Current* current) {
    I2cBusConnection* result = (I2cBusConnection*) current->object;
    
    return result;
}

int _INA3221_readSensorValue(Current* current) {
    I2cBusConnection* i2cBusConnection = _INA3221_getI2cBusConnection(current);
    
    int result = 0;
    unsigned char INA3221Msb = 0;
    unsigned char INA3221Lsb = 0;

    //I2C START 
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    //I2C ADDRESS SELECT Write
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2cBusConnection(i2cBusConnection);
    //I2C REGISTER SELECT
    portableMasterWriteI2C(i2cBusConnection, INA3221_CHANNEL1_SHUNT_VOLTAGE);
    WaitI2cBusConnection(i2cBusConnection);
    
    // Restart in read mode
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    
    //I2C ADDRESS SELECT Read
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2cBusConnection(i2cBusConnection);
    
    //I2C DATA READ
    INA3221Msb = portableMasterReadI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    //I2C DATA READ
    INA3221Lsb = portableMasterReadI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    
    //I2C STOP
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    if (INA3221Msb & 0x80) {
        //courant negatif
        result = 0x1234; 
    }
    else { 
        //courant positif

    result = ((((INA3221Msb<<8) + INA3221Lsb)>>3) * INA3221_DELTA ) / INA3221_SHUNT;    
    }
     
    //result en mA
    return result;
}

void _INA3221_writeAlertLimit(Current* current, int currentSensorValue) {
    I2cBusConnection* i2cBusConnection = _INA3221_getI2cBusConnection(current);

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
}

void initCurrentINA3221(Current* current, I2cBusConnection* i2cBusConnection) {
    initCurrent(current, _INA3221_readSensorValue, _INA3221_writeAlertLimit, i2cBusConnection);
}
