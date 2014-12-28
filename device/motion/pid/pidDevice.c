#include "pidDevice.h"
#include "pidDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/error/error.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/device.h"
#include "../../../motion/pid/pid.h"
#include "../../../motion/pid/motionEndDetection.h"
#include "../../../motion/pid/pidPersistence.h"

bool isPIDDeviceOk(void) {
    return 1;
}

void devicePIDHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_WRITE_PID) {
        // send acknowledge
        appendAck(outputStream);
        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);

        // PID Value => 2..9 char index
        float p = (float) readHex2(inputStream);
        float i = (float) readHex2(inputStream);
        float d = (float) readHex2(inputStream);
        float maxI = (float) readHex2(inputStream);


        if (pidIndex >= 0 && pidIndex < PID_COUNT) {
            setPID(pidIndex - 1, p, i, d, maxI);
            savePID();
        } else {
            // All Values
            if (pidIndex == -1) {
                int pidIndex2;
                for (pidIndex2 = 0; pidIndex2 < PID_COUNT; pidIndex2++) {
                    setPID(pidIndex2, p, i, d, maxI);
                }
                savePID();
            } else {
                writeError(PID_INDEX_INCORRECT);
            }
        }
        append(outputStream, PID_DEVICE_HEADER);
        append(outputStream, COMMAND_WRITE_PID);
    } else if (header == COMMAND_READ_PID) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_READ_PID);

        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);

        // we test all pid value (test mode included)
        Pid* localPid = getPID(pidIndex, 0);
        appendHex2(outputStream, pidIndex);
        appendHex2(outputStream, (int) localPid->p);
        appendHex2(outputStream, (int) localPid->i);
        appendHex2(outputStream, (int) localPid->d);
        appendHex2(outputStream, (int) localPid->maxIntegral);
    }
    // End Detection Parameter
    else if (header ==  COMMAND_GET_END_DETECTION_PARAMETER) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter();
        appendHex2(outputStream, motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold);
        appendHex2(outputStream, motionEndDetectionParameter->maxUIntegralFactorThreshold);
        appendHex2(outputStream, motionEndDetectionParameter->maxUIntegralConstantThreshold);
        appendHex2(outputStream, motionEndDetectionParameter->timeRangeAnalysis);
        appendHex2(outputStream, motionEndDetectionParameter->noAnalysisAtStartupTime);
    }
    else if (header ==  COMMAND_SET_END_DETECTION_PARAMETER) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter();

        motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = (unsigned char) readHex2(inputStream);
        motionEndDetectionParameter->maxUIntegralFactorThreshold = (unsigned char) readHex2(inputStream);
        motionEndDetectionParameter->maxUIntegralConstantThreshold = (unsigned char) readHex2(inputStream);
        motionEndDetectionParameter->timeRangeAnalysis = (unsigned char) readHex2(inputStream);
        motionEndDetectionParameter->noAnalysisAtStartupTime = (unsigned char) readHex2(inputStream);
    }
    // Debug : _01001-0002005678-4000200050008000
    else if (header ==  COMMAND_SEND_DEBUG_DATA_PID) {
        int instructionIndex = readHex(inputStream);

        PidMotion* pidMotion = getPidMotion();
        PidComputationValues* computationValues = &(pidMotion->computationValues);

        MotionError* localError = &(computationValues->err[instructionIndex]);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_SEND_DEBUG_DATA_PID);

        appendHex(outputStream, instructionIndex);
        appendHex3(outputStream, getPidTime());
        // TODO : pidType
        appendHex(outputStream, 0);

        appendSeparator(outputStream);

        Motion* localMotion = &(computationValues->motion[instructionIndex]);
        appendHex5(outputStream, (int) localMotion->position);

        appendSeparator(outputStream);

        appendHex4(outputStream, (int) localError->error);

        appendSeparator(outputStream);

        appendHex2(outputStream, (int) localMotion->u);

        appendSeparator(outputStream);

        MotionEndInfo* motionEnd = &(computationValues->motionEnd[instructionIndex]);
        appendHex4(outputStream, motionEnd->integralTime);
        appendHex4(outputStream, (int) motionEnd->absDeltaPositionIntegral);
        appendHex4(outputStream, (int) motionEnd->absUIntegral);
    }
    else if (header == COMMAND_SEND_MOTION_PARAMETER) {
        int instructionIndex = readHex(inputStream);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_SEND_MOTION_PARAMETER);

        PidMotion* pidMotion = getPidMotion();
        PidMotionDefinition* motionDefinition = &(pidMotion->currentMotionDefinition);
        MotionInstruction* localInst = &(motionDefinition->inst[instructionIndex]);
        appendHex(outputStream, instructionIndex);
        appendHex2(outputStream, (int) localInst->a);
        appendHex2(outputStream, (int) localInst->speed);
        appendHex2(outputStream, (int) localInst->speedMax);
        
        appendSeparator(outputStream);

        appendHex3(outputStream, (int) localInst->t1);
        appendHex3(outputStream, (int) localInst->t2);
        appendHex3(outputStream, (int) localInst->t3);
        
        appendSeparator(outputStream);

        appendHex5(outputStream, (int) localInst->p1);
        appendHex5(outputStream, (int) localInst->p2);

        appendSeparator(outputStream);

        appendHex(outputStream, localInst->profileType);
        appendHex(outputStream, localInst->motionType);
        appendHex(outputStream, localInst->pidType);
    }    
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initPID,
    .deviceShutDown = &stopPID,
    .deviceIsOk = &isPIDDeviceOk,
    .deviceHandleRawData = &devicePIDHandleRawData,
};

DeviceDescriptor* getPIDDeviceDescriptor() {
    return &descriptor;
}
