#ifndef I2C_MASTER_INPUT_STREAM_H
#define I2C_MASTER_INPUT_STREAM_H

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"

/**
* Init an inputStream arround i2c with an address.
* @param i2cInputBuffer the buffer to read from i2c slave
* @param inputStream a structure to initialize
* @param the write address for I2C
*/
void initMasterI2cInputStream(Buffer* i2cInputBuffer,
							  InputStream* inputStream,
						 		unsigned char i2cWriteAddress);

#endif
