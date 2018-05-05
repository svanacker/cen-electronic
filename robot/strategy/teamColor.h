#ifndef TEAM_COLOR_H
#define TEAM_COLOR_H

#include "../../common/io/outputStream.h"

/** Define the color for the team. */
enum TeamColor {
    /** 2018 Orange Color. */
    TEAM_COLOR_ORANGE = 0,
    /** 2018 Green Color. */
    TEAM_COLOR_GREEN = 1
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
