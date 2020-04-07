#include <stdbool.h>
#include <stdlib.h>

#include "gameTarget.h"
#include "gameTargetActionList.h"

#include "../../common/commons.h"

void clearGameTarget(GameTarget* target) {
    target->name = "?";
    target->potentialGain = 0;
    target->status = TARGET_AVAILABLE;

    if (&(target->actionList) != NULL) {
        clearTargetActionList(&(target->actionList));
    }
}

void updateTargetStatus(GameTarget* target) {
    GameTargetActionList* list = &(target->actionList);
    if (list == NULL) {
        return;
    }
    unsigned int i;
    unsigned int size = list->size;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = list->actions[i];
        if (targetAction->status == ACTION_STATUS_ERROR) {
            target->status = TARGET_MISSED;
            return;
        }

        if (targetAction->status == ACTION_STATUS_DOING) {
            target->status = TARGET_HANDLING;
            return;
        }
    }
    target->status = TARGET_HANDLED;
}
