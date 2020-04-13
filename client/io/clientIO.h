#ifndef CLIENT_IO_H
#define CLIENT_IO_H

#include <stdbool.h>

#include "../../common/io/pin.h"
#include "../../device/io/ioDeviceInterface.h"

/**
 * Client Stub to read on a remote IO
 * @param pinIndex the index of the pin that we would like to read
 * @param value a pointer to the result value
 * @return true if the remote call was ok, false else !
  */
bool clientIORead(unsigned char pinIndex, bool* value);

/**
 * Client Stub to write on a remote IO
 * @param pinIndex the index of the pin that we would like to write
 * @param value the value that we would like to write
 * @return true if the remote call was ok, false else !
 */
bool clientIOWrite(unsigned char pinIndex, bool value);

#endif
