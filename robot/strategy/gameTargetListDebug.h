#ifndef GAME_TARGET_LIST_DEBUG_H
#define GAME_TARGET_LIST_DEBUG_H

#include "gameTargetList.h"

#include "../../common/io/outputStream.h"

/**
 * Print the game target list, and for each the detail of target.
 */
void printGameTargetListTable(GameTargetList* gameTargetList, OutputStream* outputStream);

#endif

