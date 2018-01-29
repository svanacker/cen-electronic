#include "eepromPc.h"
#include "../eeprom.h"

#include <windows.h>
#include <stdbool.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "../../../common/error/error.h"
#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/system/system.h"

// #define EEPROM_PC_MAX_INDEX        0x03FFFF

// 4 Ko of Eeprom for the PC must be enough for lots of things
#define EEPROM_PC_MAX_INDEX        0x001000

/** TODO : STATIC must be removed. */
static char eepromPc[EEPROM_PC_MAX_INDEX];

/**
* Creates or Open the File when initializing.
*/
FILE* eepromPCGetOrCreateFile(Eeprom* eeprom_, bool load) {
    char fileName[255];
    // TODO ! Change the Path !
    char* directory = "c:/PERSO/";
    char* boardName = getBoardName();
    char* extension = ".hex";
    strcpy(fileName, directory);
    strcat(fileName, boardName);
    strcat(fileName, extension);

    FILE* file = fopen(fileName, "rb+");
    // if file does not exist, create it
    if (file == NULL)
    {
        file = fopen(fileName, "wb");
        // Fill data
        fwrite(&eepromPc, 1, EEPROM_PC_MAX_INDEX, file);
    }
    // we read it !
    else {
        if (load) {
            fread(&eepromPc, 1, EEPROM_PC_MAX_INDEX, file);
        }
    }
    return file;
}

void eepromPcWriteCharIntoFile(Eeprom* eeprom_, unsigned long index, unsigned char value) {
    // Store it in the file too !
    FILE* file = eepromPCGetOrCreateFile(eeprom_, false);
    fseek(file, index, 0);
    char valueToWrite[1];
    valueToWrite[0] = value;
    fwrite(valueToWrite, 1, 1, file);
    fclose(file);
}

void eepromPcWriteChar(Eeprom* eeprom_, unsigned long index, unsigned char value) {
    if (index >= EEPROM_PC_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return;
    }
    eepromPc[index] = value;
    eepromPcWriteCharIntoFile(eeprom_, index, value);
}

char eepromPcReadChar(Eeprom* eeprom_, unsigned long index) {
    if (index >= EEPROM_PC_MAX_INDEX) {
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

/**
* Reload the content (usefull for Windows).
*/
void eepromPcReload(Eeprom* eeprom_) {
    FILE* file = eepromPCGetOrCreateFile(eeprom_, true);
    fclose(file);
}

/**
* Dump the content of the eeprom_ into a file (always the same).
* Only available on PC.
*/
void eepromPcDump(Eeprom* eeprom_) {
    for (int i = 0; i < EEPROM_PC_MAX_INDEX; i++) {
        eepromPcWriteCharIntoFile(eeprom_, i, eepromPc[i]);
    }
}

void initEepromPc(Eeprom* eepromPc, char* fileName) {
    initEeprom(eepromPc,
        EEPROM_PC_MAX_INDEX,
        eepromPcWriteChar,
        eepromPcReadChar,
        eepromPcReadBlock,
        eepromPcWriteBlock,
        eepromPcReload,
        eepromPcDump,
        fileName);
    eepromPcReload(eepromPc);
}