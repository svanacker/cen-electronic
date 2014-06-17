#include <stdlib.h>
#include <string.h>
#include "jennic5139Driver.h"
#include "jennic5139EventParser.h"

#include "../../common/commons.h"
#include "../../common/delay/cenDelay.h"

#include "../../common/error/error.h"

#include "../../common/io/buffer.h"
#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/hexUtils.h"

// Singleton
static JennicEventList jennicEventList;
static char dataRawInputBufferArray[JENNIC_SEARCH_DATA_RAW_INPUT_BUFFER_LENGTH];
static char searchDataBufferArray[JENNIC_SEARCH_DATA_BUFFER_LENGTH];
static char dataInputBufferArray[JENNIC_DATA_INPUT_BUFFER_LENGTH];

JennicEventList* getJennicEventList() {
    return &jennicEventList;
}

void initJennicEventList() {
    initBuffer(&(jennicEventList.dataRawInputBuffer), &dataRawInputBufferArray, JENNIC_SEARCH_DATA_RAW_INPUT_BUFFER_LENGTH, "jennicDataRawInputBuffer", "DATA_RAW");
	initBuffer(&(jennicEventList.searchDataBuffer), &searchDataBufferArray, JENNIC_SEARCH_DATA_BUFFER_LENGTH, "searchDataBuffer", "SEARCH_DATA_BUFFER");
    initBuffer(&(jennicEventList.dataInputBuffer), &dataInputBufferArray, JENNIC_DATA_INPUT_BUFFER_LENGTH, "jennicDataInputBuffer", "DATA_IN");
}

Buffer* getJennicInDataBuffer() {
    return &(jennicEventList.dataInputBuffer);
}

void addJennicEvent(JennicEvent* jennicEvent,
					 char* eventCommand,
					 char* argument0,
					 char* argument1,
					 char* argument2,
					 char payLoadArgumentIndex,
					JennicEventFunction* onEvent) {
    unsigned char size = jennicEventList.size;
    if (size < MAX_JENNIC_EVENT) {
        jennicEventList.events[size] = jennicEvent;
        jennicEventList.size++;
		// eventCommand
		jennicEvent->eventCommand[0] = *eventCommand;
		eventCommand++;
		jennicEvent->eventCommand[1] = *eventCommand;
		eventCommand++;
		jennicEvent->eventCommand[2] = *eventCommand;

		jennicEvent->argument0 = argument0;
		jennicEvent->argument1 = argument1;
		jennicEvent->argument2 = argument2;
		jennicEvent->onEvent = onEvent;
		jennicEvent->payLoadArgumentIndex = payLoadArgumentIndex;
    } else {
        writeError(TOO_MUCH_JENNIC_EVENT);
    }
}

JennicEvent* getJennicEvent(int index) {
    return jennicEventList.events[index];
}

int getJennicEventCount() {
    return jennicEventList.size;
}

/**
 * @private
 */
void clearJennicEventSearch() {
	jennicEventList.dataBlockBeginMatchIndex = 0;
	jennicEventList.matchEvent = NULL;
	clearBuffer(&(jennicEventList.searchDataBuffer));
	clearBuffer(&(jennicEventList.dataRawInputBuffer));
	jennicEventList.currentArgumentIndex = 0;
	jennicEventList.currentCommand[0] = 0;
	jennicEventList.currentCommand[1] = 0;
	jennicEventList.currentCommand[2] = 0;
}	

/**
 * @private
 */
void initJennic5139DataSearch(JennicEvent* matchEvent) {
	if (matchEvent == NULL) {
		return;
	} 
	OutputStream* searchOutputStream = &(jennicEventList.searchDataBuffer.outputStream);
	clearBuffer(&(jennicEventList.searchDataBuffer));
	// Command / Event
	append(searchOutputStream, matchEvent->eventCommand[0]);
	append(searchOutputStream, matchEvent->eventCommand[1]);
	append(searchOutputStream, matchEvent->eventCommand[2]);
	if (matchEvent->argument0 != NULL) {
		append(searchOutputStream, ',');
		appendString(searchOutputStream, matchEvent->argument0);
	}
	if (matchEvent->argument1 != NULL) {
		append(searchOutputStream, ',');
		appendString(searchOutputStream, matchEvent->argument1);
	}
	if (matchEvent->argument2 != NULL) {
		append(searchOutputStream, ',');
		appendString(searchOutputStream, matchEvent->argument2);
	}
}

/**
 * @private
 * Transform jennic RawData To Data.
 */
void jennicRawDataToData() {
    // Transform RawInData into Data (only for Data Events)
	Buffer* dataRawInputBuffer = &(jennicEventList.dataRawInputBuffer);
    InputStream* rawDataInputStream = getInputStream(dataRawInputBuffer);
    while (getBufferElementsCount(dataRawInputBuffer) >= 2) {
		// Received Data is Hexadecimal content (the content is already himself hexadecimal, but it is not important !)
		unsigned char c = readHex2(rawDataInputStream);
		OutputStream* dataOutputStream = getOutputStream(&(jennicEventList.dataInputBuffer));
		append(dataOutputStream, c);
    }
}

void handleJennicNextChar(char c) {
	// while data are available on inputStream
	int dataBlockLength = getBufferElementsCount(&(jennicEventList.searchDataBuffer));
	// get the next char
	if (c == CR || c == LF) {
		// If a matchEvent was detected before, trigger the Event
		JennicEvent* matchEvent = jennicEventList.matchEvent;
		if (matchEvent != NULL) {
			matchEvent->onEvent(matchEvent);
		}
		// reset Index : after a new line, we must research a new DATA string
		clearJennicEventSearch();
		return;
	}
	// Determine which command it is
	if (jennicEventList.dataBlockBeginMatchIndex < LENGTH_OF_JENNIC_AT_COMMAND) {
		// store the char into the current command
		jennicEventList.currentCommand[jennicEventList.dataBlockBeginMatchIndex] = c;
		jennicEventList.dataBlockBeginMatchIndex++;
		bool foundPossibleCandidate = false;

		int eventIndex = 0;
		for (eventIndex = 0; eventIndex < jennicEventList.size; eventIndex++) {
			JennicEvent* event = jennicEventList.events[eventIndex];
			int charIndex;
			bool matchCompletely = true;
			// we must check complete command
			// Ex : DAT and RST have "T" at the end, we must not control only
			// the last character
			for (charIndex = 0; charIndex < jennicEventList.dataBlockBeginMatchIndex; charIndex++) {
				// if we found a difference
				if (event->eventCommand[charIndex] != jennicEventList.currentCommand[charIndex]) {
					matchCompletely = false;
					break; 
				}
			}
			if (matchCompletely) {
				// maybe this one
				foundPossibleCandidate = true;
				// init search string only if we have 3 characters
				if (jennicEventList.dataBlockBeginMatchIndex == LENGTH_OF_JENNIC_AT_COMMAND) {
					// definitive candidate
					jennicEventList.matchEvent = event;
					// We build the search buffer
					initJennic5139DataSearch(jennicEventList.matchEvent);
				}
				break;
			}
		}
		// This is another event which is not search, or unknown string
		if (!foundPossibleCandidate) {
			clearJennicEventSearch();
			return;	
		}
	}
	else {
		// Data >= dataBlockLength (after arguments) is payLoad data
		if (jennicEventList.matchEvent->payLoadArgumentIndex == jennicEventList.currentArgumentIndex) {
			// can only occured if payLoadArgumentIndex != NO_PAYLOAD
			bufferWriteChar(&(jennicEventList.dataRawInputBuffer), c);
		}
		// avoid comparing data beyond dataBlockLength (=> wrong access to memory !!!)
		else if (jennicEventList.dataBlockBeginMatchIndex < dataBlockLength) {
			// Get the searched Data Char : We used the normally internal s array
			// because we do not use the rotating aspect of the buffer (we don't 
			// read into). If searchDataBuffer change, it must be cleared 
			char* sPointer = (char*) jennicEventList.searchDataBuffer.s;
			// Shift to the right cell index
			sPointer += jennicEventList.dataBlockBeginMatchIndex;
			char blockBeginChar = *sPointer;
			// TODO 
			// char blockBeginChar = '?';
			// The string match with search Data
			if (blockBeginChar == '?' || c == blockBeginChar) {
				jennicEventList.dataBlockBeginMatchIndex++;
			} else {
				// START DEBUG ONLY
				println(getDebugOutputStreamLogger());
				appendStringAndDec(getDebugOutputStreamLogger(), "index=", jennicEventList.dataBlockBeginMatchIndex);
				append(getDebugOutputStreamLogger(), ':');
				append(getDebugOutputStreamLogger(), blockBeginChar);
				appendString(getDebugOutputStreamLogger(), "<>");
				append(getDebugOutputStreamLogger(), c);
				println(getDebugOutputStreamLogger());
				// END DEBUG ONLY
	
				// reset : we consider that the strings does not match
				clearJennicEventSearch();
				return;
			}
		}
		if (c == ',') {
			jennicEventList.currentArgumentIndex++;
		}
	}
	
	jennicRawDataToData();
}

// DEBUG

void printJennicEvent(JennicEvent* event, OutputStream* outputStream) {
	appendString(outputStream, " cmd=");
	append(outputStream, event->eventCommand[0]);
	append(outputStream, event->eventCommand[1]);
	append(outputStream, event->eventCommand[2]);

	appendString(outputStream, ",arg0=\"");
	appendString(outputStream, event->argument0);

	appendString(outputStream, "\",arg1=");
	appendString(outputStream, event->argument1);

	appendString(outputStream, ",arg2=");
	appendString(outputStream, event->argument2);

	appendString(outputStream, ",payLoadArgumentIndex=");
	appendbool(outputStream, event->payLoadArgumentIndex);
	appendCRLF(outputStream);
}

void printJennicEventList(OutputStream* outputStream) {
	appendString(outputStream, "JENNIC EVENT LIST:\n");

	int index;	
	for (index = 0; index < jennicEventList.size; index++) {
		JennicEvent* event = jennicEventList.events[index];
		printJennicEvent(event, outputStream);
	}
}
