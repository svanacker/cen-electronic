#include "pipeHelper.h"

#include <windows.h>
#include <stdbool.h>


HANDLE initMasterToSlavePipe(LPCWSTR pipeName) {

	printf("Create the Master To Slave Pipe ...\r\n");
	HANDLE result = CreateNamedPipe(pipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE /* | PIPE_NOWAIT */,
		// Only one instance
		2,
		// outBufferSize
		100,
		// inBufferSize
		0,
		// default time out, in milliseconds
		0,
		NULL);
	int lastError = GetLastError();
	if (lastError != 0)
	{
		printf("CreateNamedPipe failed, lastError=%d.\n", GetLastError());
		getchar();
		return result;
	}

	printf("ConnectNamedPipe ...");

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

	// SetNamedPipeHandleState(result, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_NOWAIT, NULL, NULL);

	return result;
}

bool writeCharToPipe(HANDLE pipe, char c) {
	char dataBuffer[1];
	dataBuffer[0] = 1;
	DWORD numBytesWritten = 0;
	WriteFile(pipe, dataBuffer, 1, &numBytesWritten, NULL);

	int error = GetLastError();
	if (error != 0) {
		printf("Error when writeCharToPipe : %d", error);
		return false;
	}

	if (numBytesWritten != 1) {
		printf("Error when writeCharToPipe : numBytesWritten : %d", numBytesWritten);
	}
	return true;
}

HANDLE initSlaveToMasterPipe(LPCWSTR pipeName) {

	// securityAttributes.

	HANDLE result = CreateFile(
		pipeName,		// pipe name 
		GENERIC_READ,	// read,
		0,              // no sharing 
		NULL,           // default security attributes
		OPEN_EXISTING,  // opens existing pipe 
		0,              // default attributes 
		NULL);          // no template file 

	DWORD pipeMode = PIPE_READMODE_BYTE | PIPE_NOWAIT;
	// SetNamedPipeHandleState(result, &pipeMode, NULL, NULL);

	if (GetLastError() != 0)
	{
		printf("Could not open pipe. LastError=%d\n", GetLastError());
		getchar();
		return NULL;
	}
	return result;
}

unsigned char readCharFromPipe(HANDLE pipe) {
	const numberOfByteToRead = 1;
	unsigned char buffer[1];
	DWORD numBytesRead = 0;
	BOOL ok = ReadFile(
		pipe,
		buffer, // the data from the pipe will be put here
		numberOfByteToRead, // number of bytes allocated
		&numBytesRead, // this will store number of bytes actually read
		NULL // not using overlapped IO
		);

	if (ok) {
		printf("Number of bytes read: %d\r\n", numBytesRead);
	}
	else {
		printf("Failed to read data from the pipe.\r\n");
	}
	unsigned char result = buffer[0];

	return result;
}
