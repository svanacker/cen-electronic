#ifndef START_MATCH_PERSITENCE_H
#define START_MATCH_PERSITENCE_H

#include <stdbool.h>

#include "startMatch.h"
#include "endMatch.h"

#include "../robot.h"
#include "teamColor.h"


#define EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET         0
#define EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET         6
#define EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET    12

#define EEPROM_START_MATCH_ROBOT_POSITION_BLOCK_SIZE      20

/**
* Fill the Robot Position structure with the initial position when having teamColor set.
* @param robotPosition (IN) the structure to fill
* @param teamColor the color for which we want the initial Position.
*/
void loadStartMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor);

/** 
 * Save into the Eeprom the startMatch position for a specific color.
 */
void saveMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor);

#endif
