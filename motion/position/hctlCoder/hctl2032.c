#include "hctl2032.h"

#include "../../../common/delay/cenDelay.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../motion/position/coders.h"
#include "../../../motion/position/coderType.h"


#ifdef PROG_32
    #include "32/hctl2032_pindefinition32.h"
#else
    #include "30F/hctl2032_pindefinition30F.h"
    #include <p30Fxxxx.h>
#endif

// variables
static Coder coders[CODER_COUNT];

/**
 * Init the device.
 */
void initHCTL2032() {

    // Init I/0

    // Reset as output
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
    #ifndef PROG_32
        ADPCFG = 0xFFFF;
    #endif

    // PORTE as input for data (8 bits in parallel)
    TRISE = TRIS_DX;

    // RSTX / RSTY to 1 to avoid reset (see doc)
    RSTX = 1;
    RSTY = 1;

    // We add to initialize it 3 times so that it works
    RSTY = 1;
    RSTX = 1;

    hctl_clearCoders();
}

/**
 * Get the struct of a coder.
 */
Coder* getCoder(enum CoderType coderType) {
    Coder* result = &coders[coderType];
    return result;
}

signed long hctl_getCoderValue(enum CoderType coderType) {
    Coder* localCoder = getCoder(coderType);
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
void readAndLatchPositions(void) {
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
unsigned long readCoderByteValue(void) {
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
void readCoderValue(enum CoderType coderType) {
    signed long value = 0;

    unsigned long coderByteValue;
    int shiftValue;

    X_Y = coderType;

    int selectionIndex;
    for (selectionIndex = LOW_BYTE_INDEX; selectionIndex <= MASTER_BYTE_INDEX; selectionIndex++) {
        // Select the coder
        setSelectionIndex(selectionIndex);
        // read the byte indexed by selectionIndex
        coderByteValue = readCoderByteValue();
        // shift value : 0, 8, 16 or 24
        shiftValue = selectionIndex * 8;
        value += coderByteValue << shiftValue;
    }
    // Stores in memory the value
    Coder* localCoder = getCoder(coderType);
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
 * Returns true if the previousValue and value has change.
 */
int hctl_hasCoderValueChange(int coderIndex) {
    Coder* localCoder = &coders[coderIndex];
    return localCoder->value != localCoder->previousValue;
}

/**
 * Returns true if any change appears on X_CODER or Y_CODER.
 */
int hctl_hasAnyCoderValueChange() {
    int result = hctl_hasCoderValueChange(X_INDEX) || hctl_hasCoderValueChange(Y_INDEX);
    return result;
}
