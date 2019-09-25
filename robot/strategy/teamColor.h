#ifndef TEAM_COLOR_H
#define TEAM_COLOR_H

#include "../../common/io/outputStream.h"

/** Define the color for the team. */
enum TeamColor {
    /** Unknown Color */
    TEAM_COLOR_UNKNOWN = 0,
    /** 2020 Blue Color. */
    TEAM_COLOR_BLUE = 1,
    /** 2020 Yellow Color. */
    TEAM_COLOR_YELLOW = 2
};

/** 
 * Append the color of the team color to an outputStream.
 */
unsigned int appendTeamColorAsString(OutputStream* outputStream, enum TeamColor teamColor);

/**
 * Add a table data with the team color.
 */
unsigned int addTeamColorTableData(OutputStream* outputStream, enum TeamColor teamColor, int columnSize);

#endif
