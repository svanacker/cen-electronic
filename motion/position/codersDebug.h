#ifndef CODERS_DEBUG_H
#define CODERS_DEBUG_H

#include "coders.h"

#include "../../common/io/outputStream.h"

#define CODER_DEBUG_HISTORY_COUNT    1000

/** Structure to store Coder Data. */
typedef struct {
    signed long left;
    signed long right;
} CoderData;

typedef struct {
    /** The current index. */
    unsigned int writeIndex;
    /** How many data we would like to acquire .*/
    unsigned int sampleToAcquire;
    CoderData coderHistory[CODER_DEBUG_HISTORY_COUNT];
} CoderDataHistory;

// SYNCHRONOUS READ

/**
 * Print the current value of coder table.
 */
void printCurrentCoderTable(OutputStream* outputStream);

// ASYNCHRONOUS SAMPLING

/**
 * Enable the record of sample during a period of time and for an amount of data to acquire
 * @param dataToAcquireCountParam the amount of sample to get
 * @param samplingRateMilliSeconds how many milliseconds between each sample
 */
void enableCoderSampleRecording(unsigned int sampleCountParam, unsigned int samplingRateMilliSeconds);

/**
* Print the coder history.
*/
void printSampleCoderHistory(OutputStream* outputStream);

#endif
