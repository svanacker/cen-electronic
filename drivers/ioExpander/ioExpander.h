#ifndef IO_EXPANDER_H
#define IO_EXPANDER_H

#include <stdbool.h>

// forward declaration
struct IOExpander;
typedef struct IOExpander IOExpander;

/**
 * Type of function to initialize the IO Expander.
 */
typedef bool ioExpanderInitFunction(IOExpander* ioExpander);

// ALL BITS

/**
* Read all values of the IO.
* @return the value of the IO Expander
*/
typedef unsigned char ioExpanderReadValueFunction(IOExpander* ioExpander);

/**
* Write a value to drive the ioExpander as Output for all ios.
*/
typedef void ioExpanderWriteValueFunction(IOExpander* ioExpander, unsigned char value);

// SINGLE BIT 

/**
* Read if the IO is on or off for the specified io
* @return the value of the IO Expander
*/
typedef bool ioExpanderReadSingleValueFunction(IOExpander* ioExpander, unsigned int ioIndex);

/**
* Write a value to drive the ioExpander as Output for a single io.
*/
typedef void ioExpanderWriteSingleValueFunction(IOExpander* ioExpander, unsigned int ioIndex, bool value);

/**
* Defines the contract IO Expander like PCF8574.
*/
struct IOExpander {
    /** The function which must be used to init the io */
    ioExpanderInitFunction* ioExpanderInit;
    /** The function which must be used to read all values at the same time */
    ioExpanderReadValueFunction* ioExpanderReadValue;
    /** The function which can be used to write all values at the same time. */
    ioExpanderWriteValueFunction* ioExpanderWriteValue;
    /** The function which must be used to read the value of each io */
    ioExpanderReadSingleValueFunction* ioExpanderReadSingleValue;
    /** The function which can be used to change the value of a specific io. */
    ioExpanderWriteSingleValueFunction* ioExpanderWriteSingleValue;
    /** How many IO are managed .*/
    unsigned int count;
    /** Last value (must not be handled by external systems) */
    unsigned value;
    /** pointer on other object (useful for I2C Connection for example) .*/
    int* object;
};

/** 
 * Init the wrapper around IO Expander. 
 */
void initIOExpander(IOExpander* ioExpander,
               ioExpanderInitFunction* ioExpanderInit,
               ioExpanderReadValueFunction* ioExpanderReadValue,
               ioExpanderWriteValueFunction* ioExpanderWriteValue,
               ioExpanderReadSingleValueFunction* ioExpanderReadSingleValue,
               ioExpanderWriteSingleValueFunction* ioExpanderWriteSingleValue,
               unsigned int count,
               int* object);

#endif
