#include "system.h"

static char* picName;

void setPicName(char* aPicName) {
    picName = aPicName;
}

char* getPicName(void) {
    return picName;
}