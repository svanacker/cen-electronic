#include <p30Fxxxx.h>

// ---------
// Input Bits 
// ---------

#define D0             PORTBbits.RB0
#define D1             PORTBbits.RB1
#define D2             PORTBbits.RB2
#define D3             PORTBbits.RB3
#define D4             PORTBbits.RB8
#define D5             PORTBbits.RB9
#define D6             PORTBbits.RB10
#define D7             PORTBbits.RB11

// PORT B0->B3 as input
// PORT B8->B11 as input
// PORT B4->B7 as output
// PORT B12->B15 as output
#define TRIS_DX     0b0000111100001111

// ---------
// SEL1 - SEL2
// ---------

// Select the byte index to read 8 bits from 32 bits register
// -> 0/1 => Master Byte (Byte 1)
// -> 1/1 => Byte 2
// -> 0/0 => Byte 3
// -> 1/0 => Low Byte (Byte 4)
#define SEL1         LATFbits.LATF0
#define SEL2         LATFbits.LATF1
#define TRIS_SEL1     TRISFbits.TRISF0
#define TRIS_SEL2     TRISFbits.TRISF1

// ---------
// X_Y
// ---------
#define X_Y         LATAbits.LATA11
#define TRIS_X_Y     TRISAbits.TRISA11

// ---------
// OE (Output Enabled, when OE = 0, the position is latch, when 1, new position is updated
// ---------
#define OE             LATBbits.LATB12
#define TRIS_OE     TRISBbits.TRISB12

// ---------
// RSTX, RSTY
// ---------
#define RSTX         LATFbits.LATF6
#define RSTY         LATFbits.LATF6
#define TRIS_RSTX    TRISFbits.TRISF6
#define TRIS_RSTY     TRISFbits.TRISF6
