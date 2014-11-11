#ifndef ASSER_ANALYSIS_H
#define ASSER_ANALYSIS_H

/**
* This unit enables to send data to analyze PID to adjust the value
* Data are structured to be analysed on Excel
* @author svanacker
* @version 18/05/2010
*/

/**
* Defines the structure which will be stored
*/
typedef struct {
    signed int pidTime;
    signed int positionLeft;
    signed int positionRight;
} Sample;

/**
* Add a sample to the slavery
*/
void addSample(int pidTime, int left, int right);

/**
* Print the samples
*/
void printSamples(void);

#endif
