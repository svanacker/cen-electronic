#ifndef PID_MOTION_PROFIL_COMPUTER_H
#define PID_MOTION_PROFIL_COMPUTER_H

/** Acceleration phase / constant speed / Deceleration phase. */
#define PROFILE_TYPE_TRAPEZE 0

/** Type of trajectory in which we do not reach the max speed (=> acceleration phase, deceleration phase). */
#define PROFILE_TYPE_TRIANGLE 1

/**
 * Clear initial speeds to avoid that the trajectory finished
 * when we stop the robot.
 */
void clearInitialSpeeds();

void computeMotionInstruction(MotionInstruction* inst);

/**
 * Set the next Position that the robot must reach.
 * @param instructionIndex the index of which instruction to follow
 * @param motionType the type of motion which must be used
 * @param pidType the type of pid which must be used
 * @param pNextPosition can be either negative or positive
 * @param pa is the maximal absolute value of acceleration
 * @param pSpeedMax is the maximal absolute value of speed
 */
void setNextPosition(int instructionIndex,
        unsigned char motionType,
        unsigned char pidType,
        float pNextPosition,
        float pa,
        float pSpeedMax);


#endif
