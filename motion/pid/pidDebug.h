#ifndef PID_DEBUG_H
#define PID_DEBUG_H

#include "pid.h"

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"

/**
* Print the error struct of the index.
* @param errorIndex INSTRUCTION_THETA_INDEX / INSTRUCTION_ALPHA_INDEX
*/
void printErrorStruct (OutputStream* outputStream, MotionError* motionError);

/**
 * Print the content of pid motion.
 */
void printPidMotion(OutputStream* outputStream);

/**
* Print the motion struct of the index.
* @param motionIndex INSTRUCTION_THETA_INDEX / INSTRUCTION_ALPHA_INDEX
*/
void printMotionStruct (OutputStream* outputStream,  int motionIndex );

/**
* Print the instruction struct of the index.
*/
void printInst (OutputStream* outputStream, MotionInstruction * inst );

/**
* Print a simulation of trajectory to an outputStream
*/
void printTrajectory(OutputStream* outputStream,  MotionInstruction* instruction, float maxPidTime);

void printPid(OutputStream* outputStream, int pidIndex);

void printAllPids(OutputStream* outputStream);

#endif
