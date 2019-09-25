#include "../../../motion/position/coders.h"
#include "../../../motion/position/coderType.h"

// variables
static Coder coders[CODER_COUNT];

void updateCoders(void) {
    // DO NOTHING
}

signed long getCoderValue(enum CoderType coderType) {
    return coders[coderType].value;
}

void setCoderValue(enum CoderType coderType, signed long value) {
    coders[coderType].previousValue = coders[coderType].value;
    coders[coderType].value = value;
}

void clearCoders() {
    coders[CODER_LEFT].value = 0;
    coders[CODER_LEFT].previousValue = 0;
    coders[CODER_RIGHT].value = 0;
    coders[CODER_RIGHT].previousValue = 0;
}

void initCoders(void) {
    clearCoders();
}

void checkCoders() {
    // TODO : Implementation
}

int getCodersErrorCount(enum CoderType coderType) {
    return 0;
}

int getCodersErrorValue(enum CoderType coderType) {
    return 0;
}

signed long getCodersInitialPosition(enum CoderType coderType) {
    // TODO : Implementation
    return 0;
}

int getCodersZCount(enum CoderType coderType) {
    return 0;
}
