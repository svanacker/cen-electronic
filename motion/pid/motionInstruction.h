#ifndef MOTION_INSTRUCTION_H
#define MOTION_INSTRUCTION_H

#include "../../common/io/outputStream.h"

#include "profile/profileType.h"
#include "pidType.h"
#include "../../motion/parameters/motionParameterType.h"

/**
 * Defines the structs which stores the instruction.
 */
typedef struct MotionInstruction {
    /** the position which must be reached when using classic implementation */
    float nextPosition;
    /** The acceleration which is asked : > 0 */
    float a;
    /** The initial speed. */
    float initialSpeed;
    /** The maximal speed which is asked : > 0 */
    float speed;
    /** The maximal speed which can be reached : negative or positive */
    float speedMax;
    /** The target end Speed (decelerationTime). */
    float endSpeed;
    /** The acceleration time > 0 */
    float t1;
    /** The time before deceleration > 0 */
    float t2;
    /** The time after deceleration > 0 */
    float t3;
    /** The first position after acceleration time */
    float p1;
    /** The first position after speed constant */
    float p2;
    /** The type of the trajectory (TRAPEZE / TRIANGLE) */
    enum ProfileType profileType;
    /** The type of MotionParameterType (GO, ROTATION, MAINTAIN_POSITION). */
    enum MotionParameterType motionParameterType;
    /** The type of pid which must be used. */
    enum PidType pidType;
} MotionInstruction;

/**
 * Clear the motion Instruction data
 * @param motionInstruction
 */
void clearMotionInstruction(MotionInstruction* motionInstruction);

/**
* Print the instruction struct of the index.
*/
void printMotionInstruction(OutputStream* outputStream, MotionInstruction* inst);

/**
* Print a simulation of trajectory to an outputStream
*/
void printTrajectory(OutputStream* outputStream, MotionInstruction* instruction, float maxPidTime);

#endif
