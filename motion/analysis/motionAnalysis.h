#ifndef ASSER_ANALYSIS_H
#define ASSER_ANALYSIS_H

/**
 * This unit enables to send data to analyse PID to adjust the value
 * Data are structured to be analysed on Excel
 */

/**
 * Defines the structure which will be stored to have some sample of data.
 */
typedef struct {
    /** The pid time. */
    signed int pidTime;
    /** the left position. */
    signed int positionLeft;
    /** The right position. */
    signed int positionRight;
} Sample;

/**
 * Add a sample to the slavery.
 */
void addSample(int pidTime, int left, int right);

/**
 * Print the samples.
 */
void printSamples(void);

#endif
