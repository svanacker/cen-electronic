#include "pidMotion.h"

#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"
#include "../../common/error/error.h"
#include "../../robot/kinematics/robotKinematics.h"
#include "../../robot/kinematics/robotKinematicsPersistence.h"

#include "pidTimer.h"
#include "parameters/pidParameterPersistence.h"
#include "pidComputationValues.h"
#include "../../motion/parameters/motionParameterPersistence.h"

bool checkPidMotionNotNull(const PidMotion* pidMotion) {
	if (pidMotion == NULL) {
		writeError(PID_MOTION_NULL);
		return false;
	}
	return true;
}

bool isPidMotionInitialized(const PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return false;
	}
	return pidMotion->motionLength > 0;
}

void clearPidMotionDefinition(PidMotionDefinition* pidMotionDefinition) {
    pidMotionDefinition->motionType = MOTION_TYPE_UNDEFINED;
    pidMotionDefinition->computeU = NULL;
    pidMotionDefinition->notificationOutputStream = NULL;
    pidMotionDefinition->state = PID_MOTION_DEFINITION_STATE_UNDEFINED;
}

void clearPidMotion(PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return;
	}
	pidMotion->motionWriteIndex = 0;
	pidMotion->motionReadIndex = 0;
	unsigned int i;

    PidMotionDefinition* pidMotionDefinition = (PidMotionDefinition*)pidMotion->motionDefinitions;
	
	// Reinit all values to make the Debug more easy
	for (i = 0; i < pidMotion->motionLength; i++) {
        clearPidMotionDefinition(pidMotionDefinition);
        pidMotionDefinition++;
	}
    
    clearPidComputationValues(&(pidMotion->computationValues));
}

bool isPidMotionFull(const PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return false;
	}
	return ((pidMotion->motionWriteIndex + 1) % pidMotion->motionLength) == pidMotion->motionReadIndex;
}

bool isPidMotionEmpty(const PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return true;
	}
	return pidMotion->motionReadIndex == pidMotion->motionWriteIndex;
}

unsigned int getPidMotionElementsCount(const PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return 0;
	}
	int result = pidMotion->motionWriteIndex - pidMotion->motionReadIndex;
	if (result < 0) {
		result += pidMotion->motionLength;
	}
	return result;
}

unsigned int getPidMotionCapacity(const PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return 0;
	}
	return pidMotion->motionLength - 1;
}

PidMotionDefinition* pidMotionReadMotionDefinition(PidMotion* pidMotion, bool errorIfEndOfList) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return NULL;
	}
	bool isEmpty = isPidMotionEmpty(pidMotion);
	if (!isEmpty) {
		PidMotionDefinition* result = (PidMotionDefinition*)pidMotion->motionDefinitions;
		// Shift to the right cell index
		result += pidMotion->motionReadIndex;

		pidMotion->motionReadIndex++;
		pidMotion->motionReadIndex %= pidMotion->motionLength;
		return result;
	}
	else {
        if (errorIfEndOfList) {
            // We must log the problem
            writeError(PID_MOTION_EMPTY);
        }
		return NULL;
	}
}

PidMotionDefinition* pidMotionGetNextToWritePidMotionDefinition(PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return NULL;
	}
	// If we stack or if the pidMotion is Empty, we add a new definition !
	if (pidMotion->stackMotionDefinitions || isPidMotionEmpty(pidMotion)) {
		bool isFull = isPidMotionFull(pidMotion);
		if (!isFull) {
			PidMotionDefinition* result = (PidMotionDefinition*)pidMotion->motionDefinitions;
			// Shift to the right cell index
			result += pidMotion->motionWriteIndex;
			// For next time
			pidMotion->motionWriteIndex++;
			pidMotion->motionWriteIndex %= pidMotion->motionLength;
			return result;
		}
		else {
			// We must log the problem
			writeError(PID_MOTION_FULL);
			return NULL;
		}
	}
    // We overwrite on the read Index
    PidMotionDefinition* result = (PidMotionDefinition*)pidMotion->motionDefinitions;
    // Shift to the right cell index
    result += pidMotion->motionReadIndex;
    // We overwrite the writeIndex to the next one to avoid inconsistency
    pidMotion->motionWriteIndex = (pidMotion->motionReadIndex + 1) % pidMotion->motionLength;

    return result;
}

PidMotionDefinition* pidMotionGetCurrentMotionDefinition(PidMotion* pidMotion) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return NULL;
	}
	unsigned int size = getPidMotionElementsCount(pidMotion);
	if (size <= 0) {
        return NULL;
    }
    PidMotionDefinition* result = (PidMotionDefinition*)pidMotion->motionDefinitions;
    // Shift to the right cell index
    result += pidMotion->motionReadIndex;
    return result;
}

PidMotionDefinition* getMotionDefinition(PidMotion* pidMotion, unsigned int index) {
	unsigned int size = getPidMotionElementsCount(pidMotion);
	if (index < size) {
		PidMotionDefinition* result = (PidMotionDefinition*)pidMotion->motionDefinitions;
		// Shift to the right cell index
		result += ((pidMotion->motionReadIndex + index) % pidMotion->motionLength);

		return result;
	}
	else {
		// We must log the problem
		writeError(PID_MOTION_NOT_ENOUGH_DATA);
	}
	return NULL;
}

// STACK / REPLACE MODE

void setMotionModeAdd(PidMotion* pidMotion) {
	pidMotion->stackMotionDefinitions = true;
}

void setMotionModeReplace(PidMotion* pidMotion) {
	pidMotion->stackMotionDefinitions = false;
}

bool isStackMotionDefinitions(PidMotion* pidMotion) {
	return pidMotion->stackMotionDefinitions;
}

// MOTION PARAMETERS

MotionEndDetectionParameter* getMotionEndDetectionParameter(PidMotion* pidMotion) {
	return &(pidMotion->globalParameters.motionEndDetectionParameter);
}

// INIT

void initPidMotion(PidMotion* pidMotion, 
                   DualHBridgeMotor* dualHBridgeMotor,
                   Eeprom* _eeprom,
                   PidMotionDefinition(*array)[],
                   unsigned int length) {
	if (!checkPidMotionNotNull(pidMotion)) {
		return;
	}
    if (_eeprom == NULL) {
        writeError(EEPROM_NULL);
        return;
    }
    pidMotion->dualHBridgeMotor = dualHBridgeMotor;
	pidMotion->motionDefinitions = array;
	pidMotion->motionLength = length;
	pidMotion->pidPersistenceEeprom = _eeprom;

	// We load the values from the eeprom, but we don't load default values unless the eeprom is a memory type
	loadPidParameters(pidMotion, _eeprom->eepromType == EEPROM_TYPE_MEMORY);

    if (_eeprom->eepromType == EEPROM_TYPE_MEMORY) {
        loadPidParameters(pidMotion, true);
        // We store to do as it was already previously store !
        savePidParameters(pidMotion);
    }
    else {
        loadPidParameters(pidMotion, false);
    }
    // Load the kinematics by calling the singleton
	getRobotKinematics();
    
	initPidTimer();
}

