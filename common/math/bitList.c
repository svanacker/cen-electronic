#include "bitList.h"

// #define BIT_LIST_DEBUG

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

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
	#ifdef BIT_LIST_DEBUG
		println(getOutputStreamLogger(INFO));
		appendStringAndDec(getOutputStreamLogger(INFO), ", index=", index);
		appendStringAndDec(getOutputStreamLogger(INFO), ", value=", value);
	#endif
	if (index > bitList->size) {
		appendStringAndDec(getOutputStreamLogger(ALWAYS), ", index=", index);
		appendStringAndDec(getOutputStreamLogger(ALWAYS), ", size=", bitList->size);
		writeError(BIT_LIST_ARRAY_OUT_OF_BOUNDS);
		return;
	}
	unsigned int* arrayPointer = (unsigned int*) bitList->array;
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), "arrayPointer=", (int) arrayPointer);
	#endif

	// Division by 16 (2^4))
	unsigned char arrayIndex = index >> 4;
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), ", arrayIndex=", arrayIndex);
	#endif

	// relative index = modulo
	unsigned char relativeIntIndex = index - (arrayIndex << 4);
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), ", relativeIntIndex=", relativeIntIndex);
	#endif


	// Shift to the right cell index
	arrayPointer += arrayIndex;
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), ", newArrayPointer=", (int) arrayPointer);
		appendStringAndDec(getOutputStreamLogger(INFO), ", pointerValue=", *arrayPointer);
	#endif

	unsigned int mask = (1 << relativeIntIndex);
	if (value) {
		*arrayPointer |= mask;
	}
	else {
		*arrayPointer &= (~mask);
	}
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), ", newPointerValue=", *arrayPointer);
	#endif
}

BOOL getBit(BitList* bitList, unsigned char index) {
	#ifdef BIT_LIST_DEBUG
		println(getOutputStreamLogger(INFO));
		appendStringAndDec(getOutputStreamLogger(INFO), ", index=", index);
	#endif	

	if (index > bitList->size) {
		writeError(BIT_LIST_ARRAY_OUT_OF_BOUNDS);
		return FALSE;
	}

	unsigned int* arrayPointer = (unsigned int*) bitList->array;

	// Division by 16 (2^4))
	unsigned char arrayIndex = index >> 4;
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), ", arrayIndex=", arrayIndex);
	#endif

	// relative index = modulo
	unsigned char relativeIntIndex = index - (arrayIndex << 4);
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), ", relativeIntIndex=", relativeIntIndex);
	#endif
	
	arrayPointer += arrayIndex;
	#ifdef BIT_LIST_DEBUG
		appendStringAndDec(getOutputStreamLogger(INFO), ", arrayPointer=", *arrayPointer);
	#endif

	unsigned int mask = (1 << relativeIntIndex);
	return (*arrayPointer & mask) != 0;
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
		appendDec(outputStream, value);
	}
}
