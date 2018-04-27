#ifndef TEAM_COLOR_H
#define TEAM_COLOR_H

/** Define the color for the team. */
enum TeamColor {
    /** 2018 Orange Color. */
    TEAM_COLOR_ORANGE = 0,
    /** 2018 Green Color. */
    TEAM_COLOR_GREEN = 1
};

/** 
 * Returns the color of the team.
 */
char* getTeamColorAsString(enum TeamColor teamColor);

#endif
