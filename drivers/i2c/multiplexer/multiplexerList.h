#ifndef MULTIPLEXER_LIST_H
#define MULTIPLEXER_LIST_H

#include <stdbool.h>

#include "../../../common/io/outputStream.h"

#include "multiplexer.h"

// Forward declaration
typedef struct MultiplexerList MultiplexerList;

/**
 * The struct defining a list of Multiplexer.
 */
struct MultiplexerList {
    /** An array of pointer on multiplexer. */
    Multiplexer(*multiplexerArray)[];
    /** the size of the list. */
    unsigned int size;
};

/**
 * Initialises a list of Multiplexer.
 * @param multiplexerArray the array presized with Multiplexer
 * @param multiplexerListSize the size of the array of Multiplexer
 */
void initMultiplexerList(MultiplexerList* multiplexerList,
        Multiplexer(*multiplexerArray)[],
        unsigned int multiplexerListSize);

/**
 * Get an Multiplexer by his index.
 * @param index the index of the Multiplexer to get.
 * @return a multiplexer at the right index.
 */
Multiplexer* getMultiplexerByIndex(MultiplexerList* multiplexerList, unsigned int index);


#endif
