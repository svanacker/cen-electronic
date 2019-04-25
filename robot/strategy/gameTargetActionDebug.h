#ifndef GAME_TARGET_ACTION_DEBUG_H
#define GAME_TARGET_ACTION_DEBUG_H

#include "gameTargetAction.h"

#include "../../common/io/outputStream.h"

// ActionStatus

unsigned int appendActionStatusAsString(OutputStream* outputStream, enum ActionStatus actionStatus);

unsigned int appendActionStatusTableData(OutputStream* outputStream, enum ActionStatus actionStatus, int columnSize);

#endif

