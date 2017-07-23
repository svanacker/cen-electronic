#ifndef SERIAL_LINK_DEBUG_H
#define SERIAL_LINK_DEBUG_H

#include "serialLink.h"

#include "../../common/io/outputStream.h"

// DEBUG

/**
 * Print the serialLink information.
 * @param outputStream the outputStream where we write debug information.
 * @param serialLink the pointer on serialLink for which we want to debug information.
 * @param index the index of the serialLink in the list
 */
void printSerialLink(OutputStream* outputStream, const SerialLink* serialLink, int index);

/**
 * Print the list of serialLink.
 * @param outputStream the outputStream where we write debug information.
 */
void printSerialLinkList(OutputStream* outputStream);

/**
 * Debug Function which writes the content of each Buffer (input / output) to an outputStream.
 * @param outputStream the outputStream where we want to print the content of the buffer
 * @param serialLink the pointer on serialLink for which we want to debug information.
 */
void printSerialLinkBuffer(OutputStream* outputStream, const SerialLink* serialLink);

/**
 * Clear the content of each buffer (input / output) of the serialLink
 * @param serialLink the serialLink for which we would like to clear the buffers
 */
void clearSerialLinkBuffer(const SerialLink* serialLink);

#endif
