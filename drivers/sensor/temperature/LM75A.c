#include "LM75A.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cConstants.h"
#include "../../../common/i2c/master/i2cMaster.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/math/bcdUtils.h"

char getTemperatureSensor(I2cBus* i2cBus){
    char temperature = 0;
    char lm75aMsb = 0;
    char lm75aLsb = 0;

    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, LM75A_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, LM75A_READ_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    //I2C read Address
    portableMasterWriteI2C(i2cBus, LM75A_ADDRESS | 0x01);
    WaitI2C(i2cBus);
    lm75aMsb = portableMasterReadI2C(i2cBus);
    WaitI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);

    lm75aLsb = portableMasterReadI2C(i2cBus);
    WaitI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);

    temperature = lm75aMsb;
    return temperature;
}

void setTemperatureAlertLimit(I2cBus* i2cBus, int TemperatureSensorAlert){

    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, LM75A_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, LM75A_OVER_TEMPERATURE_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    unsigned char value = bcd2CharToDec(TemperatureSensorAlert);
    portableMasterWriteI2C(i2cBus, value);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, 0x00);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);

    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, LM75A_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, LM75A_CONFIGURATION_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, OS_POLARITY_HIGH);

    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
}
