#include "motionInstruction.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

// TODO : Move code into PIDComputer
#include "computer/pidComputer.h"

void clearMotionInstruction(MotionInstruction* motionInstruction) {
    motionInstruction->nextPosition = 0.0f;
    motionInstruction->a = 0.0f;
    motionInstruction->initialSpeed = 0.0f;
    motionInstruction->speed = 0.0f;
    motionInstruction->speedMax = 0.0f;
    motionInstruction->endSpeed = 0.0f;
    motionInstruction->t1 = 0.0f;
    motionInstruction->t2 = 0.0f;
    motionInstruction->t3 = 0.0f;
    motionInstruction->p1 = 0.0f;
    motionInstruction->p2 = 0.0f;
    // TODO : Define a profile "UNKNOWN"
    motionInstruction->profileType = PROFILE_TYPE_UNDEFINED;
    motionInstruction->motionParameterType = MOTION_PARAMETER_TYPE_UNDEFINED;
    motionInstruction->pidType = PID_TYPE_GO_INDEX;
}

void printMotionInstruction (OutputStream* outputStream, MotionInstruction* inst ) {
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
    appendProfileTypeAsString(outputStream, inst->profileType);
    appendCRLF(outputStream);

    // PidType
    appendString(outputStream, ",pidType=");
    appendPidTypeAsString(outputStream, inst->pidType);
    appendCRLF(outputStream);

    // MotionParameterType
    appendString(outputStream, ",motionType=");
    appendMotionParameterTypeAsString(outputStream, inst->motionParameterType);
    appendCRLF(outputStream);
     
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
