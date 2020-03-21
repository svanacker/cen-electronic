#include "../serial.h"
#include "../serialInputInterrupt.h"

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "serialPc.h"

#include "../../../common/delay/cenDelay.h"
#include "../../../common/io/buffer.h"
#include "../../../common/io/bufferDebug.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/pc/pipe/pipeClientHelper.h"
#include "../../../common/pc/pipe/pipeServerHelper.h"
#include "../../../common/pc/thread/threadHelper.h"

// forward declaration
DWORD WINAPI serialInputInterruptCallback(LPVOID lpvParam);

static HANDLE serialPipeThreadHandle1;
static DWORD serialPipeThreadId1 = 0;

static Buffer* serialInputBuffer1;

static int consoleInterruptCounter;

void initSerialInputBuffer(Buffer* buffer, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        serialInputBuffer1 = buffer;

        // Create a thread to handle master to slave data
        serialPipeThreadHandle1 = createStandardThread(
                serialInputInterruptCallback, // thread proc
                (LPVOID) serialPortIndex, // thread parameter 
                &serialPipeThreadId1); // returns thread ID 

    }
}

void printSerialInputBuffers(OutputStream* outputStream) {
    appendString(outputStream, "SERIAL INPUT BUFFER 1:");
    appendStringAndDec(outputStream, "\nCounter=", consoleInterruptCounter);
    printDebugBuffer(outputStream, serialInputBuffer1);
}

DWORD WINAPI serialInputInterruptCallback(LPVOID lpvParam) {
    printf("PC->MainBoard -> SerialInputInterruptCallback !\r\n");
    while (true) {
        int serialPortIndex = (int) lpvParam;
        HANDLE serialPipeHandle1 = getSerialInputPipeHandle(serialPortIndex);

        if (serialPipeHandle1 == NULL) {
            continue;
        }

        // Blocking Call
        char c = readCharFromPipe(serialPipeHandle1);

        if (GetLastError() != 0) {
            break;
        }

        if (c == 0) {
            continue;
        }
        delayMicroSecs(1);
        OutputStream* outputStream = getOutputStream(serialInputBuffer1);
        // Fill the internal Buffer
        append(outputStream, c);

    }
    printf("serialInputInterruptCallback exiting.\n");

    return 1;
}