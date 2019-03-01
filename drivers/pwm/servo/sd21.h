/**
CONTROLE DE LA CARTE SD21 DE DEVANTECH 
11-01-2010 ebauche du fonctionnement de la carte
*/

#ifndef SD21_H
#define SD21_H

#include "../device.h"

#define SD21_ADDRESS_WRITE 0xC2
#define SD21_ADDRESS_READ 0xC3
#define REGISTER_SOFTWARE_REVISION 64
#define REGISTER_VOLTAGE 65

/** The value when we want full Speed for servo to reach the position. */
#define SERVO_FULL_SPEED 255

/**
* Returns the descriptor on the SD2.
*/
DeviceDescriptor getSD21DeviceDescriptor();

/**
* Initialization of SD21.
*/
void initSD21(void);

/**
* Get the Software Revision of the SD21 board.
* @return Software Revision of the SD21 board
*/
unsigned int getSD21SoftwareRevision (void);

/**
* Returns true if the SD21 is ok or not.
*/
unsigned int isSD21DeviceOk();

/*
* Get the supply voltage of the SD21 board
* @return the supply voltage of the SD21 board
*/
char getSD21BatteryLevel (void);

/*
* envoie une commande sur la carte SD21
* @param servo servo number (between 1 and 21)
* @param speed  Vitesse de déplacement du servo FF= Max   ((Target position-Start position)/Speed Reg)*20mS
* @param position the position of the servo (in microsecond)
*/
void commandSD21(char servo, char speed, int position);

#endif
