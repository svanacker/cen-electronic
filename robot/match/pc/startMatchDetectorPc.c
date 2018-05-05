#include "startMatchDetectorPc.h"
#include "../startMatch.h"

#include <stdbool.h>
#include <stdio.h>

#include "../../../common/error/error.h"

#include "../../../common/pc/file/fileUtils.h"

void startMatchPc(void) {
    // TODO
}

bool isMatchStartedPc(StartMatch* startMatch) {
    FILE * filePointer;

    filePointer = fopen(START_MATCH_DETECTOR_PC_FILE_NAME, "r");

    unsigned long fileLength = readFileLength(filePointer);

    if (fileLength != START_MATCH_DETECTOR_PC_FILE_LENGTH) {
        writeError(ROBOT_START_MATCH_DETECTOR_PC_FILE_LENGTH_ERROR);
        return false;
    }

    bool result = fgetc(filePointer) == '1';

    return result;
}
