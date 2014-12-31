#ifndef LOG_HANDLER_LIST_H
#define LOG_HANDLER_LIST_H

#include "logHandlerList.h"
#include "logHandler.h"

/** The max limit of handler list. */
// Currently, we use only 2 Handlers max (DEBUG, LCD ...) !
#define MAX_LOG_HANDLER 2

/**
 * The struct defining a list of log handler.
 */
typedef struct {
    /** An array of pointer on device Descriptor. */
    LogHandler* logHandlers[MAX_LOG_HANDLER];
    /** the size of the list. */
    unsigned char size;
} LogHandlerList;

/**
 * Add a log handler to the list.
 * @param logHandlerList the list in which we add the log handler
 * @param logHandler the handler that we want to add
 */
void addLogHandlerToList(LogHandlerList* logHandlerList, LogHandler* logHandler);

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

