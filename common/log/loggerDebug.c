#include "logger.h"
#include "logHandler.h"
#include "logHandlerList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printTableWriter.h"

#define LOGGER_DEBUG_INDEX_COLUMN_LENGTH			  10
#define LOGGER_DEBUG_HANDLER_NAME_COLUMN_LENGTH       20
#define LOGGER_DEBUG_LEVEL_COLUMN_LENGTH			  20
#define LOGGER_DEBUG_LAST_COLUMN_LENGTH			      57

/**
 * Private.
 */
void printLogListHeader(OutputStream* outputStream) {
    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "index", LOGGER_DEBUG_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "handler Name", LOGGER_DEBUG_HANDLER_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "level", LOGGER_DEBUG_LEVEL_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LOGGER_DEBUG_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}

void printLogHandler(OutputStream* outputStream, LogHandler* logHandler, int index) {
    appendDecTableData(outputStream, index, LOGGER_DEBUG_INDEX_COLUMN_LENGTH);
    appendStringTableData(outputStream, logHandler->handlerName, LOGGER_DEBUG_HANDLER_NAME_COLUMN_LENGTH);
    char* logLevelAsString = getLevelAsString(logHandler->logLevel);
    appendStringTableData(outputStream, logLevelAsString, LOGGER_DEBUG_LEVEL_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LOGGER_DEBUG_LAST_COLUMN_LENGTH);
}

void printLogger(OutputStream* outputStream) {
    Logger* logger = getLoggerInstance();
    println(outputStream);
    appendKeyAndName(outputStream, "GlobalLogLevel=", getLevelAsString(logger->globalLogLevel));
    println(outputStream);
    appendKeyAndName(outputStream, "WriteLogLevel=", getLevelAsString(logger->writeLogLevel));
    println(outputStream);
    printLogListHeader(outputStream);
    // For Each LogHandler
    LogHandlerList* logHandlerList = getLoggerHandlerList();
    int count = getLogHandlerCount(logHandlerList);
    int i;
    for (i = 0; i < count; i++) {
        LogHandler* logHandler = getLogHandler(logHandlerList, i);
        printLogHandler(outputStream, logHandler, i);
    }
    appendTableHeaderSeparatorLine(outputStream);
}
