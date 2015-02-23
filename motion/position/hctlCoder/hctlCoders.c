#include "../../../motion/position/coders.h"
#include "hctl2032.h"

void updateCoders(void) {
    hctl_updateCoders();
}

signed long getCoderValue(enum CoderType coderType) {
    return hctl_getCoderValue(coderType);
}

void clearCoders() {
    hctl_clearCoders();
}

void initCoders(void) {
    // init the program
    initHCTL2032();

    clearCoders();
}

void checkCoders() {
    // TODO : Implementation
}

int getCodersErrorCount(int index) {
    // TODO : Implementation
    return 0;
}

int getCodersErrorValue(int index) {
    // TODO : Implementation
    return 0;
}

signed long getCodersInitialPosition(int index) {
    // TODO : Implementation
    return 0;
}

int getCodersZCount(int index) {
    // TODO : Implementation
    return 0;
}
