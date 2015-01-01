#ifndef DRIVER_STREAM_LISTENER_H
#define DRIVER_STREAM_LISTENER_H

#include <stdbool.h>

#include "../common/commons.h"
#include "../common/io/buffer.h"
#include "../common/io/filter.h"
#include "../common/io/outputStream.h"

/**
 * Listen if there is any commands on the inputStream.
 * and returns true if it handled something
 * @param inputBuffer the buffer containing data
 * @param outputBuffer the result from the devices
 * @param outputStream the outputStream in which we will write (can be NULL)
 * @param inputFilterChar the function for filtering (can be NULL)
 * @param outputFilterChar the function for filtering the output (can be NULL)
 * @return true if there is an instruction which was handled
 */
bool handleStreamInstruction(Buffer* inputBuffer,
        Buffer* outputBuffer,
        OutputStream* outputStream,
        filterCharFunction* inputFilterChar,
        filterCharFunction* outputFilterChar
        );

#endif
