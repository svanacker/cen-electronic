#ifndef LOG_HANDLER_LIST_H
#define LOG_HANDLER_LIST_H

#include "logHandlerList.h"
#include "logHandler.h"

/**
 * The struct defining a list of log handler.
 */
typedef struct {
    /** An array of pointer on device Descriptor. */
    LogHandler(*logHandlers)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;
} LogHandlerList;


/**
* Init the list of logHandler
* @param handlerListArray the array containing all log Handlers
* @param handlerListSize the size of the previous array
*/
void initLogHandlerList(LogHandlerList* logHandlerList, LogHandler(*logHandlerListArray)[], unsigned char logHandlerListSize);

/**
 * Add a log handler to the list.
 * @param logHandlerList the list in which we add the log handler
 * @param logLevel the log level
 * @param handlerName the name of the handler
 * @param outputStream the underlying outputStream
 * @return logHandler the result.
 */
LogHandler* addLogHandlerToList(LogHandlerList* logHandlerList, enum LogLevel logLevel, unsigned long logCategoryMask, char* handlerName, OutputStream* outputStream);

/**
 * Get the log handler by the index.
 * @param logHandlerList the list in which we want to take an indexed element
 * @param logHandlerIndex the index (between 0 and getLogHandlerCount)
 * @return a pointer on the available LogHandler
 */
LogHandler* getLogHandler(LogHandlerList* logHandlerList, int logHandlerIndex);

/**
 * Get the count of log Handler.
 * @param logHandlerList the list of log handlers
 * @return the count of log Handler in the list.
 */
int getLogHandlerCount(LogHandlerList* logHandlerList);

#endif

