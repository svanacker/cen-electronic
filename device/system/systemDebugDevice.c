#include "systemDebugDevice.h"
#include "systemDebugDeviceInterface.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/loggerDebug.h"

#include "../../common/serial/serialInputInterrupt.h"

#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"
#include "../../device/deviceUsage.h"

#include <windows.h>
#include <stdio.h>

void deviceSystemDebugInit(void) {
}

void deviceSystemDebugShutDown(void) {
}

bool deviceSystemDebugIsOk(void) {
    return true;
}

void deviceSystemDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_WRITE_LOG_LEVEL) {
        int logHandlerIndex = readHex2(inputStream);
        int logLevel = readHex2(inputStream);

        LogHandler* logHandler = getLogHandler(getLoggerInstance()->logHandlerList, logHandlerIndex);
        logHandler->logLevel = logLevel;

        // data
        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_WRITE_LOG_LEVEL);
        // we don't use driver stream (buffered->too small), instead of log (not buffered)
        printLogger(getOutputStreamLogger(ALWAYS));
    }
    // Dispatcher List
    else if (header == COMMAND_DISPATCHER_LIST) {

        HANDLE motorBoardPipe = CreateFile(
            L"\\\\.\\pipe\\mainBoardPipe",		// pipe name 
            GENERIC_READ |  // read and write access 
            GENERIC_WRITE,
            0,              // no sharing 
            NULL,           // default security attributes
            OPEN_EXISTING,  // opens existing pipe 
            0,              // default attributes 
            NULL);          // no template file 

        if (GetLastError() != 0)
        {
            printf("Could not open pipe. LastError=%d\n", GetLastError());
            getchar();
            return;
        }

        wchar_t buffer[128];
        DWORD numBytesRead = 0;
        BOOL result = ReadFile(
            motorBoardPipe,
            buffer, // the data from the pipe will be put here
            127 * sizeof(wchar_t), // number of bytes allocated
            &numBytesRead, // this will store number of bytes actually read
            NULL // not using overlapped IO
            );

        if (result) {
            printf("Number of bytes read: %d", numBytesRead);
        }
        else {
            printf("Failed to read data from the pipe.");
        }


        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_DISPATCHER_LIST);
        DriverDataDispatcherList* dispatcherList = getDispatcherList();
        printDriverDataDispatcherList(getOutputStreamLogger(ALWAYS), dispatcherList);         
    }
    // Serial Input Buffers
    else if (header == COMMAND_SERIAL_INPUT_BUFFERS) {
        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_INPUT_BUFFERS);
        printSerialInputBuffers(getOutputStreamLogger(ALWAYS));         
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSystemDebugInit,
    .deviceShutDown = &deviceSystemDebugShutDown,
    .deviceIsOk = &deviceSystemDebugIsOk,
    .deviceHandleRawData = &deviceSystemDebugHandleRawData,
};

DeviceDescriptor* getSystemDebugDeviceDescriptor(void) {
    return &descriptor;
}
