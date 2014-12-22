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
		100,
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

	return result;
}

bool writeCharToPipe(HANDLE pipe, char c) {
	char dataBuffer[1];
	dataBuffer[0] = c;
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

	if (GetLastError() != 0)
	{
		printf("Could not open pipe. LastError=%d\n", GetLastError());
		getchar();
		return NULL;
	}
	return result;
}

unsigned char readCharFromPipe(HANDLE pipe) {
	#define NUMBER_OF_BYTES_TO_READ 1
	unsigned char buffer[NUMBER_OF_BYTES_TO_READ + 1];
	buffer[0] = '\0';
	DWORD numBytesRead = 0;
	BOOL ok = ReadFile(
		pipe,
		buffer, // the data from the pipe will be put here
		NUMBER_OF_BYTES_TO_READ, // number of bytes allocated
		&numBytesRead, // this will store number of bytes actually read
		NULL // not using overlapped IO
		);
	int lastError = GetLastError();

	if (lastError != 0) {
		printf("lastError: %d\r\n", lastError);
	}

	unsigned char result = buffer[0];
	if (!ok) {
		printf("Failed to read data from the pipe.\r\n");
	}
	else {
		// printf("Content of bytes read: %d\r\n", result);
	}

	return result;
}
