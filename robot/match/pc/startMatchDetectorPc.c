#include "startMatchDetectorPc.h"
#include "../startMatch.h"

#include <stdbool.h>
#include <stdio.h>

#include "../../../common/delay/cenDelay.h"

#include "../../../common/error/error.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"

#include "../../../common/pc/file/fileUtils.h"

void startMatchPc(void) {
    // TODO
}

bool isMatchStartedPc(StartMatch* startMatch) {
    // Delay to avoid that it is always looping on reading the file
    delayMilliSecs(100);

    FILE* filePointer;

    filePointer = fopen(START_MATCH_DETECTOR_PC_FILE_NAME, "r");

    unsigned long fileLength = readFileLength(filePointer);

    if (fileLength != START_MATCH_DETECTOR_PC_FILE_LENGTH) {
        writeError(ROBOT_START_MATCH_DETECTOR_PC_FILE_LENGTH_ERROR);

        OutputStream* debugOutputStream = getErrorOutputStreamLogger();
        appendStringAndDecLN(debugOutputStream, "fileLength = ", fileLength);

        fclose(filePointer);
        return false;
    }

    // '1' == 5V like on PICS, where there is a pull Up
    bool result = fgetc(filePointer) == '0';

    fclose(filePointer);

    return result;
}
