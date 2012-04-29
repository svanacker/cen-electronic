#include <p30fxxxx.h>

#include "../../motion/position/hctl2032.h"

#include "../../common/delay/delay30F.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

// ---------
// Input Bits 
// ---------

#define D0 			PORTBbits.RB0
#define D1 			PORTBbits.RB1
#define D2 			PORTBbits.RB2
#define D3 			PORTBbits.RB3
#define D4 			PORTBbits.RB8
#define D5 			PORTBbits.RB9
#define D6 			PORTBbits.RB10
#define D7 			PORTBbits.RB11

// PORT B0->B3 as input
// PORT B8->B11 as input
// PORT B4->B7 as output
// PORT B12->B15 as output
#define TRIS_DX 	0b0000111100001111

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
#define SEL1 		LATFbits.LATF0 		//by JJ PORTCbits.RC14
#define SEL2 		LATFbits.LATF1
#define TRIS_SEL1 	TRISFbits.TRISF0	//by JJTRISCbits.TRISC14
#define TRIS_SEL2 	TRISFbits.TRISF1

#define MASTER_BYTE_INDEX 3
#define BYTE_3_INDEX 2
#define BYTE_2_INDEX 1
#define LOW_BYTE_INDEX 0

// ---------
// X_Y
// ---------
#define X_Y 		LATAbits.LATA11
#define TRIS_X_Y 	TRISAbits.TRISA11

// ---------
// OE (Output Enabled, when OE = 0, the position is latch, when 1, new position is updated
// ---------
#define OE 			LATBbits.LATB12
#define TRIS_OE 	TRISBbits.TRISB12

// ---------
// RSTX, RSTY
// ---------
#define RSTX 		LATFbits.LATF6
#define RSTY 		LATFbits.LATF6
#define TRIS_RSTX	TRISFbits.TRISF6
#define TRIS_RSTY 	TRISFbits.TRISF6

// variables
static Coder coders[CODER_COUNT];

/**
 * Init the device.
 */
void initHCTL2032() {

    // Init I/0

    // Reset as ouput
    TRIS_RSTX = 0;
    TRIS_RSTY = 0;

    // X_Y as output
    TRIS_X_Y = 0;

    // SEL1 / SEL2 as output
    TRIS_SEL1 = 0;
    TRIS_SEL2 = 0;

    // OE as output
    TRIS_OE = 0;

    // Avoid reset of the coder value
    RSTX = 1;
    RSTY = 1;

    //Initialize LED pin data to off state
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    // PORTF = 0;
    TRISD = 0;

    // PORTB as digital
    ADPCFG = 0xFFFF;

    // PORTB as input for data (8 bits in parallel)
    TRISB = TRIS_DX;

    // RSTX / RSTY to 1 to avoid reset (see doc)
    RSTX = 1;
    RSTY = 1;

    // Il faut l'initialiser 3 fois pour que �a marche !
    RSTY = 1;
    RSTX = 1;

    hctl_clearCoders();
}

/**
 * Get the struct of a coder.
 */
Coder* getCoder(int coderIndex) {
    Coder* result = &coders[coderIndex];
    return result;
}

signed long hctl_getCoderValue(int coderIndex) {
    Coder* localCoder = getCoder(coderIndex);
    return localCoder->value;
}

void hctl_resetCoderValue(int coderIndex) {
    Coder* localCoder = getCoder(coderIndex);
    // Reset the internal values
    localCoder->value = 0;
    localCoder->previousValue = 0;
    // reset on the HCTL the index
    switch (coderIndex) {
        case X_INDEX:
            // do the reset
            RSTX = 0;
            // avoid reset
            RSTX = 1;
            break;
        case Y_INDEX:
        {
            // do the reset
            RSTY = 0;
            // avoid reset
            RSTY = 1;
            break;
        }
    }
}

void hctl_clearCoders() {
    int index;
    for (index = 0; index < CODER_COUNT; index++) {
        hctl_resetCoderValue(index);
    }
}

/**
 * Set the selection port to read the correct value on the D0-D7 port on HCTL2032.
 * @param selectionIndex value between (0=LOW_BYTE_INDEX and 3=MASTER_BYTE_INDEX)
 */
void setSelectionIndex(int selectionIndex) {
    switch (selectionIndex) {
        case MASTER_BYTE_INDEX:
        {
            SEL1 = 0;
            SEL2 = 1;
            break;
        }
        case BYTE_3_INDEX:
        {
            SEL1 = 1;
            SEL2 = 1;
            break;
        }
        case BYTE_2_INDEX:
        {
            SEL1 = 0;
            SEL2 = 0;
            break;
        }
        case LOW_BYTE_INDEX:
        {
            SEL1 = 1;
            SEL2 = 0;
            break;
        }
    }
}

/**
 * Read and latchs for BOTH coders position.
 * We must use latchs for BOTH coders to avoid gap between coders position due to read time gap.
 */
void readAndLatchPositions() {
    // Ask to update the position
    OE = 1;
    delaymSec(1);

    // block the position (use latch)
    OE = 0;
}

/**
 * Read the coder value on the D0-D7 on HCTL2032.
 * @return a value between 0 and 255
 */
unsigned long readCoderByteValue() {
    unsigned long value = 0;

    if (D7) {
        value += 128;
    }
    if (D6) {
        value += 64;
    }
    if (D5) {
        value += 32;
    }
    if (D4) {
        value += 16;
    }
    if (D3) {
        value += 8;
    }
    if (D2) {
        value += 4;
    }
    if (D1) {
        value += 2;
    }
    if (D0) {
        value += 1;
    }
    return value;
}

/**
 * Read the coderValue.
 * @param coderIndex either CODER_X or CODER_Y
 */
void readCoderValue(int coderIndex) {
    signed long value = 0;

    unsigned long coderByteValue;
    int shiftValue;

    X_Y = coderIndex;

    int selectionIndex;
    for (selectionIndex = LOW_BYTE_INDEX; selectionIndex <= MASTER_BYTE_INDEX; selectionIndex++) {
        // Select the coder
        setSelectionIndex(selectionIndex);
        // read the byte indexed by selectionIndex
        coderByteValue = readCoderByteValue(coderIndex);
        // shift value : 0, 8, 16 or 24
        shiftValue = selectionIndex * 8;
        value += coderByteValue << shiftValue;
    }
    // Stores in memory the value
    Coder* localCoder = getCoder(coderIndex);
    localCoder->previousValue = localCoder->value;
    localCoder->value = value;
}

/**
 * Read the value of each coders, and store them in memory.
 */
void hctl_updateCoders() {
    // latch for both X and Y read to avoid gab between read of X and Y
    readAndLatchPositions();
    readCoderValue(X_INDEX);
    readCoderValue(Y_INDEX);
}

/**
 * Print the value of a coder.
 */
void printCoderValue(OutputStream* outputStream, int coderIndex) {
    unsigned long value = hctl_getCoderValue(coderIndex);
    appendDec(outputStream, value);
}

/**
 * Print the values of both coder.
 */
void hctl_printCodersValue(OutputStream* outputStream) {
    appendString(outputStream, "X=");
    printCoderValue(outputStream, X_INDEX);
    appendString(outputStream, ",Y=");
    printCoderValue(outputStream, Y_INDEX);
    println(outputStream);
}

/**
 * Returns TRUE if the previousValue and value has change.
 */
int hctl_hasCoderValueChange(int coderIndex) {
    Coder* localCoder = &coders[coderIndex];
    return localCoder->value != localCoder->previousValue;
}

/**
 * Returns TRUE if any change appears on X_CODER or Y_CODER.
 */
int hctl_hasAnyCoderValueChange() {
    int result = hctl_hasCoderValueChange(X_INDEX) || hctl_hasCoderValueChange(Y_INDEX);
    return result;
}
