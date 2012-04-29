#ifndef PIN_H
#define PIN_H

#include "../../common/commons.h"

#include "outputStream.h"

// Port B

#define PIN_INDEX_RB0		0x00
#define PIN_INDEX_RB1		0x01
#define PIN_INDEX_RB2		0x02
#define PIN_INDEX_RB3		0x03
#define PIN_INDEX_RB4		0x04
#define PIN_INDEX_RB5		0x05
#define PIN_INDEX_RB6		0x06
#define PIN_INDEX_RB7		0x07
#define PIN_INDEX_RB8		0x08
#define PIN_INDEX_RB9		0x09
#define PIN_INDEX_RB10		0x0A
#define PIN_INDEX_RB11		0x0B
#define PIN_INDEX_RB12		0x0C

// Port C
#define PIN_INDEX_RC13		0x0D	// 13
#define PIN_INDEX_RC14		0x0E	// 14
#define PIN_INDEX_RC15		0x0F	// 15

// Port D
#define PIN_INDEX_RD0		0x14	// 20
#define PIN_INDEX_RD1		0x15	// 21
#define PIN_INDEX_RD2		0x16	// 22
#define PIN_INDEX_RD3		0x17	// 23
#define PIN_INDEX_RD8		0x1C	// 28
#define PIN_INDEX_RD9		0x1D	// 29

// Port A
#define PIN_INDEX_RA11		0x1F	// 31

// Port F
#define PIN_INDEX_RF0		0x28	// 40
#define PIN_INDEX_RF6		0x2E	// 46

#define PIN_MIN_INDEX		0x00
#define PIN_MAX_INDEX		PIN_INDEX_RF6

/**
 * Get the pin value for the index
 */
BOOL getPinValue(int pinIndex);

/**
 * Set the value for the pin Index (see pin.h)
 */
void setPinValue(int pinIndex, BOOL pinValue);

/**
 * Print All Pin Values.
 */
void printAllPinValues(OutputStream* outputStream);

#endif

