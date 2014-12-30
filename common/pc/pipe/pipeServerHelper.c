#include "pipeServerHelper.h"

#include <windows.h>
#include <stdbool.h>

HANDLE initServerPipe(LPCWSTR pipeName) {

    printf("Create the Server Pipe '%ls' ... ", pipeName);
    HANDLE result = CreateNamedPipe(pipeName,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE /* | PIPE_NOWAIT */,
        // Only one instance
        2,
        // outBufferSize
        100,
        // inBufferSize
        100,
        // default time out, in milliseconds
        0,
        NULL);
    int lastError = GetLastError();
    if (lastError != 0)
    {
        printf("KO : lastError=%d.\r\n", GetLastError());
        getchar();
        return result;
    }
    else {
        printf("OK !\r\n");
    }

    printf("ConnectNamedPipe '%ls' ... ", pipeName);

    ConnectNamedPipe(result, NULL);
    if (result == NULL) {
        lastError = GetLastError();

        printf("KO\r\nFailed to make connection on named pipe : errorCode=%d.", lastError);

        // look up error code here using GetLastError()
        CloseHandle(result); // close the pipe
        getchar();
        return NULL;
    }
    printf("OK !\r\n");

    return result;
}

bool writeCharToPipe(HANDLE pipe, char c) {
    char dataBuffer[1];
    dataBuffer[0] = c;
    DWORD numBytesWritten = 0;
    WriteFile(pipe, dataBuffer, 1, &numBytesWritten, NULL);

    int error = GetLastError();
    if (error != 0) {
        printf("writeCharToPipe->Error when writeCharToPipe : %d\r\n", error);
        return false;
    }

    if (numBytesWritten != 1) {
        printf("writeCharToPipe->Error when writeCharToPipe : numBytesWritten : %d\r\n", numBytesWritten);
    }
    return true;
}
