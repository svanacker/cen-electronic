#include "gameTargetList.h"
#include "gameTarget.h"

#include "../../common/error/error.h"

/**
 * Target list.
 * Singleton
 */
static GameTargetList targets;

void addGameTarget(GameTarget* target, char* targetName) {
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


void printGameTargetList(OutputStream* outputStream) {
	int i;
	int size = targets.size;
	println(outputStream);	
	for (i = 0; i < size; i++) {
		GameTarget* target = targets.targets[i];
		printGameTarget(outputStream, target);
	}
}
