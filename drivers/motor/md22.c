#include "../../common/commons.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"


#include "md22.h"

#include "../../common/delay/delay30F.h"

//addresses of modules on I2C bus
#define MD22_BASE			0xB0
#define MD22_ADDR_W			MD22_BASE + 0
#define MD22_ADDR_R			MD22_BASE + 1
//md22 register locations
#define MD22_MODE			0
#define MD22_SPEED_LEFT		1
#define MD22_SPEED_RIGHT	2
#define MD22_SPEED			MD22_SPEED_LEFT
#define MD22_ACCEL			3
#define MD22_SWVER			7

/**
 * Reads a register from the MD22.
 * @param addr I2C address of MD22
 * @param reg register from which to read
 * @return the value read from the register
 */
unsigned char readMD22(char addr, char reg) {
    WaitI2C();
    portableStartI2C();
	portableMasterWaitSendI2C();
    // send the address
    portableMasterWriteI2C(MD22_ADDR_W);
    WaitI2C();
    // send the register
    portableMasterWriteI2C(reg);
    WaitI2C();
    portableStopI2C();
    WaitI2C();
    portableStartI2C();
	portableMasterWaitSendI2C();
    // send the address again with read bit

    portableMasterWriteI2C(MD22_ADDR_R);
    WaitI2C();
    // read the data
    unsigned char data = portableMasterReadI2C();
    portableStopI2C();
    return data;
}

/**
 * Writes a command to the MD22
 * @param addr I2C address of MD22
 * @param reg register in which to write
 * @param cmd command which is sent to the register
 */
void writeMD22Command(char addr, char reg, char cmd) {
    portableStartI2C();

    // Wait till Start sequence is completed
    WaitI2C();

    portableMasterWriteI2C(addr);
    portableMasterWriteI2C(reg);
    // command
    portableMasterWriteI2C(cmd);

    portableStopI2C();
}

unsigned int getMD22Version(void) {
    return readMD22(MD22_ADDR_R, MD22_SWVER);
}

void setMD22MotorSpeeds(signed char leftSpeed, signed char rightSpeed) {
    portableStartI2C();

    WaitI2C();
	portableMasterWaitSendI2C();
    portableMasterWriteI2C(MD22_ADDR_W);
    WaitI2C();
    portableMasterWriteI2C(MD22_SPEED);
    WaitI2C();
    // left motor speed
    portableMasterWriteI2C(leftSpeed);
    WaitI2C();
    // the next value is written to the right motor speed register
    portableMasterWriteI2C(rightSpeed);
    WaitI2C();

    portableStopI2C();

}

void stopMD22Motors(void) {
    setMD22MotorSpeeds(0, 0);
}

// DEVICE INTERFACE

bool initMD22(void) {
    getMD22Version();
    delaymSec(10);

    // Sets data mode 1 (speeds between -128 and 127)
    writeMD22Command(MD22_ADDR_W, MD22_MODE, 1);
    // Be careful, mode is not always taken in consideration, so we repeat it
    // and we use timer to be ensure that's is ok
    delaymSec(10);
    writeMD22Command(MD22_ADDR_W, MD22_MODE, 1);
    delaymSec(10);
    // Initialize the device, first instruction is ignored
    // Sets acceleration to max
    writeMD22Command(MD22_ADDR_W, MD22_ACCEL, 0);
    delaymSec(10);
    setMD22MotorSpeeds(0, 0);
    delaymSec(10);

    return TRUE;
}

void stopMD22(void) {
    stopMD22Motors();
}

unsigned int isMD22DeviceOk(void) {
    return getMD22Version();
}

const char* getMD22DeviceName(void) {
    return "MD22";
}

static DriverDescriptor descriptor = {
//    .driverEnabled = TRUE,
    .driverInit = &initMD22,
    .driverShutDown = &stopMD22,
    // .driverIsOk = &isMD22DeviceOk,
    // .driverGetSoftwareRevision = &getMD22Version,
    .driverGetName = &getMD22DeviceName
};

DriverDescriptor* getMD22DriverDescriptor() {
    return &descriptor;
}
