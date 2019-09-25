#include <windows.h>

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../serial.h"
#include "../../pc/pipe/pipeServerHelper.h"
#include "../../pc/pipe/pipeClientHelper.h"
#include "../../pc/thread/threadHelper.h"

#define PIPE_SERIAL_INPUT_NAME_1     L"\\\\.\\pipe\\serialInputPipe1"
#define PIPE_SERIAL_OUTPUT_NAME_1    L"\\\\.\\pipe\\serialOutputPipe1"

static HANDLE serialInputPipeHandle1;
static HANDLE serialOutputPipeHandle1;

HANDLE getSerialInputPipeHandle(enum SerialPort serialPort) {
    if (serialPort == SERIAL_PORT_1) {
        return serialInputPipeHandle1;
    }
    return NULL;
}

void openSerial(enum SerialPort serialPort, unsigned long baudRate) {
    if (serialPort == SERIAL_PORT_1) {
        serialInputPipeHandle1 = initClientPipe(PIPE_SERIAL_INPUT_NAME_1);
        serialOutputPipeHandle1 = initServerPipe(PIPE_SERIAL_OUTPUT_NAME_1);
    }   
}

void openSerialAtDefaultSpeed(enum SerialPort serialPort) {
    openSerial(serialPort, 0);
}

void closeSerial(enum SerialPort serialPort) {
    CloseHandle(serialInputPipeHandle1);
    CloseHandle(serialOutputPipeHandle1);
}

void serialPutc(enum SerialPort serialPort, unsigned char c) {
    writeCharToPipe(serialOutputPipeHandle1, c);
}

