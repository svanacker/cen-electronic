#include "eepromPc.h"
#include "../eeprom.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "../../../common/error/error.h"
#include "../../../common/io/buffer.h"
#include "../../../common/io/printWriter.h"

#define EEPROM_PC_MAX_INDEX        0xFFFF

static signed int eepromPc[EEPROM_PC_MAX_INDEX + 1];

void eepromPcWriteInt(Eeprom* eeprom_, unsigned long index, signed int value) {
    if (index > EEPROM_PC_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
    }
    eepromPc[index] = value;
}

signed int eepromReadInt(Eeprom* eeprom_, unsigned long index) {
    if (index > EEPROM_PC_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return 0;
    }
    signed int result = eepromPc[index];
    return result;
}

void eepromReadBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    unsigned long i;
    for (i = index; i < index + length; i++) {
        signed int value = eepromReadInt(eeprom_, i);
        // TODO
        writeError(UNIMPLETEMENTED_EXCEPTION);
    }
}

void eepromWriteBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    unsigned long i;
    for (i = index; i < index + length; i++) {
        signed int value = eepromReadInt(eeprom_, i);
        // TODO
        writeError(UNIMPLETEMENTED_EXCEPTION);
    }

}

void initEepromPc(Eeprom* eepromPc) {
    initEeprom(eepromPc, EEPROM_PC_MAX_INDEX, eepromPcWriteInt, eepromReadInt, eepromReadBlock, eepromWriteBlock, NULL);
}

/**
* Dump the content of the eeprom_ into a file (always the same).
* Only available on PC.
*/
void dumpEeprom(Eeprom* eeprom_) {
	HANDLE handleFile;
	char DataBuffer[] = "This is some test data to write to the file.";
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	handleFile = CreateFile(TEXT("c:/PERSO/test.txt"),                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if (handleFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("Terminal failure: Unable to open file for write.\n"));
		return;
	}

	_tprintf(TEXT("Writing %d bytes to File.\n"), dwBytesToWrite);

	bErrorFlag = WriteFile(
		handleFile,           // open file handle
		DataBuffer,      // start of data to write
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