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

#include "../../motion/simple/motion.h"
#include "../../motion/simple/motionParameterType.h"

void printErrorStruct (OutputStream* outputStream, int index ) {
    // TODO 
    /*
    MotionError* localErr = getMotionError(index);

    appendStringAndDecf(outputStream, "pe=", localErr->previousError);
    appendStringAndDecf(outputStream, ",e=", localErr->error);
    appendStringAndDecf(outputStream, ",de=", localErr->derivativeError);
    appendStringAndDecf(outputStream, "ie=", localErr->integralError);
    println(outputStream);
    */
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

void printInst (OutputStream* outputStream, MotionInstruction* inst ) {
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
    appendProfileTypeAsString(inst->profileType, outputStream);
    appendCRLF(outputStream);

    // PidType
    appendString(outputStream, ",pidType=");
    appendPidTypeAsString(inst->pidType, outputStream);
    appendCRLF(outputStream);

    // MotionParameterType
    appendString(outputStream, ",motionType=");
    appendMotionParameterTypeAsString(inst->motionParameterType, outputStream);
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


