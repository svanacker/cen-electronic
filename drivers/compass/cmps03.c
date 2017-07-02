#define _SUPPRESS_PLIB_WARNING
#include <i2c.h>
#include <delay.h>

#include "cmps03.h"

#define CMPS03_ADDRESS_WRITE 0xC0
#define CMPS_ADDRESS_READ 0xC1
#define REGISTER_SOFTWARE_REVISION 0


char getRevCMPS03(void) {
  unsigned char version;
 
  IdleI2C();

  StartI2C();
/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);

  MasterWriteI2C(CMPS03_ADDRESS_WRITE);        //adddresse I2C de la carte
  IdleI2C();

  MasterWriteI2C(0);        //registre de version
  IdleI2C();
  
  StopI2C();
  IdleI2C();
  StartI2C();
/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN)

  MasterWriteI2C(CMPS_ADDRESS_READ);        //adddresse I2C de la carte
  IdleI2C();

  version = MasterReadI2C();        //registre de version
  IdleI2C();

  return (version);
}

char getByteCMPS03(void) {
  unsigned char version;
 
  IdleI2C();

  StartI2C();
/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);

  MasterWriteI2C(CMPS03_ADDRESS_WRITE);        //adddresse I2C de la carte
  IdleI2C();

  MasterWriteI2C(1);        //registre de version
  IdleI2C();
  
  StopI2C();
  IdleI2C();
  StartI2C();
/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN)

  MasterWriteI2C(CMPS_ADDRESS_READ);        //adddresse I2C de la carte
  IdleI2C();

  version = MasterReadI2C();        //registre de version
  IdleI2C();

  return (version);
}

unsigned int getDegCMPS03(void) {
  unsigned char high,low;
  unsigned int direction;
 
  IdleI2C();

  StartI2C();
/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);

  MasterWriteI2C(CMPS03_ADDRESS_WRITE);        //adddresse I2C de la carte
  IdleI2C();

  MasterWriteI2C(2);        //registre 
  IdleI2C();
  
  StopI2C();
  IdleI2C();
  StartI2C();
/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN)

  MasterWriteI2C(CMPS_ADDRESS_READ);        //adddresse I2C de la carte
  IdleI2C();

  high = MasterReadI2C();        //registre de version
  IdleI2C();






 StopI2C();
  IdleI2C();
  StartI2C();
/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN)

  MasterWriteI2C(CMPS_ADDRESS_READ);        //adddresse I2C de la carte
  IdleI2C();








  low = MasterReadI2C();        //registre de version
  IdleI2C();

  direction = 0;
  direction |= high & 0xFF;
  direction <<= 8;
  direction |= low & 0xFF;


  return (direction);
}
