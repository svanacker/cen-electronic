#include <stdlib.h>

#include "driverStreamListener.h"

#include "../common/cmd/commonCommand.h"

#include "../common/error/error.h"

#include "../common/io/buffer.h"
#include "../common/io/filter.h"
#include "../common/io/inputStream.h"
#include "../common/io/ioUtils.h"
#include "../common/io/printWriter.h"
#include "../common/io/outputStream.h"
#include "../common/io/stream.h"

#include "../common/log/logger.h"

#include "../device/dispatcher/deviceDataDispatcher.h"
#include "../drivers/dispatcher/driverDataDispatcher.h"

bool handleStreamInstruction(Buffer* inputBuffer,
                            Buffer* outputBuffer,
                            OutputStream* outputStream,
                            filterCharFunction* inputFilterChar,
                            filterCharFunction* outputFilterChar) {

    if (inputBuffer == NULL) {
        writeError(DRIVER_STREAM_LISTENER_INPUT_BUFFER_NULL);
        return false;
    }
    if (outputBuffer == NULL) {
        writeError(DRIVER_STREAM_LISTENER_OUTPUT_BUFFER_NULL);
        return false;
    }

    // We received data
    int inputBufferCount = getBufferElementsCount(inputBuffer);

    // Try to clear the buffer if needed
    int i;
    for (i = 0; i < inputBufferCount; i++) {
        char bufferElement = bufferGetCharAtIndex(inputBuffer, i);
        if (bufferElement == HEADER_CLEAR_INPUT_STREAM) {
            deepClearBuffer(inputBuffer);
            return false;
        }
        // remove all informations to the latest char
        if (bufferElement == HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER) {
            printDebugBuffer(getOutputStreamLogger(ALWAYS), inputBuffer);
            deepClearBuffer(inputBuffer);
            return false;
        }
    }

    if (inputBufferCount > 0) {
        // read the first char (but do not pop from the FIFO)
        char deviceHeader = bufferGetCharAtIndex(inputBuffer, DEVICE_HEADER_INDEX);

        if (inputFilterChar != NULL) {
            if (!inputFilterChar(deviceHeader, &deviceHeader)) {
                // remove the char from the buffer
                bufferReadChar(inputBuffer);
                return false;
            }
        }

        // As there is clear of char filtering, we must reload the size of the buffer
        int bufferSize = getBufferElementsCount(inputBuffer);

        if (bufferSize < DEVICE_AND_COMMAND_HEADER_LENGTH) {
            return false;
        }

        deviceHeader = bufferGetCharAtIndex(inputBuffer, DEVICE_HEADER_INDEX);
        char commandHeader = bufferGetCharAtIndex(inputBuffer, COMMAND_HEADER_INDEX);

        // find the device corresponding to this header
        const Device* device = deviceDataDispatcherFindDevice(deviceHeader, commandHeader, bufferSize, DEVICE_MODE_INPUT);

        // if the device was not found
        if (device == NULL) {
            return false;
        }

        // At this moment, device Interface is found
        DeviceInterface* deviceInterface = device->deviceInterface;

        // We must send device Header + commandHeader + data => + 2
        int dataToTransferCount = deviceInterface->deviceGetInterface(commandHeader, DEVICE_MODE_INPUT, false) + DEVICE_AND_COMMAND_HEADER_LENGTH;

        if (bufferSize < dataToTransferCount) {
            return false;
        }

        // We must receive ack + device header + command header + data => + 3
        int dataToReceiveCount = deviceInterface->deviceGetInterface(commandHeader, DEVICE_MODE_OUTPUT, false) + ACK_LENGTH + DEVICE_AND_COMMAND_HEADER_LENGTH;

        InputStream* bufferedInputStream = getInputStream(inputBuffer);
        OutputStream* bufferedOutputStream = getOutputStream(outputBuffer);

        // we handle locally the request
        if (device->transmitMode == TRANSMIT_LOCAL) {

            // We need the implementation for local mode
            DeviceDescriptor* deviceDescriptor = device->descriptor;
            if (deviceDescriptor == NULL) {
                writeError(NO_DEVICE_DESC_FOUND_FOR);
                append(getErrorOutputStreamLogger(), deviceHeader);
                append(getErrorOutputStreamLogger(), commandHeader);
                return false;
            }

            // remove the first char corresponding to the device header
            bufferReadChar(inputBuffer);

            // remove the second char corresponding to the command header
            bufferReadChar(inputBuffer);

            // Call to the device
            deviceDescriptor->deviceHandleRawData(commandHeader, bufferedInputStream, bufferedOutputStream);

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
        return true;
    }
    return false;
}

