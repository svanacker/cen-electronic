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
#define SEL1           LATGbits.LATG6
#define SEL2           LATGbits.LATG9
#define TRIS_SEL1      TRISGbits.TRISG6
#define TRIS_SEL2      TRISGbits.TRISG9


// ---------
// X_Y
// ---------
#define X_Y            LATFbits.LATF3
#define TRIS_X_Y       TRISFbits.TRISF3

// ---------
// OE (Output Enabled, when OE = 0, the position is latch, when 1, new position is updated
// ---------
#define OE             LATFbits.LATF0
#define TRIS_OE        TRISFbits.TRISF0

// ---------
// RSTX, RSTY
// ---------

// TODO: TO FOUND FROM F4DEB DOCUMENTATION
#define RSTX         LATFbits.LATF1
#define RSTY         LATFbits.LATF1
#define TRIS_RSTX    TRISFbits.TRISF1
#define TRIS_RSTY    TRISFbits.TRISF1    

