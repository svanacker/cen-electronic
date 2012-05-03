#include "gameTargetActionList.h"
#include "gameTargetAction.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"


void addTargetAction(GameTargetActionList* targetActionList, GameTargetAction* targetAction) {
    unsigned char size = targetActionList->size;
	if (size < MAX_TARGET_ACTION) {
	    targetActionList->actions[size] = targetAction;
	    targetActionList->size++;
	}
	else {
		writeError(TOO_MUCH_TARGET_ACTION);
    }
}

GameTargetAction* getTargetAction(GameTargetActionList* targetActionList, int index) {
    return targetActionList->actions[index];
}

int getTargetActionCount(GameTargetActionList* targetActionList) {
    return targetActionList->size;
}

void printTargetActionList(OutputStream* outputStream, GameTargetActionList* targets) {
	int i;
	int size = targets->size;
	println(outputStream);	
	for (i = 0; i < size; i++) {
		GameTargetAction* targetAction = targets->actions[i];
		printGameTargetAction(outputStream, targetAction);
	}
}
