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
            printDebugBuffer(getOutputStreamLogger(ALWAYS), inputBuffer);
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

/**
 * Special function to handle the "Ping Calls"
 * Ping Calls are broadcast to a specified Dispatcher, and not to a dispatcher which handle only a specific Device.
 * This code is a little bit tricky and should be simplified
 * @return true if a ping was handle or if there is an error that goes to a remove of all inputbuffer chars, false else
 */
bool handlePingSpecialCase(Buffer* inputBuffer,
                            Buffer* outputBuffer,
                            OutputStream* outputStream,
                            filterCharFunction* inputFilterChar,
                            filterCharFunction* outputFilterChar,
                            unsigned char deviceHeader, unsigned char commandHeader) {
    // Ping special case => We need to decide which dispatcher we ping !
    if (DATA_DISPATCHER_DEVICE_HEADER == deviceHeader && commandHeader == COMMAND_PING_DISPATCHER_INDEX) {
        
        int bufferSize = getBufferElementsCount(inputBuffer);

        unsigned char pingMessageLength = DEVICE_AND_COMMAND_HEADER_LENGTH + 2;
        // We need deviceHeader + commandHeader + Dispatcher index
        if (bufferSize < pingMessageLength) {
            return false;
        }
        unsigned char dispatcherIndex0 = bufferGetCharAtIndex(inputBuffer, COMMAND_HEADER_INDEX + 1);
        unsigned char dispatcherIndex1 = bufferGetCharAtIndex(inputBuffer, COMMAND_HEADER_INDEX + 2);

        char b0, b1;
        filterBinaryToValueChar(dispatcherIndex0, &b0);
        filterBinaryToValueChar(dispatcherIndex1, &b1);
        int dispatcherIndex = hex2CharToInt(b0, b1);

        DriverDataDispatcher* dataDispatcher = getDriverDataDispatcherByIndex(dispatcherIndex);
        if (dataDispatcher == NULL) {
            bufferClearLastChars(inputBuffer, pingMessageLength);
            return true;
        }

        // Change from 'jp' to 'SP' to be sure that it will be handled by the remote dispatcher (all boards must define a local system Device Interface)
        bufferWriteCharAtIndex(inputBuffer, DEVICE_HEADER_INDEX, SYSTEM_DEVICE_HEADER);
        bufferWriteCharAtIndex(inputBuffer, COMMAND_HEADER_INDEX, COMMAND_PING);
        transmitDriverData(dataDispatcher->transmitMode,
            dataDispatcher->address,
            inputBuffer,
            outputBuffer,
            // Send Dispatcher Index : 2 chars (input & output)
            DEVICE_AND_COMMAND_HEADER_LENGTH + 2,
            ACK_LENGTH + DEVICE_AND_COMMAND_HEADER_LENGTH + 2
            );

        // Copy the data from bufferOutputStream to the outputStream
        if (outputStream != NULL) {
            copyInputToOutputStream(&(outputBuffer->inputStream), outputStream, outputFilterChar, ACK_LENGTH + DEVICE_AND_COMMAND_HEADER_LENGTH + 2);
        }

        return true;
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

        if (bufferSize < DEVICE_AND_COMMAND_HEADER_LENGTH) {
            return false;
        }

        unsigned char deviceHeader = bufferGetCharAtIndex(inputBuffer, DEVICE_HEADER_INDEX);
        unsigned char commandHeader = bufferGetCharAtIndex(inputBuffer, COMMAND_HEADER_INDEX);

        if (handlePingSpecialCase(inputBuffer, outputBuffer, outputStream, inputFilterChar, outputFilterChar, deviceHeader, commandHeader)) {
            // We return if we handle the ping
            return true;
        }

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

            // remove the first chars corresponding to the device header and command Header
            bufferClearLastChars(inputBuffer, DEVICE_AND_COMMAND_HEADER_LENGTH);

            // Call to the device
            deviceDescriptor->deviceHandleRawData(commandHeader, bufferedInputStream, bufferedOutputStream);

        }// we forward the request through I2C
        else if (device->transmitMode == TRANSMIT_I2C || device->transmitMode == TRANSMIT_UART || device->transmitMode == TRANSMIT_ZIGBEE) {
            // copy Driver buffer through I2C
            transmitDriverData(device->transmitMode,
                    device->address,
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

