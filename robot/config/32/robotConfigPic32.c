#include <p32xxxx.h>
#include <stdlib.h>

#include "robotConfigPic32.h"

#include "../robotConfig.h"

/**
 * Implementation of the read Function of configuration switch.
 * @see robotConfig.h
 * @private
 */

unsigned int _robotConfigReadInt (RobotConfig* robotConfig){
    unsigned int value = 0;

    value = ((PORTG & 0x0004) << 11) | // PORTG2
            ((PORTC & 0x2000) >> 1) | // PORTC13
            ((PORTB & 0x8000) >> 4)|// PORTB15
            ((PORTB & 0x3E00) >> 3) | // PORTB9 -> PORTB13
            ((PORTB & 0x00C0) >> 2) | // PORTB6 - PORTB7
            ((PORTD & 0x01E0) >> 5); // PORTD5 ->PORTD8

    return value;
}

void initRobotConfigPic32(RobotConfig* robotConfig, enum RobotType robotType) {
    // Init the portb input selected as I/O
    AD1PCFG = 0xBFC0;//0b1011111011000000;

    //Init the port selected as Input
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;
    TRISDbits.TRISD8 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB9 = 1;
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB12 = 1;
    TRISBbits.TRISB13 = 1;
    TRISBbits.TRISB15 = 1;
    TRISCbits.TRISC13 = 1;
    TRISGbits.TRISG2 = 1;

    initRobotConfig(robotConfig, robotType, _robotConfigReadInt, NULL);
}
