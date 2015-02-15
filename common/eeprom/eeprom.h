#ifndef EEPROM_H
#define EEPROM_H

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/io/buffer.h"

/** Define a value which has been erased by ICD3 programming. */
#define ERASED_VALUE_EEPROM         0xFFFF

// forward declaration
struct Eeprom;
typedef struct Eeprom Eeprom;

/**
 * Writes a value at the specified index into EEPROM.
 * @param eeprom_ a pointer on the Eeprom object (Simulates POO programming)
 * @param index the index of the WORD in the EEPROM table. Index 0 should not be used because this value is erased when reprogramming the device.
 * @param value the value to store
 */
typedef void EepromWriteIntFunction(Eeprom* eeprom_, unsigned long index, signed int value);

/**
 * Reads the value from the EEPROM at the given index.
 * @param eeprom_ a pointer on the Eeprom object (Simulates POO programming)
 * @param index the index of the WORD value to read
 * @return the WORD value as a signed int
 */
typedef signed int EepromReadIntFunction(Eeprom* eeprom_, unsigned long index);

/**
* Write the buffer into the Eeprom.
* @param eeprom_ a pointer on the Eeprom object (Simulates POO programming)
* @param index the index to write the buffer
* @param length the number of data to write
* @param buffer the pointer on buffer
*/
typedef void EepromWriteBlockFunction(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer);

/**
 * Read values from the EEPROM device.
 * Slave will return all values and store them in the buffer
 * @param eeprom_ a pointer on the Eeprom object (Simulates POO programming) 
 * @param index  the random address to read
 * @param length the number of data to read
 * @param buffer the pointer on buffer
 */
typedef void EepromReadBlockFunction(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer);

/**
 * Defines the contract for an eeprom.
 */
struct Eeprom {
    /** The function which must be used to write an int (16 bits). */
    EepromWriteIntFunction* eepromWriteInt;
    /** The function which must be used to read an int (16 bits). */
    EepromReadIntFunction* eepromReadInt;
    /** The function which must be used to write the content of a buffer to an eeprom device. */
    EepromWriteBlockFunction* eepromWriteBlock;
    /** The function which must be used to read the content of an eeprom into a buffer. */
    EepromReadBlockFunction* eepromReadBlock;
    /** Max Index. */
    long maxIndex;
};

/**
 * Returns the max Index of an eeprom.
 * @param eeprom_ the maximum index allowed by eeprom.
 * @param eeprom_ a pointer on the Eeprom object (Simulates POO programming) 
 * @return the max Index of an eeprom.
 */
long getMaxIndex(Eeprom* eeprom_);

// GLOBAL FUNCTIONS - NON SPECIFIC

/**
 * Init an eeprom object with all basic Functions.
 * @param eeprom_ a pointer on the Eeprom object (Simulates POO programming)
 * @param eepromWriteInt the pointer on the real hardware function which writes an int.
 * @param eepromReadInt the pointer on the real hardware function which reads an int.
 * @param eepromReadBlock the pointer on the real hardware function which writes a block of data.
 * @param eepromWriteBlock the pointer on the real hardware function which reads a block of data.
 */
void initEeprom(Eeprom* eeprom_,
                long maxIndex,
                EepromWriteIntFunction* eepromWriteInt,
                EepromReadIntFunction* eepromReadInt,
                EepromWriteBlockFunction* eepromWriteBlock,
                EepromReadBlockFunction* eepromReadBlock);
                
/**
 * Returns true if the eeprom is initialized (if the fields of callbacks are NOT NULL), false else.
 * @param eeprom_ a pointer on the Eeprom object (Simulates POO programming) 
 * @return true if the eeprom is initialized (if the fields of callbacks are NOT NULL), false else.
 */
bool isEepromInitialized(Eeprom* eeprom_);

/**
 * Print the values of the buffer on the outputStream from the EEPROM device.
 * Slave will return all values and print them on the outputStream
 * @param eeprom_ the pointer on the eeprom object
 * @param outputStream the outputStream in which we write the content of the eeprom
 * @param index the random address to read
 * @param length the number of data to read
 * @param buffer the pointer on buffer
 */
void printEepromBlock(Eeprom* eeprom_, OutputStream* outputStream, long index, unsigned int length, Buffer* buffer);

#endif
