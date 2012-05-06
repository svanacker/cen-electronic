#include "gameTargetList.h"
#include "gameTarget.h"

#include "../../common/error/error.h"

#include "../../navigation/navigation.h"


/**
 * Target list.
 * Singleton
 */
static GameTargetList targets;

GameTargetList* getGameTargetList() {
	return &targets;
}

void addGameTarget(GameTarget* target, char* targetName, int gain, Location* location) {
    unsigned char size = targets.size;
	if (size < MAX_TARGET) {
		target->name = targetName;
		target->available = TRUE;
		target->gain = gain;
		target->location = location;
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

BOOL containsAvailableTarget() {
	int i;
	int size = targets.size;
	for (i = 0; i < size; i++) {
		GameTarget* target = targets.targets[i];
		if (target->available) {
			return TRUE;
		}	
	}
	return FALSE;
}

// DEBUG

void printGameTargetList(OutputStream* outputStream) {
	int i;
	int size = targets.size;
	println(outputStream);	
	for (i = 0; i < size; i++) {
		GameTarget* target = targets.targets[i];
		printGameTarget(outputStream, target, TRUE);
	}
}
