#include <stdlib.h>

#include "ioUtils.h"

#include "../../common/commons.h"

#include "inputStream.h"
#include "outputStream.h"
#include "printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "filter.h"

unsigned int copyInputToOutputStream(InputStream* inputStream,
        OutputStream* outputStream,
        filterCharFunction* filterChar,
        int dataCountToCopy) {
    int result = 0;
    int count = 0;
    // while data are available on inputStream
    while (inputStream->availableData(inputStream)) {

        // Controls the number of data
        if (dataCountToCopy != COPY_ALL) {
            count++;
            if (count > dataCountToCopy) {
                break;
            }
        }

        // get the next char
        unsigned char c = inputStream->readChar(inputStream);
        if (c == 0x00 || c == INCORRECT_DATA) {
            break;
        }

        // if we defined a filterChar function
        if (filterChar != NULL) {
            unsigned char filteredValue = c;
            // function returns if we include or not char
            BOOL include = filterChar(c, &filteredValue);
            if (include) {
                // write the filtered char into the output stream
                outputStream->writeChar(outputStream, filteredValue);
                result++;
            }
        } else {
            // no filter write the char into the output stream
            outputStream->writeChar(outputStream, c);
            result++;
        }
    }
    // Flush of data
    outputStream->flush(outputStream);

    return result;
}
