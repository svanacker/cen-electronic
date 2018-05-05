#include "gameTargetStatus.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned int appendGameTargetStatusAsString(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus) {
    switch (gameTargetStatus) {
        case TARGET_AVAILABLE: return appendString(outputStream, "AVAILABLE");
        case TARGET_HANDLED: return appendString(outputStream, "HANDLED");
        case TARGET_INUSE: return appendString(outputStream, "IN USE");
    }
    appendString(outputStream, "?");

    return 1;
}

unsigned int addGameTargetStatusTableData(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendGameTargetStatusAsString(outputStream, gameTargetStatus);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

