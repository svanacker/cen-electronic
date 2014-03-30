#ifndef DRIVER_TRANSMITTER_H
#define DRIVER_TRANSMITTER_H

#include "../common/commons.h"

/**
 * Define a function which can be use to redirect driver transmission.
 */
typedef bool transmitFromDriverRequestBufferFunction();

/**
 * Intercepts and do a redirection on redirection transmission.
 */
void setRedirectionTransmitFromDriverRequestBuffer(transmitFromDriverRequestBufferFunction* function);

/**
* Transmit data from the driver request buffer to the right device.
* It assumes the requestBuffer, and responseBuffer are the classic driverBuffer
* It gets the first char on the dispatcher, and use it to determine the lenght of input, and the length of output
* @return the resultBuffer
*/
bool transmitFromDriverRequestBuffer();

#endif
