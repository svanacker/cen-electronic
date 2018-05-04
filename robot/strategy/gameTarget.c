#include <stdlib.h>

#include "gameTarget.h"
#include "gameTargetActionList.h"

#include "../../common/commons.h"

void clearGameTarget(GameTarget* target) {
    target->name = "?";
    target->potentialGain = 0;
    target->status = TARGET_HANDLED;
    
    if (&(target->actionList) != NULL) {
        clearTargetActionList(&(target->actionList));
    }
}
