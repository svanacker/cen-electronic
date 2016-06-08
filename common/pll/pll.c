#include "pll.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printPll(OutputStream* outputStream, Pll* pll) {
    PllData* pllData = &(pll->pllData);
    appendHex4(outputStream, pllData->REGA);
}

void initPll(Pll* pll, 
        InitPLLFunction* initPLL,
        WritePllFunction* WritePll,        
        int* object) {
    pll->initPLL = initPLL;
    pll->WritePll = WritePll;    
    pll->object = object;
}

bool isPllInitialized(Pll* pll) {
    if (pll->initPLL == NULL 
        || pll->WritePll == NULL ) {
        return false;
    }
    return true;
}
