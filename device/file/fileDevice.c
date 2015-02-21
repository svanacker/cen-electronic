#include "fileDevice.h"
#include "fileDeviceInterface.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"
#include "../../drivers/file/eeprom/eepromFile.h"

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
		UINT bw;       /* Bytes written */

		// f_mkfs(EEPROM_DRIVE_NUMBER);

		/* Register work area (do not care about error) */
		f_mount(&fs, "", 0);

		/* Create FAT volume with default cluster size */
		res = f_mkfs("", 0, 0);
		if (res) {

			/* Create a file as new */
			res = f_open(&fil, "hello.txt", FA_CREATE_NEW | FA_WRITE);
		}
		if (res) {

			/* Write a message */
			f_write(&fil, "Hello, World!\r\n", 15, &bw);
		}
		if (bw != 15) {
			/* Close the file */
			f_close(&fil);
		}
		/* Unregister work area */
		f_mount(0, "", 0);
	}
	else if (commandHeader == COMMAND_GET_FREE_SPACE) {
		ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_GET_FREE_SPACE);
		// TODO
	}
	else if (commandHeader == COMMAND_SHOW_LIST_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_SHOW_LIST_FILE);
        // TODO
    } else if (commandHeader == COMMAND_SHOW_CONTENT_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_SHOW_CONTENT_FILE);
        unsigned int fileIndex = readHex2(inputStream);
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