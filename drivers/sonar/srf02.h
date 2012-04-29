#ifndef SRF02_H
#define SRF02_H

#include "../../device/device.h"

/** Default address of the SRF02. */
//#define SRF02_DEFAULT_ADDRESS 0xE0
#define SRF02_DEFAULT_ADDRESS 0xE2

// Use Inch as distance unit in simple mode
#define INCH_RANGE_MODE 0x50

// Use Centimeters as distance unit in simple mode
#define CM_RANGE_MODE 0x51

// Use micro-seconds for distance unit in simple mode
#define MICRO_SECONDES_RANGE_MODE 0x52

// Command register for write  or Sofware version for read
#define REGISTER_0 0x00

/**
* Read a register from SRF02
* @param addr Adresse of the selected SRF02
* @param reg register to read
* @return distance in cm
*/
unsigned char readSRF02(char addr, char reg);

/**
* Get the software revision of the SRF02
* TODO : rendre possible la lecture de plusieurs sonar
*/
unsigned int getSRF02SoftwareRevision (unsigned char sonar);

/**
* Get the distance in centimeters
* Warning that the function ask 100 ms as a delay.
* If you doesn't want any delay, use startRanging(), and after get
* @return distance in cm
* TODO : rendre possible la lecture de plusieurs sonar
*/
unsigned int getSRF02Distance (void);

/**
* Start ranging.
*/
void startSRF02Ranging(void);

/**
* You need to call startSRF02 before !!
* End the ranging, and return the distance.
*/
unsigned int getSRF02DistanceEndRanging();

/**
* Write the command at the register of the selected SRF02.
* @param addr Adresse of the selected SRF02
* @param reg register to write
* @param cmd command to do
*/
void writeSRF02Command(char addr, char reg, char cmd);

/**
* Returns if the SRF02 device with the specified address
* is ok or not.
* @param addr the address of the SRF02
*/
unsigned char isSRF02DeviceWithAddressOk(char addr);

/**
* Returns a descriptor on the device.
*/
DeviceDescriptor getSRF02DeviceDescriptor();


#endif
