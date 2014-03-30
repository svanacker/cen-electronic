#ifndef COMMONS_H
#define COMMONS_H

#include <stdbool.h>

/**
 * Defines that we want to run with MPLAB SIMULATION
 */
// #define MPLAB_SIMULATION

#define PROG_32
// #include <GenericTypeDefs.h>
// #define PROG_32
// #include <GenericTypeDefs.h>

// TODO ; Change for 32 !!
#define MAX_SIGNEDINT 0x7FFF
#define MAX_UNSIGNEDINT 0xFFFF
#define MIN_SIGNEDINT 0x8000
#define MIN_UNSIGNEDINT 0x0000




// #define bool unsigned char

// #define false 0
// #define true (!false)

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
 * Defines a function to do the same as "equals(Object obj)" in Java.
 * @param object pointer on a structure for object1
 * @param object pointer on a structure for object2
 */
// typedef bool EqualsFunction(int* object1, int* object2);

#endif
