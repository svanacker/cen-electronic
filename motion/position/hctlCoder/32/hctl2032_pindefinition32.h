#include <p32xxxx.h>

// ---------
// Input Bits 
// ---------

#define D0             PORTEbits.RE0
#define D1             PORTEbits.RE1
#define D2             PORTEbits.RE2
#define D3             PORTEbits.RE3
#define D4             PORTEbits.RE4
#define D5             PORTEbits.RE5
#define D6             PORTEbits.RE6
#define D7             PORTEbits.RE7

// PORT E0->E7 as input
#define TRIS_DX         0xFF

// ---------
// SEL1 - SEL2
// ---------

// Select the byte index to read 8 bits from 32 bits register
// -> 0/1 => Master Byte (Byte 1)
// -> 1/1 => Byte 2
// -> 0/0 => Byte 3
// -> 1/0 => Low Byte (Byte 4)
#define SEL1           LATBbits.LATB2
#define SEL2           LATBbits.LATB3
#define TRIS_SEL1      TRISBbits.TRISB2
#define TRIS_SEL2      TRISBbits.TRISB3


// ---------
// X_Y
// ---------
#define X_Y            LATBbits.LATB6
#define TRIS_X_Y       TRISBbits.TRISB6

// ---------
// OE (Output Enabled, when OE = 0, the position is latch, when 1, new position is updated
// ---------
#define OE             LATBbits.LATB4
#define TRIS_OE        TRISBbits.TRISB4

// ---------
// RSTX, RSTY
// ---------

#define RSTX         LATBbits.LATB5
#define RSTY         LATBbits.LATB5
#define TRIS_RSTX    TRISBbits.TRISB5
#define TRIS_RSTY    TRISBbits.TRISB5    

