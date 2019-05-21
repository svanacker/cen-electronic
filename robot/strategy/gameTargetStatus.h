#ifndef GAME_TARGET_STATUS_H
#define GAME_TARGET_STATUS_H

#include "../../common/io/outputStream.h"

/** 
 * Enumerates the different status of a game target.
 */
enum GameTargetStatus {
    /** The target is Available. */
    TARGET_AVAILABLE = 0,
    /** We reach the starting point of the target .*/
    TARGET_STARTING_POINT_REACHED = 1,
    /** The target is Handled. */
    TARGET_HANDLED = 2,
    /** The target is missed. */
    TARGET_MISSED = 3
};

unsigned int appendGameTargetStatusAsString(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus);

unsigned int addGameTargetStatusTableData(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus, int columnSize);

#endif
