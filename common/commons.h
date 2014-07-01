#ifndef COMMONS_H
#define COMMONS_H

#include <stdbool.h>

/**
 * Defines that we want to run with MPLAB SIMULATION
 */
//#define MPLAB_SIMULATION

#define PROG_32

#ifdef PROG_32
    #define QUARTZ_FREQUENCY    8000000L
    #define CLOCK_PLL           20
    #define FOSC                (QUARTZ_FREQUENCY * CLOCK_PLL / 2)
#else
    #define QUARTZ_FREQUENCY    7372800L
    #define CLOCK_PLL           16
#endif

#define CYCLE_FREQUENCY     (QUARTZ_FREQUENCY * CLOCK_PLL / 4)


// TODO ; Change for 32 !!
#define MAX_SIGNEDINT 0x7FFF
#define MAX_UNSIGNEDINT 0xFFFF
#define MIN_SIGNEDINT 0x8000
#define MIN_UNSIGNEDINT 0x0000

/** Carriage return : \r". */
#define CR 13

/** Line Feed : \n". */
#define LF 10

#define CLS 12

#define DECIMAL_SEPARATOR '.'

#define ACK 'a'

#define IN_AS_STRING "IN"
#define OUT_AS_STRING "OUT"

#endif
