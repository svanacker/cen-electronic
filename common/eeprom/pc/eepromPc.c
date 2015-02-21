#include "eepromPc.h"
#include "../eeprom.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "../../../common/error/error.h"
#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#define EEPROM_PC_MAX_INDEX        0xFFFF

static char eepromPc[EEPROM_PC_MAX_INDEX + 1];

void eepromPcWriteChar(Eeprom* eeprom_, unsigned long index, char value) {
    if (index > EEPROM_PC_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
    }
    eepromPc[index] = value;
}

char eepromPcReadChar(Eeprom* eeprom_, unsigned long index) {
    if (index > EEPROM_PC_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return 0;
    }
    char result = eepromPc[index];
    return result;
}

void eepromPcReadBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    unsigned long i;
    for (i = index; i < index + length; i++) {
        char value = eepromPcReadChar(eeprom_, i);
		append(getOutputStream(buffer), value);
    }
}

void eepromPcWriteBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    unsigned long i;
    for (i = index; i < index + length; i++) {
		InputStream* inputStream = getInputStream(buffer);
		char value = readBinaryChar(inputStream);
		eepromPcWriteChar(eeprom_, i, value);
    }
}

void initEepromPc(Eeprom* eepromPc) {
    initEeprom(eepromPc, EEPROM_PC_MAX_INDEX, eepromPcWriteChar, eepromPcReadChar, eepromPcReadBlock, eepromPcWriteBlock, NULL);
}

/**
* Dump the content of the eeprom_ into a file (always the same).
* Only available on PC.
*/
void dumpEeprom(Eeprom* eeprom_) {
	HANDLE handleFile;

	long maxIndex = eeprom_->maxIndex;

	char* dataBuffer = malloc(maxIndex);
	char* currentDataBuffer = dataBuffer;
	for (int i = 0; i < maxIndex; i++) {
		char value = eeprom_->eepromReadChar(eeprom_, i);
		*currentDataBuffer = value;
		currentDataBuffer++;
	}

	// char* DataBuffer = "This is some test data to write to the file.";
	DWORD dwBytesToWrite = (DWORD)maxIndex;
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	handleFile = CreateFile(TEXT("c:/PERSO/eeprom.hex"),                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		TRUNCATE_EXISTING,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if ((handleFile == NULL) && (GetLastError() == ERROR_FILE_NOT_FOUND))
	{
		handleFile = CreateFile(TEXT("c:/PERSO/eeprom.hex"), GENERIC_WRITE, 0, NULL, CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL, NULL);
	}

	if (handleFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("Terminal failure: Unable to open file for write.\n"));
		return;
	}

	_tprintf(TEXT("Writing %d bytes to File.\n"), dwBytesToWrite);

	bErrorFlag = WriteFile(
		handleFile,           // open file handle
		dataBuffer,      // start of data to write
		dwBytesToWrite,  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL);            // no overlapped structure

	if (FALSE == bErrorFlag)
	{
		printf("Terminal failure: Unable to write to file.\n");
	}
	else
	{
		if (dwBytesWritten != dwBytesToWrite)
		{
			// This is an error because a synchronous write that results in
			// success (WriteFile returns TRUE) should write all data as
			// requested. This would not necessarily be the case for
			// asynchronous writes.
			printf("Error: dwBytesWritten != dwBytesToWrite\n");
		}
		else
		{
			_tprintf(TEXT("Wrote %d bytes to file successfully.\n"), dwBytesWritten);
		}
	}

	CloseHandle(handleFile);
}