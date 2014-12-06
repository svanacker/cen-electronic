#include <peripheral/legacy/i2c_legacy.h>

#include <p30Fxxxx.h>
#include <libpic30.h>
#include "robotConfig30F.h"
#include "../../robot/config/robotConfig.h"

/**
 * @private
 */
unsigned char readPCFByte(int pcfAddress, int pcfConfigAddress) {
    unsigned char read = readPCF8574(pcfAddress, pcfConfigAddress, 0xFF);

    // The high 4 bits of each byte is inversed => 1100 0001 is in reality : 0011 0001
    unsigned char result = read & 0x0F;
    if (read & 0x10) {
        result += 0x80;
    }
    if (read & 0x20) {
        result += 0x40;
    }
    if (read & 0x40) {
        result += 0x20;
    }
    if (read & 0x80) {
        result += 0x10;
    }
    return result;
}

signed int _robotConfigReadInt (RobotConfig* robotConfig){

    unsigned char lowByte = readPCFByte(PCF8574_BASE_ADDRESS, PCF8574_LOW_BYTE_CONFIG_ADDRESS);
    unsigned char highByte = readPCFByte(PCF8574_BASE_ADDRESS, PCF8574_HIGH_BYTE_CONFIG_ADDRESS);

    // The both highest bit is not available => be careful to the inversion made by readPCFByte
    signed int result = ((highByte & 0x3F) << 8) | lowByte;

    return result;
}

void initRobotConfig30F(RobotConfig* robotConfig) {
    initRobotConfig(robotConfig, _robotConfigReadInt);
}
