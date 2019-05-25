#include "ioExpanderList.h"

#include <stdlib.h>
#include <stdbool.h>

#include "ioExpander.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"


void initIOExpanderList(IOExpanderList* ioExpanderList,
                       IOExpander(*ioExpanderArray)[],
                       unsigned int ioExpanderListSize) {
    if (ioExpanderArray == NULL) {
        writeError(IO_EXPANDER_LIST_NOT_INITIALIZED);
    }
    ioExpanderList->ioExpanderArray = ioExpanderArray;
    ioExpanderList->size = ioExpanderListSize;
}

IOExpander* getIOExpanderByIndex(IOExpanderList* ioExpanderList, unsigned int index) {
    if (ioExpanderList == NULL || ioExpanderList->ioExpanderArray == NULL) {
        writeError(IO_EXPANDER_LIST_NOT_INITIALIZED);
        return NULL;
    }
	if (index < 0 || index >= ioExpanderList->size) {
		writeError(IO_EXPANDER_LIST_ILLEGAL_INDEX);
		return NULL;
	}
    IOExpander* result = (IOExpander*) ioExpanderList->ioExpanderArray;
	// we don't need use sizeof because our pointer is a IOExpander pointer, so the shift
	// is already of the structure, we just have to shift of index.
	result += index;

	return result;
}
