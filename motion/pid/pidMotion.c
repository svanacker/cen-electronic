#include "pidMotion.h"

#include "../../common/error/error.h"

// Contains all information about current motion (singleton)
static PidMotion pidMotion;

PidMotion* getPidMotion(void) {
    return &pidMotion;
}

void setMotionModeAdd(void) {
	pidMotion.stackMotionDefinitions = true;
}

void setMotionModeReplace(void) {
	pidMotion.stackMotionDefinitions = false;
}

bool isStackMotionDefinitions(void) {
	return pidMotion.stackMotionDefinitions;
}

PidMotionDefinition* getCurrentMotionDefinition(void) {
	return &(pidMotion.motionDefinitions[0]);
}

/**
* Returns the motion definition with a specified index
*/
PidMotionDefinition* getMotionDefinition(unsigned int index) {
	// TODO : Check array bounds
	return &(pidMotion.motionDefinitions[index]);
}

/**
* Returns how many motion definition are stored.
*/
unsigned int getMotionDefinitionCount(void) {
	return pidMotion.motionDefinitionCount;
}

/*
PidMotionDefinition* removeCurrentMotionDefinition(void) {
	if (pidMotion.motionDefinitionCount > 0) {
		pidMotion.motionDefinitionCount--;
	}
}
*/

PidMotionDefinition* getNextMotionDefinition(void) {
	int index = 0;
	// If we stack
	if (isStackMotionDefinitions()) {
		// we check that the list is not full
		if (pidMotion.motionDefinitionCount >= NEXT_MOTION_DEFINITION_COUNT) {
			writeError(MOTION_DEFINITION_LIST_FULL);
			// We return the same pidMotion to avoid to get Null Pointer Exception if we returns NULL
			return &(pidMotion.motionDefinitions[index]);
		}
		// Compute index
		index = pidMotion.motionDefinitionCount;
		pidMotion.motionDefinitionCount++;
	}
	return &(pidMotion.motionDefinitions[index]);
}

void initPidMotion(void) {
	// We have always a motion ???
	pidMotion.motionDefinitionCount = 1;
    initMotionEndParameter(getMotionEndDetectionParameter());
	PidMotionDefinition* motionDefinition = getCurrentMotionDefinition();
    initFirstTimeBSplineCurve(&(motionDefinition->curve));
}