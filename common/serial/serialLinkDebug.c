#include <stdlib.h>

#include "serialLinkDebug.h"
#include "serialLink.h"
#include "serialLinkList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define SERIAL_LINK_IDX_COLUMN_LENGTH				                          10
#define SERIAL_LINK_PORT_COLUMN_LENGTH				                          10
#define SERIAL_LINK_NAME_COLUMN_LENGTH				                          20
#define SERIAL_LINK_SPEED_COLUMN_LENGTH			                              10
#define SERIAL_LINK_INPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH			  15
#define SERIAL_LINK_OUTPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH		  15

#define SERIAL_LINK_DEBUG_LAST_COLUMN_LENGTH                                  0

/**
 * Private.
 */
void printSerialLinkDebugHeader(OutputStream* outputStream) {
	appendTableHeaderSeparatorLine(outputStream);
    // First Header Line
	appendStringHeader(outputStream, "idx", SERIAL_LINK_IDX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "port", SERIAL_LINK_PORT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "name", SERIAL_LINK_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "speed", SERIAL_LINK_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "inputBuffer", SERIAL_LINK_INPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "output Buffer", SERIAL_LINK_OUTPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, SERIAL_LINK_DEBUG_LAST_COLUMN_LENGTH);
    // Second Header Line
    appendStringHeader(outputStream, "idx", SERIAL_LINK_IDX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "port", SERIAL_LINK_PORT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "name", SERIAL_LINK_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "speed", SERIAL_LINK_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "available", SERIAL_LINK_INPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "available", SERIAL_LINK_OUTPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, SERIAL_LINK_DEBUG_LAST_COLUMN_LENGTH);
    // Third Header Line
    appendStringHeader(outputStream, "idx", SERIAL_LINK_IDX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "port", SERIAL_LINK_PORT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "name", SERIAL_LINK_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "speed", SERIAL_LINK_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Char Count", SERIAL_LINK_INPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Char Count", SERIAL_LINK_OUTPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, SERIAL_LINK_DEBUG_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

void printSerialLinkList(OutputStream* outputStream) {
    int size = getSerialLinkCount();
    appendStringAndDec(outputStream, "serialLinkCount=", size);
    int i;
	println(outputStream);
	printSerialLinkDebugHeader(outputStream);
    for (i = 0; i < size; i++) {
        SerialLink* serialLink = getSerialLink(i);
        printSerialLink(outputStream, serialLink, i);
    }
	appendTableHeaderSeparatorLine(outputStream);
}

void printSerialLink(OutputStream* outputStream, const SerialLink* serialLink, int index) {
    if (serialLink != NULL) {
        StreamLink* streamLink = serialLink->streamLink;
        const Buffer* inputBuffer = streamLink->inputBuffer;
        unsigned int inputBufferAvailableCharCount = getBufferElementsCount(inputBuffer);
        const Buffer* outputBuffer = streamLink->outputBuffer;
        unsigned int outputBufferAvailableCharCount = getBufferElementsCount(outputBuffer);
		appendDecTableData(outputStream, index, SERIAL_LINK_IDX_COLUMN_LENGTH);
		appendDecTableData(outputStream, serialLink->serialPort, SERIAL_LINK_PORT_COLUMN_LENGTH);
		appendStringTableData(outputStream, serialLink->name, SERIAL_LINK_NAME_COLUMN_LENGTH);
		appendDecTableData(outputStream, serialLink->speed, SERIAL_LINK_SPEED_COLUMN_LENGTH);
        appendDecTableData(outputStream, inputBufferAvailableCharCount, SERIAL_LINK_INPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);
        appendDecTableData(outputStream, outputBufferAvailableCharCount, SERIAL_LINK_OUTPUT_BUFFER_AVAILABLE_CHAR_COUNT_COLUMN_LENGTH);

        appendEndOfTableColumn(outputStream, SERIAL_LINK_DEBUG_LAST_COLUMN_LENGTH);
    }
}

void printSerialLinkBuffer(OutputStream* outputStream, const SerialLink* serialLink) {
    if (serialLink != NULL) {
        StreamLink* streamLink = serialLink->streamLink;

        // Serial Input Buffer
        appendCRLF(outputStream);
        Buffer* serialInputBuffer = streamLink->inputBuffer;
        appendString(outputStream, "SERIAL INPUT BUFFER : ");
        printDebugBuffer(outputStream, serialInputBuffer);

        // Serial Output Buffer
        appendCRLF(outputStream);
        Buffer* serialOutputBuffer = streamLink->outputBuffer;
        appendString(outputStream, "SERIAL OUTPUT BUFFER : ");
        printDebugBuffer(outputStream, serialOutputBuffer);
    }
}

void clearSerialLinkBuffer(const SerialLink* serialLink) {
    if (serialLink != NULL) {
        StreamLink* streamLink = serialLink->streamLink;

        // Serial Input Buffer
        Buffer* serialInputBuffer = streamLink->inputBuffer;
        deepClearBuffer(serialInputBuffer);

        // Serial Output Buffer
        Buffer* serialOutputBuffer = streamLink->outputBuffer;
        deepClearBuffer(serialOutputBuffer);
    }
}
