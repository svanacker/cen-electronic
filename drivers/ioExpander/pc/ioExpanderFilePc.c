#include "ioExpanderFilePc.h"

#include "../../../common/pc/file/fileUtils.h"

#include <stdbool.h>

bool ioExpanderFilePcInit(IOExpander* ioExpander) {
    return true;
}

// ALL BITS

unsigned char ioExpanderFilePcReadValue(IOExpander* ioExpander) {
    char* fileName = (char*) ioExpander->object;
    char data[IO_EXPANDER_FILE_BIT_COUNT];
    readOrWriteDataFromFile(fileName, true, '0', (char*) &data, IO_EXPANDER_FILE_BIT_COUNT, true);
    unsigned int i;
    unsigned char result = 0;
    for (i = 0; i < IO_EXPANDER_FILE_BIT_COUNT; i++) {
        if (data[IO_EXPANDER_FILE_BIT_COUNT - 1 - i] == '1') {
            result += (1 << i);
        }
    }
    return result;
}

void ioExpanderFilePcWriteValue(IOExpander* ioExpander, unsigned char value) {
    char* fileName = (char*)ioExpander->object;
    char data[IO_EXPANDER_FILE_BIT_COUNT];
    unsigned int i;
    for (i = 0; i < IO_EXPANDER_FILE_BIT_COUNT; i++) {
        if (value & (1 << i)) {
            data[i] = '1';
        }
        else {
            data[i] = '0';
        }
    }

    readOrWriteDataFromFile(fileName, false, '0', (char*) &data, IO_EXPANDER_FILE_BIT_COUNT, true);
}

// SINGLE BIT

bool ioExpanderFilePcReadSingleValue(IOExpander* ioExpander, unsigned int ioIndex) {
    char* fileName = (char*)ioExpander->object;
    char data[IO_EXPANDER_FILE_BIT_COUNT];
    readOrWriteDataFromFile(fileName, true, '0', (char*) &data, IO_EXPANDER_FILE_BIT_COUNT, true);

    return (data[IO_EXPANDER_FILE_BIT_COUNT - 1 - ioIndex] == '1');
}

void ioExpanderFilePcWriteSingleValue(IOExpander* ioExpander, unsigned int ioIndex, bool value) {
    char* fileName = (char*)ioExpander->object;
    char data[IO_EXPANDER_FILE_BIT_COUNT];
    // Load the whole file
    readOrWriteDataFromFile(fileName, true, '0', (char*) &data, IO_EXPANDER_FILE_BIT_COUNT, true);

    // Change a single value
    if (value) {
        data[IO_EXPANDER_FILE_BIT_COUNT - 1 - ioIndex] = '1';
    }
    else {
        data[IO_EXPANDER_FILE_BIT_COUNT - 1 - ioIndex] = '0';
    }
    // Write the whole file
    readOrWriteDataFromFile(fileName, false, '0', (char*) &data, IO_EXPANDER_FILE_BIT_COUNT, true);
}

void initIOExpanderFilePc(IOExpander* ioExpander, const char* fileName) {
    initIOExpander(ioExpander,
            &ioExpanderFilePcInit,
            &ioExpanderFilePcReadValue,
            &ioExpanderFilePcWriteValue,
            &ioExpanderFilePcReadSingleValue,
            &ioExpanderFilePcWriteSingleValue,
            IO_EXPANDER_FILE_BIT_COUNT,
            (int*) fileName);
}
