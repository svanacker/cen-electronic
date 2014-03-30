#include "outputStream.h"

void initOutputStream(OutputStream* outputStream,
        OpenOutputStreamFunction* openOutputStream,
        CloseOutputStreamFunction* closeOutputStream,
        WriteCharFunction* writeChar,
        FlushFunction* flush,
        int* object) {

    outputStream->openOutputStream = openOutputStream;
    outputStream->closeOutputStream = closeOutputStream;
    outputStream->writeChar = writeChar;
    outputStream->flush = flush;
    outputStream->object = object;
}
