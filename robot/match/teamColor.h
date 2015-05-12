#ifndef TEAM_COLOR_H
#define TEAM_COLOR_H

/** Define the color for the team. */
enum TeamColor {
    /** 2015 Yellow Color. */
    COLOR_YELLOW = 0,
    /** 2015 Green Color. */
    COLOR_GREEN = 1
};

/** 
 * Returns the color of the team.
 */
char* getTeamColorAsString(enum TeamColor teamColor);

#endif
