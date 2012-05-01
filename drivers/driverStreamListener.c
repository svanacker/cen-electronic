#include <stdlib.h>

#include "driverStreamListener.h"

#include "../common/commons.h"

#include "../common/cmd/commonCommand.h"

#include "../common/error/error.h"

#include "../common/io/filter.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/ioUtils.h"
#include "../common/io/stream.h"

#include "../common/log/logger.h"

#include "../device/dispatcher/deviceDataDispatcher.h"
#include "../drivers/dispatcher/driverDataDispatcher.h"

BOOL handleStreamInstruction(Buffer* inputBuffer,
					        Buffer* outputBuffer,
					        OutputStream* outputStream,
					        filterCharFunction* inputFilterChar,
					        filterCharFunction* outputFilterChar) {

	if (inputBuffer == NULL) {
		writeError(DRIVER_STREAM_LISTENER_INPUT_BUFFER_NULL);
		return FALSE;
	}
	if (outputBuffer == NULL) {
		writeError(DRIVER_STREAM_LISTENER_OUTPUT_BUFFER_NULL);
		return FALSE;
	}

    // We received data
    int inputBufferCount = getBufferElementsCount(inputBuffer);

    if (inputBufferCount > 0) {
        // read the first char (but do not pop from the FIFO)
        unsigned char header = bufferGetFirstChar(inputBuffer);

        if (header == HEADER_CLEAR_INPUT_STREAM || header == INCORRECT_DATA) {
            clearBuffer(inputBuffer);
            return FALSE;
        }

        if (inputFilterChar != NULL) {
            if (!inputFilterChar(header, &header)) {
                // remove the char from the buffer
                bufferReadChar(inputBuffer);
                return FALSE;
            }
        }

        int bufferSize = getBufferElementsCount(inputBuffer);

        // find the device corresponding to this header
        const Device* device = deviceDataDispatcherFindDevice(header, bufferSize, DEVICE_MODE_INPUT);

        // if the device was not found
        if (device == NULL) {
            return FALSE;
        }

        DeviceInterface* deviceInterface = device->interface;

        // We must send header + data => + 1
        int dataToTransferCount = deviceInterface->deviceGetInterface(header, DEVICE_MODE_INPUT, FALSE) + 1;

        // We must receive ack + header + data => + 2
        int dataToReceiveCount = deviceInterface->deviceGetInterface(header, DEVICE_MODE_OUTPUT, FALSE) + 2;

        InputStream* bufferedInputStream = getInputStream(inputBuffer);
        OutputStream* bufferedOutputStream = getOutputStream(outputBuffer);

        // we handle locally the request
        if (device->transmitMode == TRANSMIT_LOCAL) {

            // We need the implementation for local mode
            DeviceDescriptor* deviceDescriptor = device->descriptor;
            if (deviceDescriptor == NULL) {
                writeError(NO_DEVICE_DESC_FOUND_FOR);
                append(getErrorOutputStreamLogger(), header);
                return FALSE;
            }

            // remove the first char corresponding to the header
            bufferReadChar(inputBuffer);

            // Call to the device
            deviceDescriptor->deviceHandleRawData(header, bufferedInputStream, bufferedOutputStream);

        }// we forward the request through I2C
        else if (device->transmitMode == TRANSMIT_I2C) {
            // copy Driver buffer through I2C
            transmitDriverData(device->transmitMode,
                    device->address,
                    inputBuffer,
                    outputBuffer,
                    dataToTransferCount,
                    dataToReceiveCount
                    );
        }
		// we forward the request through ZIGBEE
        else if (device->transmitMode == TRANSMIT_ZIGBEE) {
            // copy Driver buffer through I2C
            transmitDriverData(device->transmitMode,
                    		   device->address,
                      		   inputBuffer,
                    		   outputBuffer,
                    		   dataToTransferCount,
                    		   dataToReceiveCount
                    );
        }
		
        // In Both Cases (Local / I2C)

        // Copy the data from bufferOutputStream to the outputStream
        if (outputStream != NULL) {
            copyInputToOutputStream(&(outputBuffer->inputStream), outputStream, outputFilterChar, dataToReceiveCount);
        }
        return TRUE;
    }
    return FALSE;
}

