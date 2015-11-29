#ifndef PID_MOTION_H
#define PID_MOTION_H

#include "parameters/pidGlobalParameters.h"
#include "pidMotionDefinition.h"
#include "pidComputationValues.h"

// NUMBER OF NEXT_MOTION_DEFINITION_COUNT

#define NEXT_MOTION_DEFINITION_COUNT 2

/**
 * Global struct to make links between all structures and variables to achieve
 * motion with PID.
 */
typedef struct PidMotion {
    // Parameters for all motions => INVARIANT.
    PidGlobalParameters globalParameters;
	// If false (default value), replace Motion Definition, if true stack All New Motion Definition
	bool stackMotionDefinitions;
	// Count the total motionDefinition
	int motionDefinitionCount;
    // Contains the next Motion Definition;
    PidMotionDefinition motionDefinitions[NEXT_MOTION_DEFINITION_COUNT];
    // All current values (must be reset after each new move) => CHANGE EVERY TIME COMPUTATION
    PidComputationValues computationValues;
} PidMotion;

/**
 * Returns the current pidMotion.
 */
PidMotion* getPidMotion(void);

/**
 * Get the current Motion Definition, as we use array for implementation, is the first item of the array
 */
PidMotionDefinition* getCurrentMotionDefinition(void);

/**
* Remove the current motion definition, and returns the next one
*/
PidMotionDefinition* removeCurrentMotionDefinition(void);

/**
* Get the next pid Motion Definition to fill. Depend if we are in stack or replace mode.
*/
PidMotionDefinition* getNextMotionDefinition(void);

/**
* Set the motion mode in ADDING Mode (All new motion instructions are stacked).
*/
void setMotionModeAdd(void);

/**
* Set the motion mode in REPLACE Mode (All new motion instruction replace the current one).
*/
void setMotionModeReplace(void);

/**
 * Returns if we stack (true) or not replace (false) the motion definitions.
 */
bool isStackMotionDefinitions(void);

/**
 * Initializes the Pid Motion global structure.
 */
void initPidMotion(void);

#endif

