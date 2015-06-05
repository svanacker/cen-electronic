#include "system.h"

static char* boardName;

void setBoardName(char* aBoardName) {
    boardName = aBoardName;
}

char* getBoardName(void) {
    return boardName;
}
