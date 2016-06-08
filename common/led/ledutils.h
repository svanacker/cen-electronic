#ifndef LED_UTILS_H
#define LED_UTILS_H

#define ELECTRONICAL_MAIN_BOARD_REV_1_40

#ifdef ELECTRONICAL_MAIN_BOARD_REV_1_30
#define led1 PORTCbits.RC14
#define led2 PORTDbits.RD11

#define led1_dir TRISCbits.TRISC14
#define led2_dir TRISDbits.TRISD11
#endif
#ifdef ELECTRONICAL_MAIN_BOARD_REV_1_40
#define led2 LATBbits.LATB0
#define led1 LATBbits.LATB1

#define led2_dir TRISBbits.TRISB0
#define led1_dir TRISBbits.TRISB1

#endif

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

