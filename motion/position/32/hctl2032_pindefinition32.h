#include <p32xxxx.h>

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
// EN1 - EN2 (HARDLY CONNECTED)
// ---------

// Enable1/Enable2 to select the 1x, 2x, 4x factor
// EN1 - EN2
// -> 0/0 => Illegal Mode
// -> 1/0 => Factor x4
// -> 0/1 => Factor x2
// -> 1/1 => Factor x1

// ---------
// SEL1 - SEL2
// ---------

// Select the byte index to read 8 bits from 32 bits register
// -> 0/1 => Master Byte (Byte 1)
// -> 1/1 => Byte 2
// -> 0/0 => Byte 3
// -> 1/0 => Low Byte (Byte 4)
#define SEL1         LATFbits.LATF0         //by JJ PORTCbits.RC14
#define SEL2         LATFbits.LATF1
#define TRIS_SEL1     TRISFbits.TRISF0    //by JJTRISCbits.TRISC14
#define TRIS_SEL2     TRISFbits.TRISF1

#define MASTER_BYTE_INDEX 3
#define BYTE_3_INDEX 2
#define BYTE_2_INDEX 1
#define LOW_BYTE_INDEX 0

// ---------
// X_Y
// ---------
#ifdef PROG_32
    // TODO : To FIND !
    #define X_Y         LATBbits.LATB0
    #define TRIS_X_Y    TRISBbits.TRISB0
#else
    #define X_Y         LATAbits.LATA11
    #define TRIS_X_Y     TRISAbits.TRISA11
#endif

// ---------
// OE (Output Enabled, when OE = 0, the position is latch, when 1, new position is updated
// ---------
#define OE             LATBbits.LATB12
#define TRIS_OE     TRISBbits.TRISB12

// ---------
// RSTX, RSTY
// ---------
#ifdef PROG_32
    // TODO : TO FIND THE NEW VALUE !!!
    #define RSTX         LATFbits.LATF0
    #define RSTY         LATFbits.LATF0
    #define TRIS_RSTX    TRISFbits.TRISF0
    #define TRIS_RSTY     TRISFbits.TRISF0    
#else
    #define RSTX         LATFbits.LATF6
    #define RSTY         LATFbits.LATF6
    #define TRIS_RSTX    TRISFbits.TRISF6
    #define TRIS_RSTY     TRISFbits.TRISF6
#endif

