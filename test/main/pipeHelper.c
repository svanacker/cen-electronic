#include "pipeHelper.h"

#include <windows.h>
#include <stdbool.h>


HANDLE initMasterToSlavePipe(LPCWSTR pipeName) {

	printf("Create the Master To Slave Pipe ...\r\n");
	HANDLE result = CreateNamedPipe(pipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
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
	return result;
}

bool writeCharToPipe(HANDLE pipe, char c) {
	wchar_t* data = L"?";
	DWORD numBytesWritten = 0;
	WriteFile(pipe, data, wcslen(data) * sizeof(wchar_t), &numBytesWritten, NULL);

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