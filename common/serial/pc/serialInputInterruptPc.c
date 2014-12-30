#include "../serial.h"
#include "../serialInputInterrupt.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

static Buffer* consoleInputBuffer;

static int consoleInterruptCounter;

void initSerialInputBuffer(Buffer* buffer, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        consoleInputBuffer = buffer;
    }
}

void printSerialInputBuffers(OutputStream* outputStream) {
    appendString(outputStream, "CONSOLE INPUT BUFFER 1:");
    appendStringAndDec(outputStream, "\nCounter=", consoleInterruptCounter);
    printDebugBuffer(outputStream, consoleInputBuffer);
}
