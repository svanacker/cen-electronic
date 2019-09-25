#ifndef SRF08_H
#define SRF08_H

// Use Inch as distance unit in simple mode
#define INCH_RANGE_MODE 0x50

// Use Centimeters as distance unit in simple mode
#define CM_RANGE_MODE 0x51

// Use micro-seconds for distance unit in simple mode
#define MICRO_SECONDES_RANGE_MODE 0x52

// Use Inch as distance unit in artificial neural network (ANN)
#define ANN_INCH_RANGE_MODE 0x53

// Use Centimeters as distance unit in artificial neural network (ANN)
#define ANN_CM_RANGE_MODE 0x54

// Use micro-seconds for distance unit in artificial neural network (ANN)
#define ANN_MICRO_SECONDES_RANGE_MODE 0x55

/** Default address of the SRF08. */
#define SRF08_DEFAULT_ADDRESS 0xE0

/**
* Init the SRF08 with an address and a mode
*/
void initSRF08(unsigned char addr, unsigned char mode);

/**
* Get the software revision of the SRF08
*/
unsigned char getSRF08SoftwareRev(unsigned char addr);

/**
* Ask the SRF08 to know if it's ok or not.
*/
unsigned char isSRF08DeviceOk(unsigned char addr);

void changeAddress(unsigned char addr, unsigned char oldAddress, unsigned char newAddress);

void startRanging(unsigned char addr);

/**
* Read the distance and returns value depending on the mode which
* was given at the initialisation of the SRF08
*/
unsigned char readDistance(unsigned char addr);



#endif
