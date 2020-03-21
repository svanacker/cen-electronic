#ifndef IO_EXPANDER_LIST_H
#define IO_EXPANDER_LIST_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"

#include "ioExpander.h"

// Forward declaration
typedef struct IOExpanderList IOExpanderList;

/**
 * The struct defining a list of IO Expander.
 */
struct IOExpanderList {
    /** An array of pointer on ioExpander. */
    IOExpander(*ioExpanderArray)[];
    /** the size of the list. */
    unsigned int size;
};

/**
 * Initializes a list of IO Expander.
 * @param ioExpanderArray the array presized with IOExpander
 * @param ioExpanderListSize the size of the array of IOExpander
 */
void initIOExpanderList(IOExpanderList* ioExpanderList,
        IOExpander(*ioExpanderArray)[],
        unsigned int ioExpanderListSize);

/**
 * Get an IO Expander by his index.
 * @param index the index of the IOExpander to get.
 * @return a ioExpander at the right index.
 */
IOExpander* getIOExpanderByIndex(IOExpanderList* ioExpanderList, unsigned int index);


#endif
