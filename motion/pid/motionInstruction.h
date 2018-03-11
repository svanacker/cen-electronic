#ifndef MOTION_INSTRUCTION_H
#define MOTION_INSTRUCTION_H

#include "../../common/io/outputStream.h"

#include "profile/profileType.h"
#include "pidType.h"
#include "../../motion/parameters/motionParameterType.h"

/**
 * Defines the structure which stores the instruction.
 */
typedef struct MotionInstruction {
    /** the position which must be reached when using classic implementation */
    float nextPosition;
    /** The acceleration which is requested : > 0, in mm / sec^2 */
    float a;
    /** The initial speed in mm / sec. */
    float initialSpeed;
    /** The maximal speed which is requested : > 0 : in mm / sec */
    float speed;
    /** The maximal speed which can be reached : negative or positive : in mm / sec */
    float speedMax;
    /** The target end Speed (decelerationTime). : in mm / sec */
    float endSpeed;
    /** The acceleration time > 0 : in second */
    float t1;
    /** The time before deceleration > 0 : in second */
    float t2;
    /** The time after deceleration > 0 : in second */
    float t3;
    /** The first position after acceleration time */
    float p1;
    /** The first position after speed constant */
    float p2;
    /** The type of the trajectory (TRAPEZE / TRIANGLE) */
    enum ProfileType profileType;
    /** The type of MotionParameterType (GO, ROTATION, MAINTAIN_POSITION). */
    enum MotionParameterType motionParameterType;
    /** The type of pid which must be used (for the beginning). */
    enum PidType initialPidType;
} MotionInstruction;

/**
 * Clear the motion Instruction data.
 * @param motionInstruction the motion instruction to clear
 */
void clearMotionInstruction(MotionInstruction* motionInstruction);

#endif
