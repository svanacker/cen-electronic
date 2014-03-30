#include "inputStream.h"

void initInputStream(InputStream* stream,
        OpenInputStreamFunction* openInputStream,
        CloseInputStreamFunction* closeInputStream,
        ReadCharFunction* readChar,
        AvailableDataFunction* availableData,
        int* object) {

    stream->openInputStream = openInputStream;
    stream->closeInputStream = closeInputStream;
    stream->readChar = readChar;
    stream->availableData = availableData;
    stream->object = object;
}

void clearInputStream(InputStream* inputStream) {
    while (inputStream->availableData(inputStream)) {
        // clear buffer
        inputStream->readChar(inputStream);
    }
}
