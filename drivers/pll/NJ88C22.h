#ifndef NJ88C22_H
#define NJ88C22_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/outputStream.h"

#include "../../common/pll/pll.h"

#define FOSC_OL1_PLL 12800  //6400Khz
#define FCOMP_OL1_PLL 10   //10KHz
#define DIV_P 64           //diviseur par 64



#define NJ88C22_WRITE_ADDRESS       PCF8574_ADDRESS_7
#define NJ88C22_READ_ADDRESS        NJ88C22_WRITE_ADDRESS + 1

/** Setup the NJ88C22
 * @param pll a pointer on the pll structure.
*/
void setupNJ88C22 (Pll* pll);


/**
 * Initializes a pll object with a NJ88C22 hardware component.
 * @param pll a pointer on the mpu structure.
 */
void initPllNJ88C22(Pll* pll, I2cBusConnection* i2cBusConnection);

#endif