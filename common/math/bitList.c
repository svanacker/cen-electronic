#include "bitList.h"

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void initBitList(BitList* bitList, unsigned (*array)[], unsigned char arrayLength) {
	bitList->array = array;
	bitList->arrayLength = arrayLength;
	bitList->size = arrayLength * BITS_COUNT_IN_UNSIGNED_INT;
    // clearBitList(bitList);
}

void clearBitList(BitList* bitList) {
	int i;
	int size = bitList->size;
	for (i = 0; i < size; i++) {
		setBit(bitList, i, FALSE);
	}
}


void setBit(BitList* bitList, unsigned char index, BOOL value) {
	if (index > bitList->size) {
		writeError(BIT_LIST_ARRAY_OUT_OF_BOUNDS);
		return;
	}
	unsigned int* arrayPointer = (unsigned int*) bitList->array;

	// Division by 16 (2^4))
	unsigned char arrayIndex = index >> 4;

	// relative index = modulo
	unsigned char relativeIntIndex = index - (arrayIndex << 4);

	// Shift to the right cell index
	arrayPointer += arrayIndex;
	if (value) {
		*arrayPointer = *arrayPointer | (1 << relativeIntIndex);
	}
	else {
		*arrayPointer = *arrayPointer & (!(1 << relativeIntIndex));
	}
}

BOOL getBit(BitList* bitList, unsigned char index) {
	if (index > bitList->size) {
		writeError(BIT_LIST_ARRAY_OUT_OF_BOUNDS);
		return FALSE;
	}

	unsigned int* arrayPointer = (unsigned int*) bitList->array;

	// Division by 16 (2^4))
	unsigned char arrayIndex = index >> 4;

	// relative index = modulo
	unsigned char relativeIntIndex = index - (arrayIndex << 4);
	
	arrayPointer += arrayIndex;

	return *arrayPointer & (1 << relativeIntIndex);
}


// DEBUG

void printBitList(OutputStream* outputStream, BitList* bitList) {
	int i;
	int size = bitList->size;
	println(outputStream);	
	appendStringAndDec(outputStream, "bitList->size=", bitList->size);
	println(outputStream);	
	for (i = 0; i < size; i++) {
		if ((i != 0) && (i % BITS_COUNT_IN_UNSIGNED_INT == 0)) {
			append(outputStream, ' ');
		}
		BOOL value = getBit(bitList, i);
		appendBOOL(outputStream, value);
	}
}
