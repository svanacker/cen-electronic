#ifndef GAME_TARGET_ACTION_ITEM_DEBUG_H
#define GAME_TARGET_ACTION_ITEM_DEBUG_H

#include "gameTargetActionItem.h"

#include "../../common/io/outputStream.h"

// ActionItemStatus

unsigned int appendActionItemStatusAsString(OutputStream* outputStream, enum ActionItemStatus actionItemStatus);

unsigned int appendActionItemStatusTableData(OutputStream* outputStream, enum ActionItemStatus actionItemStatus, int columnSize);

#endif

