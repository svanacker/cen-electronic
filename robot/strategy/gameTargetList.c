#include "gameTargetList.h"
#include "gameTarget.h"

#include "../../common/error/error.h"

/**
 * Target list.
 */
static GameTargetList targets;

void addTarget(GameTarget* target, char* targetName) {
    unsigned char size = targets.size;
	if (size < MAX_TARGET) {
		target->name = targetName;
	    targets.targets[size] = target;
	    targets.size++;
	}
	else {
		writeError(TOO_MUCH_TARGETS);
    }
}

GameTarget* getGameTarget(int index) {
    return targets.targets[index];
}

int getGameTargetCount() {
    return targets.size;
}
