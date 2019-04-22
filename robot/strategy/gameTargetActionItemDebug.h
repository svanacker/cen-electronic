#ifndef GAME_TARGET_ACTION_ITEM_DEBUG_H
#define GAME_TARGET_ACTION_ITEM_DEBUG_H

#include "gameTargetActionItem.h"

#include "../../common/io/outputStream.h"

// ActionItemStatus

unsigned int appendActionItemStatusAsString(OutputStream* outputStream, enum ActionItemStatus actionItemStatus);

unsigned int appendActionItemStatusTableData(OutputStream* outputStream, enum ActionItemStatus actionItemStatus, int columnSize);

// ActionItemPhasis

/**
 * print the enum ActionItemPhasis as String
 * @param gameTargetList
 * @param outputStream
 */
unsigned int appendActionItemPhasisAsString(OutputStream* outputStream, enum ActionItemPhasis actionItemPhasis);

/**
 * Append ActionItemPhasis enum in a table
 * @param outputStream
 * @param actionItemPhasis
 * @param columnSize
 * @return
 */
unsigned int appendActionItemPhasisTableData(OutputStream* outputStream, enum ActionItemPhasis actionItemPhasis, int columnSize);

#endif

