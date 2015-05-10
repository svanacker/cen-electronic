#include "../../common/commons.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"


#include "md22.h"

#include "../../common/delay/cenDelay.h"

static I2cBusConnection* md22I2cBusConnection;

//addresses of modules on I2C bus
#define MD22_BASE            0xB0
#define MD22_ADDR_W            MD22_BASE + 0
#define MD22_ADDR_R            MD22_BASE + 1
//md22 register locations
#define MD22_MODE            0
#define MD22_SPEED_LEFT        1
#define MD22_SPEED_RIGHT    2
#define MD22_SPEED            MD22_SPEED_LEFT
#define MD22_ACCEL            3
#define MD22_SWVER            7

/**
 * Reads a register from the MD22.
 * @param addr I2C address of MD22
 * @param reg register from which to read
 * @return the value read from the register
 */
unsigned char readMD22(I2cBusConnection* i2cBusConnection, char addr, char reg) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address
    portableMasterWriteI2C(i2cBusConnection, MD22_ADDR_W);
    WaitI2C(i2cBus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address again with read bit

    portableMasterWriteI2C(i2cBusConnection, MD22_ADDR_R);
    WaitI2C(i2cBus);
    // read the data
    unsigned char data = portableMasterReadI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    return data;
}

/**
 * Writes a command to the MD22
 * @param addr I2C address of MD22
 * @param reg register in which to write
 * @param cmd command which is sent to the register
 */
void writeMD22Command(I2cBusConnection* i2cBusConnection, char addr, char reg, char cmd) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);

    // Wait till Start sequence is completed
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, addr);
    portableMasterWriteI2C(i2cBusConnection, reg);
    // command
    portableMasterWriteI2C(i2cBusConnection, cmd);

    portableMasterStopI2C(i2cBusConnection);
}

unsigned int getMD22Version(I2cBusConnection* i2cBusConnection) {
    return readMD22(i2cBusConnection, MD22_ADDR_R, MD22_SWVER);
}

void setMD22MotorSpeeds(I2cBusConnection* i2cBusConnection, signed char leftSpeed, signed char rightSpeed) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);

    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, MD22_ADDR_W);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MD22_SPEED);
    WaitI2C(i2cBus);
    // left motor speed
    portableMasterWriteI2C(i2cBusConnection, leftSpeed);
    WaitI2C(i2cBus);
    // the next value is written to the right motor speed register
    portableMasterWriteI2C(i2cBusConnection, rightSpeed);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
}

void stopMD22Motors() {
    setMD22MotorSpeeds(md22I2cBusConnection, 0, 0);
}

// DEVICE INTERFACE

bool initMD22() {
    getMD22Version(md22I2cBusConnection);
    delaymSec(10);

    // Sets data mode 1 (speeds between -128 and 127)
    writeMD22Command(md22I2cBusConnection, MD22_ADDR_W, MD22_MODE, 1);
    // Be careful, mode is not always taken in consideration, so we repeat it
    // and we use timer to be ensure that's is ok
    delaymSec(10);
    writeMD22Command(md22I2cBusConnection, MD22_ADDR_W, MD22_MODE, 1);
    delaymSec(10);
    // Initialize the device, first instruction is ignored
    // Sets acceleration to max
    writeMD22Command(md22I2cBusConnection, MD22_ADDR_W, MD22_ACCEL, 0);
    delaymSec(10);
    setMD22MotorSpeeds(md22I2cBusConnection, 0, 0);
    delaymSec(10);

    return true;
}

void stopMD22() {
    stopMD22Motors();
}

unsigned int isMD22DeviceOk(void) {
    return getMD22Version(md22I2cBusConnection);
}

const char* getMD22DeviceName(void) {
    return "MD22";
}

static DriverDescriptor descriptor = {
//    .driverEnabled = true,
    .driverInit = &initMD22,
    .driverShutDown = &stopMD22,
    // .driverIsOk = &isMD22DeviceOk,
    // .driverGetSoftwareRevision = &getMD22Version,
    .driverGetName = &getMD22DeviceName
};

DriverDescriptor* getMD22DriverDescriptor(I2cBusConnection* i2cBusConnection) {
    md22I2cBusConnection = i2cBusConnection;
    return &descriptor;
}
