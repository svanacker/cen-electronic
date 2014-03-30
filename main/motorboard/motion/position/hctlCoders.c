#include "../../motion/position/coders.h"
#include "../../motion/position/hctl2032.h"

void updateCoders(void) {
    hctl_updateCoders();
}

signed long getCoderValue(int index) {
    return hctl_getCoderValue(index);
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
