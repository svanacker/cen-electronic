#include "fileDevice.h"
#include "fileDeviceInterface.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"
#include "../../drivers/file/eeprom/eepromFile.h"

#include "../../external/fatfs/diskio.h"
#include "../../external/fatfs/ff.h"

void deviceFileInit(void) {

}

void deviceFileShutDown(void) {
}

bool isFileDeviceOk(void) {
    return true;
}

void deviceFileHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
	if (commandHeader == COMMAND_CREATE_FILE_SYSTEM) {
		ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_CREATE_FILE_SYSTEM);
		FATFS fs;
		FIL fil;       /* File object */
		FRESULT res;   /* API result code */
		UINT bw = 0;       /* Bytes written */

		// Register work area (do not care about error)
		res = f_mount(&fs, "", 0);

		// Create FAT volume with default cluster size
		res = f_mkfs("", 0, 0);

		if (res == RES_OK) {

			// Create a file as new
			res = f_open(&fil, "hello.txt", FA_CREATE_NEW | FA_WRITE);
		}
		if (res == RES_OK) {

			// Write a message
			f_write(&fil, "Hello, World!\r\n", 15, &bw);
		}
		
		if (bw != 15) {
			// Close the file
			f_close(&fil);
		}
		f_close(&fil);
		// Unregister work area
		// f_mount(0, "", 0);
	}
	else if (commandHeader == COMMAND_GET_FREE_SPACE) {
		ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_GET_FREE_SPACE);
		FATFS fs;
		FATFS* fsPointer;
		DWORD freeCluster, freeSector, tot_sect;

		fsPointer = &fs;
		f_mount(fsPointer, "", 0);
		

		char str[12];

		/* Get volume label of the default drive */
		f_getlabel("", str, 0);

		appendString(getErrorOutputStreamLogger(), str);
		// Get volume information and free clusters of drive */
		f_getfree("", &freeCluster, &fsPointer);

		/* Get total sectors and free sectors */
		tot_sect = (fs.n_fatent - 2) * fs.csize;
		freeSector = freeCluster * fs.csize;
		appendHex4(outputStream, freeSector);
		// appendHex4(outputStream, 0);

		// f_mount(0, "", 0);
	}
	else if (commandHeader == COMMAND_SHOW_LIST_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_SHOW_LIST_FILE);
		FRESULT fr;
		DIR dj;         /* Directory search object */
		FILINFO fno;    /* File information */
		FRESULT result;

		FATFS fs;
		f_mount(&fs, "", 0);

		// f_opendir(&dj, "");

		fr = f_findfirst(&dj, &fno, "", "*.txt");

		while (fr == FR_OK && fno.fname[0]) {         /* Repeat while an item is found */
			appendString(getErrorOutputStreamLogger(), fno.fname[0]);
			fr = f_findnext(&dj, &fno);               /* Search for next item */
		}
		f_closedir(&dj);

        // TODO
    } else if (commandHeader == COMMAND_SHOW_CONTENT_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_SHOW_CONTENT_FILE);
		FIL file;
		FRESULT result;
		char buffer[512];
        unsigned int fileIndex = readHex2(inputStream);

		FATFS fs;
		f_mount(&fs, "", 0);
		result = f_open(&file, "hello.txt", FA_READ);

		DWORD size = f_size(&file);
		DWORD byteRead;
		result = f_read(&file, &buffer, size, &byteRead);

		appendString(getErrorOutputStreamLogger(), &buffer);

        // TODO
    } else if (commandHeader == COMMAND_CREATE_NEW_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_CREATE_NEW_FILE);
        unsigned int fileIndex = readHex2(inputStream);
        // TODO
    } else if (commandHeader == COMMAND_DELETE_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_DELETE_FILE);
        unsigned int fileIndex = readHex2(inputStream);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceFileInit,
    .deviceShutDown = &deviceFileShutDown,
    .deviceIsOk = &isFileDeviceOk,
    .deviceHandleRawData = &deviceFileHandleRawData,
};

DeviceDescriptor* getFileDeviceDescriptor() {
    return &descriptor;
}