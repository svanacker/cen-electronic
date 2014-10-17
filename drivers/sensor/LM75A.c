#include <p32xxxx.h>
#include <peripheral/legacy/i2c_legacy.h>

#include "LM75A.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/io/outputStream.h"

char getTemperatureSensor(void){
    char temperature = 0;
    char lm75aMsb = 0;
    char lm75aLsb = 0;

    portableStartI2C();
    portableMasterWriteI2C(LM75A_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(LM75A_READ_SENSOR_REGISTER);
    WaitI2C();
    portableStartI2C();
    //I2C read Address
    portableMasterWriteI2C(LM75A_ADDRESS | 0x01);
    WaitI2C();
    lm75aMsb = portableMasterReadI2C();
    portableAckI2C();
    lm75aLsb = portableMasterReadI2C();
    portableAckI2C();
    portableStopI2C();

    temperature = lm75aMsb;
    return temperature;
}

void setTemperatureAlertLimit(int TemperatureSensorAlert){

    //2BCD to HEX
    int data;
    data = TemperatureSensorAlert>>4;
    data = data * 10;
    data = data +(TemperatureSensorAlert & 0b00001111);


    portableStartI2C();
    portableMasterWriteI2C(LM75A_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(LM75A_OVERTEMPERATURE_SENSOR_REGISTER);
    WaitI2C();
    portableMasterWriteI2C(data);
    WaitI2C();
    portableMasterWriteI2C(0x00);
    WaitI2C();
    portableStopI2C();


        portableStartI2C();
    portableMasterWriteI2C(LM75A_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(LM75A_CONFIGURATION_SENSOR_REGISTER);
    WaitI2C();
    portableMasterWriteI2C(4);

    WaitI2C();
    portableStopI2C();
}