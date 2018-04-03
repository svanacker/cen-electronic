#include "md22.h"

#include "../../common/commons.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/delay/cenDelay.h"

//md22 register locations
#define MD22_MODE_REGISTER                0
#define MD22_SPEED_LEFT_REGISTER          1
#define MD22_SPEED_RIGHT_REGISTER         2
#define MD22_SPEED_REGISTER               MD22_SPEED_LEFT_REGISTER
#define MD22_ACCELERATION_REGISTER        3
#define MD22_SOFTWARE_VERSION_REGISTER    7

// md22 values
#define MD22_MODE_1                       1
#define MD22_MODE_ACCELERATION_MAX        0


/**
 * Reads a register from the MD22.
 * @param addr I2C address of MD22
 * @param reg register from which to read
 * @return the value read from the register
 */
unsigned char readMD22(I2cBusConnection* i2cBusConnection, unsigned char reg) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    
    // TODO : Find if we must stop or not (seems that it's not used in other device, and it's often a problem)
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address again with read bit

    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2C(i2cBus);
    // read the data
    unsigned char data = portableMasterReadI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    return data;
}

/**
 * Writes a command to the MD22
 * @param reg register in which to write
 * @param cmd command which is sent to the register
 */
void writeMD22Command(I2cBusConnection* i2cBusConnection, char reg, char cmd) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);

    // Wait till Start sequence is completed
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);
    // command
    portableMasterWriteI2C(i2cBusConnection, cmd);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
}

unsigned char getMD22Version(I2cBusConnection* i2cBusConnection) {
    return readMD22(i2cBusConnection, MD22_SOFTWARE_VERSION_REGISTER);
}

void setMD22MotorSpeeds(I2cBusConnection* i2cBusConnection, signed char leftSpeed, signed char rightSpeed) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);

    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MD22_SPEED_LEFT_REGISTER);
    WaitI2C(i2cBus);
    // left motor speed
    portableMasterWriteI2C(i2cBusConnection, leftSpeed);
    WaitI2C(i2cBus);
    // the next value is written to the right motor speed register
    portableMasterWriteI2C(i2cBusConnection, rightSpeed);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
}

void stopMD22Motors(I2cBusConnection* i2cBusConnection) {
    setMD22MotorSpeeds(i2cBusConnection, 0, 0);
}

bool initMD22(I2cBusConnection* i2cBusConnection) {
    unsigned char softwareRevision = getMD22Version(i2cBusConnection);
    // Sets data mode 1 (speeds between -128 and 127)
    writeMD22Command(i2cBusConnection, MD22_MODE_REGISTER, MD22_MODE_1);
    delaymSec(10);
    writeMD22Command(i2cBusConnection, MD22_MODE_REGISTER, MD22_MODE_1);
    delaymSec(10);
    // Sets acceleration to max
    writeMD22Command(i2cBusConnection, MD22_ACCELERATION_REGISTER, MD22_MODE_ACCELERATION_MAX);
    delaymSec(10);
    // Set Motor Speed to 0 for both motors
    setMD22MotorSpeeds(i2cBusConnection, 0, 0);
    delaymSec(10);

    return softwareRevision != 0xFF;
}

