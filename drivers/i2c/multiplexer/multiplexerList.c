#include "multiplexerList.h"

#include <stdlib.h>
#include <stdbool.h>

#include "multiplexer.h"

#include "../../../common/error/error.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logHandler.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

void initMultiplexerList(MultiplexerList* multiplexerList,
        Multiplexer(*multiplexerArray)[],
        unsigned int multiplexerListSize) {
    if (multiplexerArray == NULL) {
        writeError(MULTIPLEXER_LIST_NOT_INITIALIZED);
    }
    multiplexerList->multiplexerArray = multiplexerArray;
    multiplexerList->size = multiplexerListSize;
}

Multiplexer* getMultiplexerByIndex(MultiplexerList* multiplexerList, unsigned int index) {
    if (multiplexerList == NULL || multiplexerList->multiplexerArray == NULL) {
        writeError(MULTIPLEXER_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= multiplexerList->size) {
        writeError(MULTIPLEXER_LIST_ILLEGAL_INDEX);
        return NULL;
    }
    Multiplexer* result = (Multiplexer*) multiplexerList->multiplexerArray;
    // we don't need use sizeof because our pointer is a Multiplexer pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}
