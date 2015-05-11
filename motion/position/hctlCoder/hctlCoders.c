#include "../../../motion/position/coders.h"
#include "hctl2032.h"

void updateCoders(void) {
    hctl_updateCoders();
}

signed long getCoderValue(enum CoderType coderType) {
    return hctl_getCoderValue(coderType);
}

void clearCoders(void) {
    hctl_clearCoders();
}

void initCoders(void) {
    // init the program
    initHCTL2032();

    clearCoders();
}

void checkCoders(void) {
    // TODO : Implementation
}

int getCodersErrorCount(enum CoderType coderType) {
    // TODO : Implementation
    return 0;
}

int getCodersErrorValue(enum CoderType coderType) {
    // TODO : Implementation
    return 0;
}

signed long getCodersInitialPosition(enum CoderType coderType) {
    // TODO : Implementation
    return 0;
}

int getCodersZCount(enum CoderType coderType) {
    // TODO : Implementation
    return 0;
}
