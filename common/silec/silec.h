#ifndef COMMON_SILEC_H
#define COMMON_SILEC_H

#include <p32xxxx.h>
#include <peripheral/ports.h>

#include <../include/GenericTypeDefs.h>

#include <stdbool.h>

/**
 * Universal SILEC definition.
 */

#define STROBE_UCN5895 LATFbits.LATF0
#define SER_IN_UCN5895 LATFbits.LATF1
#define CLOCK_UCN5895 LATFbits.LATF3

#define STROBE_UCN5895_dir TRISFbits.TRISF0
#define SER_IN_UCN5895_dir TRISFbits.TRISF1
#define CLOCK_UCN5895_dir TRISFbits.TRISF3

#define A0_HC237 LATEbits.LATE0
#define A1_HC237 LATEbits.LATE1
#define A2_HC237 LATEbits.LATE2
#define E1_HC237 LATEbits.LATE3

#define A0_HC237_dir TRISEbits.TRISE0
#define A1_HC237_dir TRISEbits.TRISE1
#define A2_HC237_dir TRISEbits.TRISE2
#define E1_HC237_dir TRISEbits.TRISE3

typedef struct {
    int line0;
    int line1;
    int line2;
    int line3;
    int line4;
    int line5;
    int line6;
} SilecData;

// forward declaration
struct Silec;
typedef struct Silec Silec;

/**
 * initialise the specific SILEC hardware.
 * @param silecParam the pointer on SILEC object
 */
typedef void InitSILECFunction(Silec* silecParam);

/**
 * Update the specific SILEChardware with value from the struct.
 * @param silecParam the pointer on Silec object
 */
typedef void WriteSilecFunction(Silec* silecParam);

/**
 * Defines the contract for a Silec object.
 */
struct Silec {
    /** the function which must be used to initialise the hardwre SILEC */
    InitSILECFunction* initSILEC;
    /** The function which must be used to write the content of data to the hardware. */
    WriteSilecFunction* WriteSilec;    
    /** The content with all values. */    
    SilecData silecData;
    /** A pointer on generic object (for example to store I2cBus ...). */
    int* object;
};

/**
 * Returns true if the silec is initialized (if the fields of callbacks are NOT NULL), false else.
 * @param silec a pointer on the Ilec object (Simulates POO programming) 
 * @return true if the silec is initialized (if the fields of callbacks are NOT NULL), false else.
 */
bool isSilecInitialized(Silec* Silec);

/**
 * Initializes (Constructor in POO).
 * @param silecParam a pointer on Silec structure to initialize it.
 * @param WriteSilecFunction a pointer on the WriteSilecFunction
 * @param object A pointer on generic object (for example to store I2cBus ...).
 */
void initSilec(Silec* silecParam, 
        InitSILECFunction* InitSILECFunction,
        WriteSilecFunction* WriteSilecFunction,         
        int* object);

#endif

