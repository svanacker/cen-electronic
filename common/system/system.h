#ifndef SYSTEM_H
#define SYSTEM_H

/**
* Defines the name of the PIC.
* @apicName the name of the PIC (Ex : MAIN BOARD 32 ...)
*/
void setPicName(char* apicName);

/**
* Returns the name of the PIC.
* @return the name of the PIC (Ex : MAIN BOARD 32 ...)
*/
char* getPicName(void);

#endif
