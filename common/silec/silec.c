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
    
    A0_HC237_dir = 0;
    A1_HC237_dir = 0;
    A2_HC237_dir = 0;
    E1_HC237_dir = 0;
    
    STROBE_UCN5895_dir = 0;
    SER_IN_UCN5895_dir = 0;
    CLOCK_UCN5895_dir = 0;
}

bool isSilecInitialized(Silec* silec) {
    if (silec->initSILEC == NULL 
        || silec->WriteSilec == NULL ) {
        return false;
    }
    return true;
}
