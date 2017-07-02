#include <stdlib.h>
#include <stdbool.h>

#include "eeprom.h"

#include "../../common/error/error.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/buffer.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/io/outputStream.h"

#define EEPROM_ADDRESS_LENGTH				7
#define EEPROM_BLOCK_4_VALUE_LENGTH			24
#define EEPROM_BLOCK_COUNT			        8

void initEeprom(Eeprom* eeprom_,
                long maxIndex,
                EepromWriteCharFunction* eepromWriteChar,
                EepromReadCharFunction* eepromReadChar,
                EepromWriteBlockFunction* eepromWriteBlock,
                EepromReadBlockFunction* eepromReadBlock,
                EepromLoadFunction* eepromLoadFunction,
                EepromDumpFunction* eepromDumpFunction,
                void* object) {
    if (eeprom_ == NULL) {
        writeError(EEPROM_NULL);
        return;
    }            
    eeprom_->maxIndex = maxIndex;
    eeprom_->eepromWriteChar = eepromWriteChar;
    eeprom_->eepromReadChar = eepromReadChar;
    eeprom_->eepromWriteBlock = eepromWriteBlock;
    eeprom_->eepromReadBlock = eepromReadBlock;
    eeprom_->eepromLoad = eepromLoadFunction;
    eeprom_->eepromDump = eepromDumpFunction;
    eeprom_->object = object;
}

unsigned int eepromReadInt(Eeprom* eeprom_, unsigned int index) {
    // We use Big Endian format !
    /*
    appendString(getDebugOutputStreamLogger(), "index=");
    appendDec(getDebugOutputStreamLogger(), index);
    appendCRLF(getDebugOutputStreamLogger());
    */
    unsigned int msb = eeprom_->eepromReadChar(eeprom_, index);
    /*
    appendString(getDebugOutputStreamLogger(), "msb=");
    appendDec(getDebugOutputStreamLogger(), msb);
    appendCRLF(getDebugOutputStreamLogger());
    */
    unsigned int lsb = eeprom_->eepromReadChar(eeprom_, index + 1);
    /*
    appendString(getDebugOutputStreamLogger(), "lsb=");
    appendDec(getDebugOutputStreamLogger(), lsb);
    appendCRLF(getDebugOutputStreamLogger());
    */
    unsigned int result = (msb << 8) + lsb;

    return result;
}

unsigned eepromReadLong(Eeprom* eeprom_, unsigned long index) {
    // We use Big Endian format !
    unsigned long b0 = eeprom_->eepromReadChar(eeprom_, index);
    unsigned long b1 = eeprom_->eepromReadChar(eeprom_, index + 1);
    unsigned long b2 = eeprom_->eepromReadChar(eeprom_, index + 2);
    unsigned long b3 = eeprom_->eepromReadChar(eeprom_, index + 3);
    unsigned long result = (b0 << 24) + (b1 << 16) + (b2 << 8) + b3;

    return result;
}



void eepromWriteInt(Eeprom* eeprom_, unsigned long index, unsigned int value) {
    /*
    appendString(getDebugOutputStreamLogger(), "writeInt=");
    appendHex4(getDebugOutputStreamLogger(), index);
    appendCRLF(getDebugOutputStreamLogger());
    */
    // We use Big Endian format !
    eeprom_->eepromWriteChar(eeprom_, index, value >> 8);
    eeprom_->eepromWriteChar(eeprom_, index + 1, value & 0xFF);
}

void eepromWriteLong(Eeprom* eeprom_, unsigned long index, unsigned long value) {
    // We use Big Endian format !
    eeprom_->eepromWriteChar(eeprom_, index, (value >> 24) & 0xFF);
    eeprom_->eepromWriteChar(eeprom_, index + 1, (value >> 16) & 0xFF);
    eeprom_->eepromWriteChar(eeprom_, index + 2, (value >> 8) & 0xFF);
    eeprom_->eepromWriteChar(eeprom_, index + 3, value & 0xFF);
}

long getMaxIndex(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(EEPROM_NULL);
        return -1;
    }
    long result = eeprom_->maxIndex;
    return result;
}

bool isEepromInitialized(Eeprom* eeprom_) {
    if (eeprom_->eepromWriteChar == NULL || eeprom_->eepromReadChar == NULL) {
        return false;
    }
    return true;
}

void printEepromBlock(Eeprom* eeprom_, OutputStream* outputStream, long index, unsigned int length, Buffer* buffer) {
    eeprom_->eepromReadBlock(eeprom_, index, length, buffer);
    unsigned long i;
    for (i = 0; i < length; i++) {
        char c = bufferReadChar(buffer);
        appendHex2(outputStream, c);
    }
}

void clearEeprom(Eeprom* eeprom_, unsigned long startIndex, unsigned long endIndex) {
    unsigned long i;
    for (i = startIndex; i < endIndex; i++) {
        eeprom_->eepromWriteChar(eeprom_, i, '\0');
    }
}

void dumpEepromToOutputStream(Eeprom* eeprom_, OutputStream* outputStream, unsigned long startIndex, unsigned long maxIndex) {
    unsigned long i;
    
    const unsigned int WIDTH = EEPROM_BLOCK_COUNT * 4;

	// Table Header
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "addr", EEPROM_ADDRESS_LENGTH);
	appendStringHeader(outputStream, "Block 0", EEPROM_BLOCK_4_VALUE_LENGTH);
	appendStringHeader(outputStream, "Block 1", EEPROM_BLOCK_4_VALUE_LENGTH);
	appendStringHeader(outputStream, "Block 2", EEPROM_BLOCK_4_VALUE_LENGTH);
	appendStringHeader(outputStream, "Block 3", EEPROM_BLOCK_4_VALUE_LENGTH);
	appendTableSeparator(outputStream);
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);

	unsigned long rowIndex = 0;
    for (i = startIndex; i < maxIndex; i++) {
        char c = eeprom_->eepromReadChar(eeprom_, i);
		unsigned int columnIndex = (i % WIDTH);
		if (columnIndex == 0) {
			// address
			appendHex6TableData(outputStream, i, EEPROM_ADDRESS_LENGTH);
        }
		if ((i % EEPROM_BLOCK_COUNT) == 0) {
			appendHex2TableData(outputStream, c, 3);
		}
		else {
			appendHex2(outputStream, c);
			appendSpace(outputStream);
		}
		if (columnIndex == WIDTH - 1) {
			rowIndex++;
			appendTableSeparator(outputStream);
			println(outputStream);
			if ((rowIndex % EEPROM_BLOCK_COUNT) == 0) {
				appendTableHeaderSeparatorLine(outputStream);
			}
		}
	}
}
