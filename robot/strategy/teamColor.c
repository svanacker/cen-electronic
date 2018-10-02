#include "teamColor.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned int appendTeamColorAsString(OutputStream* outputStream, enum TeamColor teamColor) {
    switch (teamColor) {
        case TEAM_COLOR_VIOLET: return appendString(outputStream, "VIOLET");
        case TEAM_COLOR_YELLOW: return appendString(outputStream, "YELLOW");
        default: return appendString(outputStream, "SIDE ?");
    }
}

unsigned int addTeamColorTableData(OutputStream* outputStream, enum TeamColor teamColor, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendTeamColorAsString(outputStream, teamColor);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}