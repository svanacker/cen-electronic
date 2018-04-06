#ifndef MD22_H
#define MD22_H

#include "../../common/i2c/i2cBusConnectionList.h"

//md22 register locations
#define MD22_MODE_REGISTER                0
#define MD22_SPEED_LEFT_REGISTER          1
#define MD22_SPEED_RIGHT_REGISTER         2
#define MD22_SPEED_REGISTER               MD22_SPEED_LEFT_REGISTER
#define MD22_ACCELERATION_REGISTER        3
#define MD22_SOFTWARE_VERSION_REGISTER    7

// md22 values
#define MD22_MODE_0                       0
#define MD22_MODE_1                       1
#define MD22_MODE_ACCELERATION_MAX        0


#define MD22_MODE_0_FULL_REVERSE          0
#define MD22_MODE_0_STOP                  128
#define MD22_MODE_0_FULL_FORWARD          255


/**
 * 
 * @param i2cBusConnection
 * @return 
 */
bool initMD22(I2cBusConnection* i2cBusConnection);

/**
 * Returns the software revision of MD22.
 * @param i2cBusConnection
 * @return 
 */
unsigned char getMD22Version(I2cBusConnection* i2cBusConnection);

/**
* Stops the motors
*/
void stopMD22Motors(I2cBusConnection* i2cBusConnection);

/**
* Write speeds to left and right motors
* @param leftSpeed the left motor speed (value between MD22_MODE_0_FULL_REVERSE and MD22_MODE_0_FULL_FORWARD)
* @param rightSpeed the right motor speed (value between MD22_MODE_0_FULL_REVERSE and MD22_MODE_0_FULL_FORWARD)
*/
void setMD22MotorSpeeds(I2cBusConnection* i2cBusConnection, unsigned char leftSpeed, unsigned char rightSpeed);

#endif
