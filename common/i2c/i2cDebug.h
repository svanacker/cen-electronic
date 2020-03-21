#ifndef I2C_DEBUG_H
#define I2C_DEBUG_H

#include <stdbool.h>


#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"

/**
 * Returns if we must debug I2C or not.
 * @return true if the I2C debug mode is enabled, false else.
 */
bool getDebugI2cEnabled();

/**
 * Enabled or not the I2C Debug Buffer.
 * @param enabled the new value for the I2C Debug mode
 */
void setDebugI2cEnabled(bool enabled);

/**
 * Get the input buffer to debug I2C.
 * @return a pointer on the buffer used to debug the I2C (Input Part).
 */
// Buffer* getDebugI2cInputBuffer();

/**
 * Get the output buffer to debug I2C.
 * @return a pointer on the buffer used to debug the I2C (Output Part).
 */
// Buffer* getDebugI2cOutputBuffer();

/**
 * Init the I2C debug buffers.
 * @param aDebugI2cInputBuffer pointer on the debug buffer for I2C Input
 * @param debugI2cInputBufferArray the array of char used by the buffer to store I2C Input
 * @param debugI2cInputBufferLength the length of the array of char used by the buffer to store I2C Input
 * @param aDebugI2cOutputBuffer pointer on the debug buffer for I2C Output
 * @param debugI2cOutputBufferArray the array of char used by the buffer to store I2C Output
 * @param debugI2cOutputBufferLength the length of the array of char used by the buffer to store I2C Output
 */
void initI2CDebugBuffers(Buffer* aDebugI2cInputBuffer,
        unsigned char(*debugI2cInputBufferArray)[],
        unsigned int debugI2cInputBufferLength,
        Buffer* aDebugI2cOutputBuffer,
        unsigned char(*debugI2cOutputBufferArray)[],
        unsigned int debugI2cOutputBufferLength
        );

void appendI2cDebugInputChar(unsigned char debugValue);

void appendI2cDebugOutputChar(unsigned char debugValue);

/**
 * Print the content of debug buffers.
 */
void printI2cDebugBuffers();


/**
 * Print the content of an I2cBus.
 * @param outputStream where we print the debug information
 * @param i2cBus the information about the i2c Bus
 */
void printI2cBus(OutputStream* outputStream, I2cBus* i2cBus);

/**
 * Print the content of an I2cBusConnection.
 * @param outputStream where we print the debug information
 * @param i2cBusConnection the information about the i2c Bus Connection
 */
void printI2cBusConnection(OutputStream* outputStream, I2cBusConnection* i2cBusConnection);

/**
 * Returns an I2cBusType into his String representation.
 * @param i2cBusType the type of i2cBus for which we want the String representation
 * @return a string representation of the I2cBusType
 */
const char* getI2cBusTypeAsString(enum I2cBusType i2cBusType);

/**
 * Returns an i2cPort into his String representation.
 * @param i2cPort the type of i2cPort for which we want the String representation
 * @return a string representation of the i2cPort
 */
const char* getI2cPortAsString(enum I2cPort i2cPort);

#endif

