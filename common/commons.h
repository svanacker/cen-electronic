#ifndef COMMONS_H
#define COMMONS_H

/**
 * Defines that we want to run with MPLAB SIMULATION
 */
// #define MPLAB_SIMULATION

#ifdef __32MX795F512H__
    #define PROG_32
#endif

#ifdef __dsPIC30F4013__
    #define PROG_30
#endif

#ifndef PROG_30
    #ifndef PROG_32
        MUST NOT COMPILE !!
    #endif
#endif

#ifdef PROG_32
    #define QUARTZ_FREQUENCY    8000000L
    #define CLOCK_PLL           20
    #define FOSC                (QUARTZ_FREQUENCY * CLOCK_PLL / 2)
#endif

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
