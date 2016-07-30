#include "silec.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printSilec(OutputStream* outputStream, Silec* silec) {
    SilecData* silecData = &(silec->silecData);
    appendHex4(outputStream, silecData->line1);
}

void initSilec(Silec* silec, 
        InitSILECFunction* initSILEC,
        WriteSilecFunction* WriteSilec,        
        int* object) {
    silec->initSILEC = initSILEC;
    silec->WriteSilec = WriteSilec;    
    silec->object = object;
}

bool isSilecInitialized(Silec* silec) {
    if (silec->initSILEC == NULL 
        || silec->WriteSilec == NULL ) {
        return false;
    }
    return true;
}
