#ifndef COMMON_SILEC_H
#define COMMON_SILEC_H

#include <../include/GenericTypeDefs.h>

#include <stdbool.h>

/**
 * Universal SILEC definition.
 */
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

