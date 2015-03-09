#include <stdlib.h>
#include <stdbool.h>

#include "driverStreamListener.h"

#include "../common/cmd/commonCommand.h"

#include "../common/error/error.h"

#include "../common/io/buffer.h"
#include "../common/io/filter.h"
#include "../common/io/inputStream.h"
#include "../common/io/ioUtils.h"
#include "../common/io/printWriter.h"
#include "../common/io/reader.h"
#include "../common/io/outputStream.h"

#include "../common/math/hexUtils.h"

#include "../common/log/logger.h"

#include "../device/transmitMode.h"
#include "../device/deviceConstants.h"
#include "../device/system/systemDeviceInterface.h"
#include "../device/dispatcher/deviceDataDispatcher.h"
#include "../drivers/dispatcher/driverDataDispatcher.h"
#include "../drivers/dispatcher/driverDataDispatcherList.h"

/**
* @private
* Try to clear the buffer if it contains some 'z' char. Very usefull when we have made a mistake taping an instruction.
* @return true if it was cleared (=> buffer will be cleared), false else
*/
bool clearBufferIfNeeded(Buffer* inputBuffer) {
    
    int i;
    int inputBufferCount = getBufferElementsCount(inputBuffer);
    for (i = 0; i < inputBufferCount; i++) {
        char bufferElement = bufferGetCharAtIndex(inputBuffer, i);
        if (bufferElement == HEADER_CLEAR_INPUT_STREAM) {
            deepClearBuffer(inputBuffer);
            return true;
        }
        // remove all informations to the latest char
        if (bufferElement == HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER) {
            printDebugBuffer(getAlwaysOutputStreamLogger(), inputBuffer);
            deepClearBuffer(inputBuffer);
            return true;
        }
    }
    return false;
}

/**
* @private
* Try to verify if the char is a filtered char or not
* @return true if it was filtered (=> buffer first char will be removed), false else
*/
bool filterFirstNextChar(Buffer* inputBuffer,  filterCharFunction* inputFilterChar) {
    // read the first char (but do not pop from the FIFO)
    char deviceHeader = bufferGetCharAtIndex(inputBuffer, DEVICE_HEADER_INDEX);

    if (inputFilterChar != NULL) {
        if (!inputFilterChar(deviceHeader, &deviceHeader)) {
            // remove the char from the buffer
            bufferReadChar(inputBuffer);
            return true;
        }
    }
    return false;
}

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

    // Try to clear the buffer if needed ('z' char)
    if (clearBufferIfNeeded(inputBuffer)) {
        return false;
    }

    // We received data
    int inputBufferCount = getBufferElementsCount(inputBuffer);

    if (inputBufferCount > 0) {

        if (filterFirstNextChar(inputBuffer, inputFilterChar)) {
            return false;
        }

        // As there is clear of char filtering, we must reload the size of the buffer
        int bufferSize = getBufferElementsCount(inputBuffer);

		if (bufferSize < DEVICE_HEADER_LENGTH) {
			return false;
		}

		// Get the header
        unsigned char deviceHeader = bufferGetCharAtIndex(inputBuffer, DEVICE_HEADER_INDEX);

		// Manage the dispatcher specifier (3 chars : Ex j01 before real command ...)
		unsigned char specifyDispatcherLength = 0;
		if (deviceHeader == DATA_DISPATCHER_DEVICE_HEADER) {
			specifyDispatcherLength += DISPATCHER_COMMAND_AND_INDEX_HEADER_LENGTH;
		}

		// Check if enough data
		if (bufferSize < specifyDispatcherLength + DEVICE_AND_COMMAND_HEADER_LENGTH) {
			return false;
		}

		// Reload the deviceHeader to take the dispatcher specifier if any
		deviceHeader = bufferGetCharAtIndex(inputBuffer, specifyDispatcherLength + DEVICE_HEADER_INDEX);
		unsigned char commandHeader = bufferGetCharAtIndex(inputBuffer, specifyDispatcherLength + COMMAND_HEADER_INDEX);

        // find the device corresponding to this header. It must at least be declared in local or in remote !
		unsigned char dataSize = bufferSize - specifyDispatcherLength;
		const Device* device = deviceDataDispatcherFindDevice(deviceHeader, commandHeader, dataSize, DEVICE_MODE_INPUT);

        // if the device was not found
        if (device == NULL) {
            return false;
        }

        // At this moment, device Interface is found
        DeviceInterface* deviceInterface = device->deviceInterface;

        // We must send device specifyDispatcherLength + Header + commandHeader + data => + 2
		int dataToTransferCount = deviceInterface->deviceGetInterface(commandHeader, DEVICE_MODE_INPUT, false) + specifyDispatcherLength + DEVICE_AND_COMMAND_HEADER_LENGTH;

        if (bufferSize < dataToTransferCount) {
            return false;
        }

        // We must receive ack + device header + command header + data => + 3
        int dataToReceiveCount = deviceInterface->deviceGetInterface(commandHeader, DEVICE_MODE_OUTPUT, false) + ACK_LENGTH + DEVICE_AND_COMMAND_HEADER_LENGTH;

        InputStream* bufferedInputStream = getInputStream(inputBuffer);
        OutputStream* bufferedOutputStream = getOutputStream(outputBuffer);

		TransmitMode transmitMode = device->transmitMode;

        // we handle locally the request
		if (specifyDispatcherLength == 0 && transmitMode == TRANSMIT_LOCAL) {

            // We need the implementation for local mode
            DeviceDescriptor* deviceDescriptor = device->descriptor;
            if (deviceDescriptor == NULL) {
                writeError(NO_DEVICE_DESC_FOUND_FOR);
                append(getErrorOutputStreamLogger(), deviceHeader);
                append(getErrorOutputStreamLogger(), commandHeader);
                return false;
            }

            // remove the first chars corresponding to the device header and command Header
            bufferClearLastChars(inputBuffer, DEVICE_AND_COMMAND_HEADER_LENGTH);

            // Call to the device
            deviceDescriptor->deviceHandleRawData(commandHeader, bufferedInputStream, bufferedOutputStream);

        } // we forward the request through Remote Operation with Dispatcher
		else if (specifyDispatcherLength > 0 || transmitMode == TRANSMIT_I2C || transmitMode == TRANSMIT_UART || transmitMode == TRANSMIT_ZIGBEE) {

			// Find dispatcher
			DriverDataDispatcher* dispatcher = NULL;

			if (specifyDispatcherLength > 0) {
				bufferClearLastChars(inputBuffer, DEVICE_HEADER_LENGTH);
				unsigned char dispatcherIndex = readHex2(bufferedInputStream);

				dispatcher = getDriverDataDispatcherByIndex(dispatcherIndex);
				if (dispatcher == NULL) {
					writeError(NO_DISPATCHER_FOUND);
					OutputStream* errorOutputStream = getErrorOutputStreamLogger();
					appendStringAndDec(errorOutputStream, ", dispatcherIndex=", dispatcherIndex);
				}
			}
			else {
				TransmitMode transmitMode = device->transmitMode;
				int address = device->address;

				dispatcher = getDriverDataDispatcherByTransmitMode(transmitMode, address);
				
				if (dispatcher == NULL) {
					writeError(NO_DISPATCHER_FOUND);
					OutputStream* errorOutputStream = getErrorOutputStreamLogger();
					appendStringAndDec(errorOutputStream, ", transmitMode=", transmitMode);
					append(errorOutputStream, '(');
					appendString(errorOutputStream, getTransmitModeAsString(transmitMode));
					append(errorOutputStream, ')');
					appendStringAndDec(errorOutputStream, ", addr=", address);
				}
			}

            // copy Driver buffer with remote Call
			dispatcher->driverDataDispatcherTransmitData(dispatcher,
					inputBuffer,
                    outputBuffer,
                    dataToTransferCount,
                    dataToReceiveCount
                    );
        }
        
        // In All Cases (Local / I2C / UART / Zigbee ...)

        // Copy the data from bufferOutputStream to the outputStream
        if (outputStream != NULL) {
            copyInputToOutputStream(&(outputBuffer->inputStream), outputStream, outputFilterChar, dataToReceiveCount);
        }
        return true;
    }
    return false;
}

