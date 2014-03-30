#ifndef IOUTILS_H
#define IOUTILS_H

#include "filter.h"
#include "inputStream.h"
#include "outputStream.h"

#define COPY_ALL -1

/**
 * Copy the data from inputStream to outputStream with a buffer
 * @param inputStream the stream corresponding to the source of data
 * @param outputStream the stream in which we copy data
 * @param filterChar a filteringChar function (can be null)
 * @param dataCountToCopy the number of data which must be read for copy. use COPY_ALL
 * if you do not want to restrict the number of data
 */
unsigned int copyInputToOutputStream(InputStream* inputStream,
        OutputStream* outputStream,
        filterCharFunction* filterChar,
        int dataCountToCopy);

#endif

