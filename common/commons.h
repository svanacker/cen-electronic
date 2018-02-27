#ifndef COMMONS_H
#define COMMONS_H

// For Visual Studio - Emulation Program
#ifdef _MSC_VER
    #define PC_COMPILER
#endif

#ifdef __32MX795F512H__
    #define PROG_32
#endif

#ifdef __dsPIC30F4013__
    #define PROG_30
#endif

// Detects if there is a problem : not in 30F mode, neither 32, neither PC
#ifndef PROG_30
    #ifndef PROG_32
        #ifndef PC_COMPILER
#error "Must not Compile because target (30, 32 or PC) is not defined"
        #endif
    #endif
#endif

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

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

//// Special Characters Definition

/** Define the ASCII table STX value. */
#define ASCII_STX '\2'

/** Define the ASCII table ETX value. */
#define ASCII_ETX '\3'

/** Define the ASCII table ASCII ACK value. */
#define ASCII_ACK '\6'

/** Line Feed : \n". */
#define LF 10

/** Carriage return : \r". */
#define CR 13

/** Clear Screnn. */
#define CLS 12

//// Classical values

#define DECIMAL_SEPARATOR '.'

#define ACK 'a'

#define IN_AS_STRING "IN"
#define OUT_AS_STRING "OUT"

#endif
