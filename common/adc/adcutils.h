#ifndef ADC_UTILS_H
#define ADC_UTILS_H

#include "../../common/io/outputStream.h"

/**
* Get a value of the channel (A / D conversion)
* @param channel the channel index between 0 and 11
* @return the value in millivolt.
*/
int getANX (unsigned char channel);

/**
 * Returns how many ANX are managed.
 * @return how many ANX are managed.
 */
int getANXCount();

/**
 * Print the list of Adc as a table
 * @param outputStream where we write the list
 */
void printAdcList(OutputStream* outputStream);

#endif

