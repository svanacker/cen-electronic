#ifndef LED_UTILS_H
#define LED_UTILS_H

#define led1 PORTCbits.RC14
#define led2 PORTDbits.RD11

#define led1_dir TRISCbits.TRISC14
#define led2_dir TRISDbits.TRISD11

/**
* Set the state of the led
* @param index the index of the led
* @param state the state of the led
*/
void setLedValue (char index,char state);

/**
*  Test the led of the Board
*/
void testLedMainBoard (void);

#endif

