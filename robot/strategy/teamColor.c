#include "teamColor.h"

#include "../../common/color/color.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

/**
 * Returns the color related to the team Color
 * @param teamColor
 * @return 
 */
Color getColorForTeam(enum TeamColor teamColor) {
    Color result;
    result.R = 0;
    result.G = 0;
    result.B = 0;
    switch (teamColor) {
        case TEAM_COLOR_UNKNOWN: {
            result.R = 0;
            result.G = 0;
            result.B = 0;
            break;
        }
        case TEAM_COLOR_BLUE: {
            result.R = 0;
            result.G = 0;
            result.B = 255;
            break;
        }
        case TEAM_COLOR_YELLOW: {
            result.R = 255;
            result.G = 255;
            result.B = 0;
            break;
        }
    }
    return result;
}

unsigned int appendTeamColorAsString(OutputStream* outputStream, enum TeamColor teamColor) {
    switch (teamColor) {
        case TEAM_COLOR_UNKNOWN: return appendString(outputStream, "UNKNOWN COLOR");
        case TEAM_COLOR_BLUE: return appendString(outputStream, "BLUE");
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