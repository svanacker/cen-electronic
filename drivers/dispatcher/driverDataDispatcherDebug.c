#include "driverDataDispatcherList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../device/transmitMode.h"


#define DISPATCHER_INDEX_NAME_COLUMN_LENGTH					 5
#define DISPATCHER_DEBUG_NAME_COLUMN_LENGTH					 25
#define DISPATCHER_DEBUG_TRANSMIT_MODE_COLUMN_LENGTH		 12
#define DISPATCHER_DEBUG_TRANSMIT_MODE_STRING_COLUMN_LENGTH  10
#define DISPATCHER_DEBUG_ADDRESS_COLUMN_LENGTH               12

// DEBUG

/**
* Private.
*/
void printDriverDataDispatcherListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Index", DISPATCHER_INDEX_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Dispatcher Name", DISPATCHER_DEBUG_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "transmitMode", DISPATCHER_DEBUG_TRANSMIT_MODE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(String)", DISPATCHER_DEBUG_TRANSMIT_MODE_STRING_COLUMN_LENGTH);
	appendStringHeader(outputStream, "addr (Hex)", DISPATCHER_DEBUG_ADDRESS_COLUMN_LENGTH);
	appendTableSeparator(outputStream);
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
}

void printDriverDataDispatcher(OutputStream* outputStream, DriverDataDispatcher* dispatcher, int index) {
	appendDecTableData(outputStream, index, DISPATCHER_INDEX_NAME_COLUMN_LENGTH);
	appendStringTableData(outputStream, dispatcher->name, DISPATCHER_DEBUG_NAME_COLUMN_LENGTH);
	TransmitMode transmitMode = dispatcher->transmitMode;
	appendDecTableData(outputStream, transmitMode, DISPATCHER_DEBUG_TRANSMIT_MODE_COLUMN_LENGTH);
	const char* transmitModeAsString = getTransmitModeAsString(transmitMode);
	appendStringTableData(outputStream, transmitModeAsString, DISPATCHER_DEBUG_TRANSMIT_MODE_STRING_COLUMN_LENGTH);
	appendHex2TableData(outputStream, dispatcher->address, DISPATCHER_DEBUG_ADDRESS_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}

void printDriverDataDispatcherList(OutputStream* outputStream, DriverDataDispatcherList* dispatcherList) {
	printDriverDataDispatcherListHeader(outputStream);
    int i;
    for (i = 0; i < dispatcherList->size; i++) {
        DriverDataDispatcher* dispatcher = getDriverDataDispatcherByIndex(i);    
        printDriverDataDispatcher(outputStream, dispatcher, i);
    }
	appendTableHeaderSeparatorLine(outputStream);
}
