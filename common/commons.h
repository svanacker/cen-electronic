#ifndef COMMONS_H
#define COMMONS_H

#define MAX_SIGNEDINT 0x7FFF
#define MAX_UNSIGNEDINT 0xFFFF
#define MIN_SIGNEDINT 0x8000
#define MIN_UNSIGNEDINT 0x0000

/**
 * Defining Boolean type
 */
#define BOOL unsigned int

#define FALSE 0
#define TRUE (!FALSE)

/** Carriage return : \r". */
#define CR 13

/** Line Feed : \n". */
#define LF 10

#define CLS 12

#define DECIMAL_SEPARATOR '.'

#define ACK 'a'

#define IN_AS_STRING "IN"
#define OUT_AS_STRING "OUT"

/**
 * Defines that we want to run with MPLAB SIMULATION
 */
// #define MPLAB_SIMULATION

/**
 * Defines a function to do the same as "equals(Object obj)" in Java.
 * @param object pointer on a structure for object1
 * @param object pointer on a structure for object2
 */
typedef BOOL EqualsFunction(int* object1, int* object2);

#endif
