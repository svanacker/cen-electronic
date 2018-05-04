#ifndef GAME_TARGET_ACTION_LIST_DEBUG_H
#define GAME_TARGET_ACTION_LIST_DEBUG_H

#include "gameTargetActionList.h"

#include "../../common/io/outputStream.h"


/**
* Print the game target action list, and for each the detail of target action
*/
void printGameTargetActionList(OutputStream* outputStream, GameTargetActionList* list);

#endif
