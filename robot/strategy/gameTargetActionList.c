#include "gameTargetActionList.h"
#include "gameTargetAction.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"


void addTargetAction(GameTargetActionList* targetActionList,
					 GameTargetAction* targetAction,
					 Location* startLocation,
					 Location* endLocation,
					 int timeToAchieve
) {
    unsigned char size = targetActionList->size;
	if (size < MAX_TARGET_ACTION) {
		targetAction->startLocation = startLocation;
		targetAction->endLocation = endLocation;
		targetAction->timeToAchieve = timeToAchieve;
	    targetActionList->actions[size] = targetAction;
	    targetActionList->size++;
	}
	else {
		writeError(TOO_MUCH_TARGET_ACTION);
    }
}

GameTargetAction* getGameTargetAction(GameTargetActionList* targetActionList, int index) {
    return targetActionList->actions[index];
}

int getGameTargetActionCount(GameTargetActionList* targetActionList) {
    return targetActionList->size;
}

void printGameTargetActionList(OutputStream* outputStream, GameTargetActionList* targets) {
	int i;
	int size = targets->size;
	for (i = 0; i < size; i++) {
		GameTargetAction* targetAction = targets->actions[i];
		printGameTargetAction(outputStream, targetAction);
	}
}
