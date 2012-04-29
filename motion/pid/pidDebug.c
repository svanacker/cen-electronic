#include "pid.h"
#include "pidMotionProfileComputer.h"
#include "pidComputer.h"

#include "../../common/commons.h"
#include "../../common/eeprom/eeprom.h"
#include "../../common/math/cenMath.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../motion/simple/motion.h"

void printErrorStruct (OutputStream* outputStream, int index ) {
	MotionError * localErr = getMotionError(index);

	appendStringAndDecf(outputStream, "pe=", localErr->previousError);
	appendStringAndDecf(outputStream, ",e=", localErr->error);
	appendStringAndDecf(outputStream, ",de=", localErr->derivativeError);
	appendStringAndDecf(outputStream, "ie=", localErr->integralError);
	println(outputStream);
}

void printMotionStruct (OutputStream* outputStream, int index) {
	// TODO
	println(outputStream);
}

void printPid(OutputStream* outputStream, int pidIndex) {
	unsigned char rollingTestMode = getRollingTestMode();
	Pid* localPid= getPID(pidIndex, rollingTestMode);

	appendStringAndDecf(outputStream, "p=", localPid->p);
	appendStringAndDecf(outputStream, ",i=", localPid->i);
	appendStringAndDecf(outputStream, ",d=", localPid->d);
	appendStringAndDecf(outputStream, ",mi=", localPid->maxIntegral);

	println(outputStream);
}

void printAllPids(OutputStream* outputStream) {
	int i;
	int pidCount = PID_COUNT;
	for (i = 0; i < pidCount; i++) {
		appendDec(outputStream, i);
		append(outputStream, ':');
		printPid(outputStream, i);
	}
}

void printInst (OutputStream* outputStream, MotionInstruction * inst ) {
	appendStringAndDecf(outputStream, "nextPos=", inst->nextPosition);
	appendStringAndDecf(outputStream, ",a=", inst->a);
	appendStringAndDecf(outputStream, ",s=", inst->speed);
	appendStringAndDecf(outputStream, ",sMax=", inst->speedMax);
	appendStringAndDecf(outputStream, ",si=", inst->initialSpeed);
	appendStringAndDecf(outputStream, ",se=", inst->endSpeed);
	appendStringAndDecf(outputStream, ",t1=", inst->t1);
	appendStringAndDecf(outputStream, ",t2=", inst->t2);
	appendStringAndDecf(outputStream, ",t3=", inst->t3);
	appendStringAndDecf(outputStream, ",p1=", inst->p1);
	appendStringAndDecf(outputStream, ",p2=", inst->p2);

	// ProfileType
	appendString(outputStream, ",profileType=");
	if (inst->profileType == PROFILE_TYPE_TRIANGLE) {
		appendString(outputStream, "TRI");
	}
	else if (inst->profileType == PROFILE_TYPE_TRAPEZE) {
		appendString(outputStream, "TRA");
	}
	else {
		append(outputStream, '?');
	}
	// PidType
	const char* pidTypeAsString;
	if (inst->pidType == PID_TYPE_GO_INDEX) {
		pidTypeAsString = "GO";
	}
	else if (inst->pidType == PID_TYPE_ROTATE_INDEX) {
		pidTypeAsString = "ROTATE";
	}
	else if (inst->pidType == PID_TYPE_MAINTAIN_POSITION_INDEX) {
		pidTypeAsString = "MAINTAIN";
	}
	else if (inst->pidType == PID_TYPE_ADJUST_DIRECTION) {
		pidTypeAsString = "ADJUST_DIR";
	}
	else if (inst->pidType == PID_TYPE_FINAL_APPROACH_INDEX) {
		pidTypeAsString = "FINAL_APPROACH";
	}
	appendKeyAndName(outputStream, ",pidType=", pidTypeAsString);

	// MotionType
	const char* motionTypeAsString;
	if (inst->motionType == MOTION_TYPE_FORWARD_OR_BACKWARD) {
		motionTypeAsString = "FOR_OR_BACK";
	}
	else if (inst->motionType == MOTION_TYPE_ROTATION) {
		motionTypeAsString = "ROT";
	}
	else if (inst->motionType == MOTION_TYPE_MAINTAIN_POSITION) {
		motionTypeAsString = "MAINT";
	}
	appendKeyAndName(outputStream, ",motionType=", motionTypeAsString);
 		
	// unsigned pidIndex = getIndexOfPid(index, inst->pidType);
	// printPid(outputStream, pidIndex);

	println(outputStream);
}

/**
 * Print a trajectory from a Motion Instruction with a maxPidTime
 */
void printTrajectory(OutputStream* outputStream,  MotionInstruction* instruction, float maxPidTime) {
	float pidTime;
	for (pidTime = 0.0f; pidTime < maxPidTime; pidTime += maxPidTime / 50.0f) {
		float normalSpeed = computeNormalSpeed(instruction, pidTime);
		float normalPosition = computeNormalPosition(instruction, pidTime);
		appendDecf(outputStream, pidTime);
		appendString(outputStream, ",");
		appendDecf(outputStream, normalSpeed);
		appendString(outputStream, ",");
		appendDecf(outputStream, normalPosition);
		appendCRLF(outputStream);
	}
}


