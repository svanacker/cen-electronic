#ifndef PIN_H
#define PIN_H

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/error/error.h"
#include "outputStream.h"

// forward declaration
struct PinList;
typedef struct PinList PinList;

/**
 * Get the pin value for the index.
 * @param pinList the encapsulation of the list of pin
 * @param the index of the pin
 * true if the pin is on, false if the pin is off
 */
typedef bool GetPinValueFunction(PinList* pinList, int pinIndex);

/**
 * Set the value for the pin Index (see pin.h)
 * @param pinList the encapsulation of the list of pin
 * @param the index of the pin
 * @param pinValue the new value of the pin
 */
typedef void SetPinValueFunction(PinList* pinList, int pinIndex, bool pinValue);

/**
 * Initialise a pin List for Pc.
 * @param pinList pointer on pinList object (POO Paradigm)
 */
void initPinList(PinList* pinList, GetPinValueFunction* getPinValueFunction, SetPinValueFunction* setPinValueFunction, int* object);

struct PinList {
    /** The function which must be called to get the status of a pin. */
    GetPinValueFunction* getPinValueFunction;
    /** The function which must be called to set a pin. */
    SetPinValueFunction* setPinValueFunction;
    /** pointer on other object (useful PC Implementation for example).*/
    int* object;
};

// PIC32 Definition : http://ww1.microchip.com/downloads/en/devicedoc/60001156j.pdf

// PORT A : only for PIC with 100 pin
#define PIN_INDEX_RA0        0x00
#define PIN_INDEX_RA1        0x01
#define PIN_INDEX_RA2        0x02
#define PIN_INDEX_RA3        0x03
#define PIN_INDEX_RA4        0x04
#define PIN_INDEX_RA5        0x05
#define PIN_INDEX_RA6        0x06
#define PIN_INDEX_RA7        0x07
#define PIN_INDEX_RA8        0x08
#define PIN_INDEX_RA9        0x09
#define PIN_INDEX_RA10       0x0A
#define PIN_INDEX_RA11       0x0B
#define PIN_INDEX_RA12       0x0C
#define PIN_INDEX_RA13       0x0D
#define PIN_INDEX_RA14       0x0E
#define PIN_INDEX_RA15       0x0F

// Port B : all PIC 32

#define PIN_INDEX_RB0        0x10
#define PIN_INDEX_RB1        0x11
#define PIN_INDEX_RB2        0x12
#define PIN_INDEX_RB3        0x13
#define PIN_INDEX_RB4        0x14
#define PIN_INDEX_RB5        0x15
#define PIN_INDEX_RB6        0x16
#define PIN_INDEX_RB7        0x17
#define PIN_INDEX_RB8        0x18
#define PIN_INDEX_RB9        0x19
#define PIN_INDEX_RB10       0x1A
#define PIN_INDEX_RB11       0x1B
#define PIN_INDEX_RB12       0x1C
#define PIN_INDEX_RB13       0x1D
#define PIN_INDEX_RB14       0x1E
#define PIN_INDEX_RB15       0x1F

// Port C
#define PIN_INDEX_RC0        0x20
#define PIN_INDEX_RC1        0x21
#define PIN_INDEX_RC2        0x22
#define PIN_INDEX_RC3        0x23
#define PIN_INDEX_RC4        0x24
#define PIN_INDEX_RC5        0x25
#define PIN_INDEX_RC6        0x26
#define PIN_INDEX_RC7        0x27
#define PIN_INDEX_RC8        0x28
#define PIN_INDEX_RC9        0x29
#define PIN_INDEX_RC10       0x2A
#define PIN_INDEX_RC11       0x2B
#define PIN_INDEX_RC12       0x2C
#define PIN_INDEX_RC13       0x2D
#define PIN_INDEX_RC14       0x2E
#define PIN_INDEX_RC15       0x2F

// Port D
#define PIN_INDEX_RD0        0x30
#define PIN_INDEX_RD1        0x31
#define PIN_INDEX_RD2        0x32
#define PIN_INDEX_RD3        0x33
#define PIN_INDEX_RD4        0x34
#define PIN_INDEX_RD5        0x35
#define PIN_INDEX_RD6        0x36
#define PIN_INDEX_RD7        0x37
#define PIN_INDEX_RD8        0x38
#define PIN_INDEX_RD9        0x39
#define PIN_INDEX_RD10       0x3A
#define PIN_INDEX_RD11       0x3B
#define PIN_INDEX_RD12       0x3C
#define PIN_INDEX_RD13       0x3D
#define PIN_INDEX_RD14       0x3E
#define PIN_INDEX_RD15       0x3F

// Port E
#define PIN_INDEX_RE0        0x40
#define PIN_INDEX_RE1        0x41
#define PIN_INDEX_RE2        0x42
#define PIN_INDEX_RE3        0x43
#define PIN_INDEX_RE4        0x44
#define PIN_INDEX_RE5        0x45
#define PIN_INDEX_RE6        0x46
#define PIN_INDEX_RE7        0x47
#define PIN_INDEX_RE8        0x48
#define PIN_INDEX_RE9        0x49
#define PIN_INDEX_RE10       0x4A

// PORT F
#define PIN_INDEX_RF0        0x50
#define PIN_INDEX_RF1        0x51
#define PIN_INDEX_RF2        0x52
#define PIN_INDEX_RF3        0x53
#define PIN_INDEX_RF4        0x54
#define PIN_INDEX_RF5        0x55
#define PIN_INDEX_RF6        0x56
#define PIN_INDEX_RF7        0x57
#define PIN_INDEX_RF8        0x58

#define PIN_MIN_INDEX        PIN_INDEX_RA0
#define PIN_MAX_INDEX        PIN_INDEX_RF8

/**
 * Returns the value of the pin Index (see pin.h)
 * @param pinList the encapsulation of the list of pin
 * @param the index of the pin
 * @return 
 */
bool getPinValue(PinList* pinList, int pinIndex);

/**
 * Set the value for the pin Index (see pin.h)
 * @param pinList the encapsulation of the list of pin
 * @param the index of the pin
 * @param pinValue the new value of the pin
 */
void setPinValue(PinList* pinList, int pinIndex, bool pinValue);

#endif

