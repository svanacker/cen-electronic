#ifndef GAME_TARGET_STATUS_H
#define GAME_TARGET_STATUS_H

#include "../../common/io/outputStream.h"

/** 
 * Enumerates the different status of a game target.
 */
enum GameTargetStatus {
    /** The target is Available. */
    TARGET_AVAILABLE = 0,
    
    /** The target is Handled. */
    TARGET_HANDLED = 1,
    
    /** The target is in use. */
    TARGET_INUSE = 2
};

unsigned int appendGameTargetStatusAsString(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus);

unsigned int addGameTargetStatusTableData(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus, int columnSize);

#endif
