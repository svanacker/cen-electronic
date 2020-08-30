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

// EVENT

/**
 * Callback function which must be used when the value is changing from previous
 * @param ioExpander the ioExpander (source of the event)
 * @param value the value of the ioExpander
 * @param eventContext an object of context for event
 */
typedef void ioExpanderOnValueChangeEventFunction(IOExpander* ioExpander, unsigned char value, int* eventContext);

/**
 * Defines the contract IO Expander like PCF8574.
 */
struct IOExpander {
    /** The name of the IO Expander. */
    char* name;
    // IMPLEMENTATION
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
    // EVENTS
    ioExpanderOnValueChangeEventFunction* ioExpanderOnValueChangeEvent;
    // A pointer on an object which will be provide to the callback
    int* eventContext;
    // SCALAR VALUES
    /** How many IO are managed .*/
    unsigned int count;
    /** Last value (must not be handled by external systems, but needed when writing a single bit
     * (to avoid to read before writing) */
    unsigned value;
    /** pointer on other object (useful for I2C Connection for example) .*/
    int* object;
};

/** 
 * Init the wrapper around IO Expander. 
 */
void initIOExpander(IOExpander* ioExpander,
        char* name,
        ioExpanderInitFunction* ioExpanderInit,
        ioExpanderReadValueFunction* ioExpanderReadValue,
        ioExpanderWriteValueFunction* ioExpanderWriteValue,
        ioExpanderReadSingleValueFunction* ioExpanderReadSingleValue,
        ioExpanderWriteSingleValueFunction* ioExpanderWriteSingleValue,
        unsigned int count,
        int* object);

/**
 * Set the event callback Function when value change.
 * @param ioExpander the IO Expander Object
 * @param ioExpanderOnValueChangeEvent the callback function which must be called
 * when value change
 */
void ioExpanderSetOnValueChangeEvent(IOExpander* ioExpander, 
                                     ioExpanderOnValueChangeEventFunction* ioExpanderOnValueChangeEvent,
                                     int* eventContext);

#endif
