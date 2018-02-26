#ifndef PID_MOTION_H
#define PID_MOTION_H

#include <stdbool.h>

#include "parameters/pidGlobalParameters.h"
#include "pidComputationValues.h"
#include "motionInstruction.h"
#include "../../common/eeprom/eeprom.h"
#include "../extended/bspline.h"

struct PidMotion;
typedef struct PidMotion PidMotion;

struct PidMotionDefinition;
typedef struct PidMotionDefinition PidMotionDefinition;

/**
* Define the function used to compute Errors.
*/
typedef void ComputeUFunction(PidMotion* pidMotion,	PidMotionDefinition* motionDefinition);

/**
 * Store if the motion is a bspline curve or a classical (rotation / forward) move
 */
enum PidMotionType {
	/**
	* The type is not defined so that we could know if pidMotionDefinition is not defined.
	*/
	MOTION_TYPE_UNDEFINED,

	/**
	* Classical Move: rotation / forward
	*/
	MOTION_TYPE_NORMAL,

	/**
	* Use of BSpline.
	*/
	MOTION_TYPE_BSPLINE
};

/**
* Definition of motion. There can be more than one PidMotionDefinition, but only one active
* at a time.
*/
struct PidMotionDefinition {
	// To know if we must use MotionInstruction or BSplineCurve
	enum PidMotionType motionType;
	// Alpha / Theta
	MotionInstruction inst[INSTRUCTION_TYPE_COUNT];
	// When using BSPline
	BSplineCurve curve;
	/** The method which will compute the errors (by using coders or absolute positions) .*/
	ComputeUFunction* computeU;
	// OutputStream for notification so that caller could have it !
	OutputStream* notificationOutputStream;
};

/**
 * Global struct to make links between all structures and variables to achieve
 * motion with PID.
 * We use Circular Buffer like in buffer.c, to be able to push new trajectory, while we read and remove the current one
 */
struct PidMotion {
    // Parameters for all motions => INVARIANT.
    PidGlobalParameters globalParameters;
	// If false (default value), replace Motion Definition, if true stack All New Motion Definition
	bool stackMotionDefinitions;
	// Count the total motionDefinition
	unsigned int length;
	// read Index
	unsigned int readIndex;
	// write Index
	unsigned int writeIndex;
    // Contains the all motion Definitions;
	PidMotionDefinition(*motionDefinitions)[];
    // All current values (must be reset after each new move) => CHANGE EVERY TIME COMPUTATION
    PidComputationValues computationValues;
	// For persistence
	Eeprom* pidPersistenceEeprom;
	// Some parameters
	bool mustReachPosition;
	// Are we in rolling Test Mode
	bool rollingTestMode;
};


/**
* Returns if a pidMotion is initialized or not.
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return true if the pidMotion is initialized, false else
* @throws PID_MOTION_NULL if the pointer is NULL
*/
bool isPidMotionInitialized(const PidMotion* pidMotion);

/**
* Clears the pidMotion
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @throws PID_MOTION_NULL if the pointer is NULL
*/
void clearPidMotion(PidMotion* pidMotion);

/**
* Returns true if the pidMotion is full, false else.
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return true if the pidMotion is full, false else
* @throws PID_MOTION_NULL if the pointer is NULL
*/
bool isPidMotionFull(const PidMotion* pidMotion);

/**
* Returns true if the pidMotion is empty, false else.
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return true if the pidMotion is empty, false else
* @throws PID_MOTION_NULL if the pointer is NULL
*/
bool isPidMotionEmpty(const PidMotion* pidMotion);

/**
* Returns the number of elements.
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return the number of elements.
* @throws PID_MOTION_NULL if the pointer is NULL
*/
unsigned int getPidMotionElementsCount(const PidMotion* pidMotion);

/**
* Returns the total capacity to store Elements.
* As we use a circular buffer, we only store n - 1 elements (where n is the size of the array), and not n, because if we use n, we cannot distinguish when array is empty or full (if readIndex == writeIndex).
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return the total capacity to store Elements.
* @throws PID_MOTION_NULL if the pointer is NULL
*/
unsigned int getPidMotionCapacity(const PidMotion* pidMotion);

/**
* Get and result the first PidMotionDefinition inserted (FIFO Stack)..
* Shift the read array to the next PidMotionDefinition.
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return the the first PidMotionDefinition inserted (FIFO Stack).
* @throws PID_MOTION_NULL if the pointer is NULL
* @throws PID_MOTION_EMPTY if not enough PidMotionDefinition in the PidMotion object
*/
PidMotionDefinition* pidMotionReadMotionDefinition(PidMotion* pidMotion);

/**
* Get and result the current PidMotionDefinition 
* Does not shift to the next PidMotionDefinition.
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return NULL if there is no CurrentMotionDefinition, else the current PidMotionDefinition inserted.
* @throws PID_MOTION_NULL if the pointer is NULL
*/
PidMotionDefinition* pidMotionGetCurrentMotionDefinition(PidMotion* pidMotion);

/**
* Gets the new PidMotionDefinition in which we could write (FIFO buffer).
* @param pidMotion the pointer on pidMotion (simulates object programming)
* @return the next pid Motion Definition in which we have to write
* @throws PID_MOTION_NULL if the pointer is NULL
* @throws PID_MOTION_FULL if not enough space
*/
PidMotionDefinition* pidMotionGetNextToWritePidMotionDefinition(PidMotion* pidMotion);

/**
* Returns the motion definition with a specified index.
*/
PidMotionDefinition* getMotionDefinition(PidMotion* pidMotion, unsigned int index);

// MODE STACK OR REPLACE

/**
* Set the motion mode in ADDING Mode (All new motion instructions are stacked).
*/
void setMotionModeAdd(PidMotion* pidMotion);

/**
* Set the motion mode in REPLACE Mode (All new motion instruction replace the current one).
*/
void setMotionModeReplace(PidMotion* pidMotion);

/**
 * Returns if we stack (true) or not replace (false) the motion definitions.
 */
bool isStackMotionDefinitions(PidMotion* pidMotion);

// MOTION PARAMETER

/**
* Returns the parameters of the end motion.
*/
MotionEndDetectionParameter* getMotionEndDetectionParameter(PidMotion* pidMotion);

// INIT

/**
 * Initializes the Pid Motion global structure.
 * @param pidMotion the pointer to the structure to initialize
 * @param eepromParam the param to the eeprom
 * @param array the array with all motion definition
 * @param length the length of the array with motion definitions
 */
void initPidMotion(PidMotion* pidMotion, Eeprom* eepromParam, PidMotionDefinition(*array)[], unsigned int length);

#endif

