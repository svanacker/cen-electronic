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

/**
* Read if the IO is on or off for the specified index.
* @return index the value of the IO Expander
*/
typedef bool ioExpanderReadValueFunction(IOExpander* ioExpander, int index);

/**
* Write a value to drive the ioExpander as Output.
*/
typedef void ioExpanderWriteValueFunction(IOExpander* ioExpander, int index, bool value);

/**
* Defines the contract IO Expander like PCF8574.
*/
struct IOExpander {
    /** The function which must be used to init the io */
    ioExpanderInitFunction* ioExpanderInit;
    /** The function which must be used to read the value of each io */
    ioExpanderReadValueFunction* ioExpanderReadValue;
    /** The function which can be used to change the value of a specific io. */
    ioExpanderWriteValueFunction* ioExpanderWriteValue;
    /** How many IO are managed .*/
    unsigned int count;
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
               unsigned int count,
               int* object);

#endif
