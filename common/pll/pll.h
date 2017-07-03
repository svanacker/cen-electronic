#ifndef COMMON_PLL_H
#define COMMON_PLL_H

#include <../include/GenericTypeDefs.h>

#include <stdbool.h>

/**
 * Universal PLL definition.
 */
typedef struct {
    INT32 REGA;
    INT32 REGM;
    INT32 REGR;
    INT32 pllFrequency;
} PllData;

// forward declaration
struct Pll;
typedef struct Pll Pll;

/**
 * initialise the specific PLL hardware.
 * @param pllParam the pointer on PLL object
 */
typedef void InitPLLFunction(Pll* pllParam);

/**
 * Update the specific PLLhardware with value from the struct.
 * @param pllParam the pointer on Pll object
 */
typedef void WritePllFunction(Pll* pllParam);

/**
 * Defines the contract for a Pll object.
 */
struct Pll {
    /** the function which must be used to initialise the hardwre PLL */
    InitPLLFunction* initPLL;
    /** The function which must be used to write the content of data to the hardware. */
    WritePllFunction* WritePll;    
    /** The content with all values. */    
    PllData pllData;
    /** A pointer on generic object (for example to store I2cBus ...). */
    int* object;
};

/**
 * Returns true if the pll is initialized (if the fields of callbacks are NOT NULL), false else.
 * @param pll a pointer on the Pll object (Simulates POO programming) 
 * @return true if the pll is initialized (if the fields of callbacks are NOT NULL), false else.
 */
bool isPllInitialized(Pll* Pll);

/**
 * Initializes (Constructor in POO).
 * @param pllParam a pointer on Pll structure to initialize it.
 * @param WritePllFunction a pointer on the WritePllFunction
 * @param object A pointer on generic object (for example to store I2cBus ...).
 */
void initPll(Pll* pllParam, 
        InitPLLFunction* InitPLLFunction,
        WritePllFunction* WritePllFunction,         
        int* object);

#endif

