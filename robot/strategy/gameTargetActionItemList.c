#include "gameTargetActionItemList.h"
#include "gameTargetActionItem.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void addTargetActionItem(GameTargetActionItemList* targetActionItemList,
					 GameTargetActionItem* targetActionItem,
					 GameTargetActionFunction* actionItem,
					 char* name
) {
    unsigned char size = targetActionItemList->size;
	if (size < MAX_TARGET_ACTION_ITEM) {
		targetActionItem->actionItem = actionItem;
		targetActionItem->name = name;
	    targetActionItemList->items[size] = targetActionItem;
	    targetActionItemList->size++;
	}
	else {
		writeError(TOO_MUCH_TARGET_ACTION_ITEM);
    }
}

GameTargetActionItem* getGameTargetActionItem(GameTargetActionItemList* targetActionItemList, int index) {
    return targetActionItemList->items[index];
}

int getGameTargetActionItemCount(GameTargetActionItemList* targetActionItemList) {
    return targetActionItemList->size;
}

void printGameTargetActionItemList(OutputStream* outputStream, GameTargetActionItemList* targetItems) {
	int i;
	int size = targetItems->size;
	for (i = 0; i < size; i++) {
		GameTargetActionItem* targetActionItem = targetItems->items[i];
		printGameTargetActionItem(outputStream, targetActionItem);
	}
}
