#include "pidDevice.h"
#include "pidDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/error/error.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"
#include "../../../common/io/stream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/device.h"
#include "../../../motion/pid/pid.h"
#include "../../../motion/pid/motionEndDetection.h"
#include "../../../motion/pid/pidPersistence.h"

BOOL isPIDDeviceOk(void) {
    return 1;
}

void devicePIDHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_WRITE_PID) {
        // send acquittement
        appendAck(outputStream);
        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);

        // PID Value => 2..9 char index
        float p = readHex2(inputStream);
        float i = readHex2(inputStream);
        float d = readHex2(inputStream);
        float maxI = readHex2(inputStream);


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
        append(outputStream, COMMAND_WRITE_PID);
    } else if (header == COMMAND_READ_PID) {
        // send acknowledgement
        appendAck(outputStream);
        append(outputStream, COMMAND_READ_PID);

        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);

        // we test all pid value (test mode included)
        Pid* localPid = getPID(pidIndex, 0);
		appendHex2(outputStream, pidIndex);
        appendHex2(outputStream, localPid->p);
        appendHex2(outputStream, localPid->i);
        appendHex2(outputStream, localPid->d);
        appendHex2(outputStream, localPid->maxIntegral);
    }
	// End Detection Parameter
	else if (header ==  COMMAND_GET_END_DETECTION_PARAMETER) {
		// send acknowledgement
        appendAck(outputStream);
        append(outputStream, COMMAND_GET_END_DETECTION_PARAMETER);

		MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter();
		appendHex2(outputStream, motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold);
		appendHex2(outputStream, motionEndDetectionParameter->maxUIntegralFactorThreshold);
		appendHex2(outputStream, motionEndDetectionParameter->maxUIntegralConstantThreshold);
		appendHex2(outputStream, motionEndDetectionParameter->timeRangeAnalysis);
		appendHex2(outputStream, motionEndDetectionParameter->noAnalysisAtStartupTime);
	}
	else if (header ==  COMMAND_SET_END_DETECTION_PARAMETER) {
		// send acknowledgement
        appendAck(outputStream);
        append(outputStream, COMMAND_GET_END_DETECTION_PARAMETER);

		MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter();

		motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = (float) readHex2(inputStream);
		motionEndDetectionParameter->maxUIntegralFactorThreshold = (float) readHex2(inputStream);
		motionEndDetectionParameter->maxUIntegralConstantThreshold = (float) readHex2(inputStream);
		motionEndDetectionParameter->timeRangeAnalysis = readHex2(inputStream);
		motionEndDetectionParameter->noAnalysisAtStartupTime = readHex2(inputStream);
	}
	// Debug : _01001-0002005678-4000200050008000
	else if (header ==  COMMAND_SEND_DEBUG_DATA_PID) {
		int instructionIndex = readHex(inputStream);

		PidMotion* pidMotion = getPidMotion();
		PidComputationValues* computationValues = &(pidMotion->computationValues);

		MotionError* localError = &(computationValues->err[instructionIndex]);

		// send acknowledgement
        appendAck(outputStream);
        append(outputStream, COMMAND_SEND_DEBUG_DATA_PID);

		appendHex(outputStream, instructionIndex);
		appendHex3(outputStream, getPidTime());
		// TODO : pidType
		appendHex(outputStream, 0);

		appendSeparator(outputStream);

		Motion* localMotion = &(computationValues->motion[instructionIndex]);
		appendHex5(outputStream, localMotion->position);

		appendSeparator(outputStream);

		appendHex4(outputStream, localError->error);

		appendSeparator(outputStream);

		appendHex2(outputStream, localMotion->u);

		appendSeparator(outputStream);

		MotionEndInfo* motionEnd = &(computationValues->motionEnd[instructionIndex]);
		appendHex4(outputStream, motionEnd->integralTime);
		appendHex4(outputStream, motionEnd->absDeltaPositionIntegral);
		appendHex4(outputStream, motionEnd->absUIntegral);
	}
	else if (header == COMMAND_SEND_MOTION_PARAMETER) {
		int instructionIndex = readHex(inputStream);

		// send acknowledgement
        appendAck(outputStream);
        append(outputStream, COMMAND_SEND_MOTION_PARAMETER);

		PidMotion* pidMotion = getPidMotion();
		PidMotionDefinition* motionDefinition = &(pidMotion->currentMotionDefinition);
		MotionInstruction* localInst = &(motionDefinition->inst[instructionIndex]);
		appendHex(outputStream, instructionIndex);
		appendHex2(outputStream, localInst->a);
		appendHex2(outputStream, localInst->speed);
		appendHex2(outputStream, localInst->speedMax);
		
		appendSeparator(outputStream);

		appendHex3(outputStream, localInst->t1);
		appendHex3(outputStream, localInst->t2);		
		appendHex3(outputStream, localInst->t3);
		
		appendSeparator(outputStream);

		appendHex5(outputStream, localInst->p1);
		appendHex5(outputStream, localInst->p2);		

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
