#ifndef SHIFTUCN5895_H
#define SHIFTUCN5895_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/outputStream.h"

#include "../../common/silec/silec.h"

#define FOSC_OL1_PLL 12800  //6400Khz
#define FCOMP_OL1_PLL 10   //10KHz
#define DIV_P 64           //diviseur par 64

#define SHIFTUCN5895_WRITE_ADDRESS       PCF8574_ADDRESS_6
#define SHIFTUCN5895_READ_ADDRESS        SHIFTUCN5895_WRITE_ADDRESS + 1


/** Setup the SHIFTUCN5895
 * @param silec a pointer on the silec structure.
*/
void setupSHIFTUCN5895 (Silec* silec);

/**
 * Initializes a silec object with a UCN5895 hardware component.
 * @param silec a pointer on the mpu structure.
 */
void initSHIFTUCN5895(Silec* silec, I2cBusConnection* i2cBusConnection);

#endif