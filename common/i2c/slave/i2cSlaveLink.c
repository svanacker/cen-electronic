#include <stdlib.h>

#include "i2cSlaveLink.h"

#include "i2cSlave.h"
#include "i2cSlaveSetup.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/streamLink.h"

// STREAM LINK INTERFACE

static char* BUFFER_NAME_I2C_SLAVE = "I2C Slave";

void openSlaveI2cStreamLink(StreamLink* i2cStreamLink,
        Buffer* inputBuffer,
		char (*inputBufferArray)[],
		unsigned char inputBufferLength,
        Buffer* outputBuffer,
		char (*outputBufferArray)[],
		unsigned char outputBufferLength,
        int i2cAddress) {
    // Init Buffers : TODO : IS IT NECESSARY ?
    initBuffer(inputBuffer, inputBufferArray, inputBufferLength, BUFFER_NAME_I2C_SLAVE, "IN");
    initBuffer(outputBuffer, outputBufferArray, outputBufferLength, BUFFER_NAME_I2C_SLAVE, "OUT");

    // Init Links
    initStreamLink(i2cStreamLink, "I2C STREAM",
            inputBuffer,
			inputBufferArray,
			inputBufferLength,
            outputBuffer,
			outputBufferArray,
			outputBufferLength,
            NULL);

    // Set the I2C Stream used by interruption routine
    setI2cStreamLink(i2cStreamLink);

    // Init the I2C Slave at the end to avoid problems with
    // variables
    i2cSlaveInitialize(i2cAddress);
}
