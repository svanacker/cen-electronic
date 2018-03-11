#include <stdbool.h>

#include "pidDevice.h"
#include "pidDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"
#include "../../../common/eeprom/eeprom.h"
#include "../../../common/error/error.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/device.h"

#include "../../../motion/motion.h"
#include "../../../motion/parameters/motionParameter.h"
#include "../../../motion/parameters/motionParameterPersistence.h"
#include "../../../motion/pid/pid.h"
#include "../../../motion/pid/parameters/pidParameter.h"
#include "../../../motion/pid/pidMotion.h"
#include "../../../motion/pid/pidComputationValues.h"
#include "../../../motion/pid/motionInstruction.h"
#include "../../../motion/pid/pidComputationInstructionValues.h"
#include "../../../motion/pid/endDetection/motionEndDetection.h"
#include "../../../motion/pid/parameters/pidParameterPersistence.h"

static PidMotion* pidMotion;

bool isPidDeviceOk(void) {
    return true;
}

void initPidDevice(void) {
}

void stopPidDevice(void) {

}

void devicePidHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // MOTION PARAMETERS
    if (commandHeader == COMMAND_GET_MOTION_PARAMETERS) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_MOTION_PARAMETERS);
        enum MotionParameterType motionParameterType = (enum MotionParameterType) readHex2(inputStream);

        MotionParameter* motionParameter = getMotionParameters(motionParameterType);
        appendHexFloat4(outputStream, motionParameter->a, 0);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, motionParameter->speed, 0);

    } else if (commandHeader == COMMAND_SET_MOTION_PARAMETERS) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_SET_MOTION_PARAMETERS);
        enum MotionParameterType motionParameterType = (enum MotionParameterType) readHex2(inputStream);
        checkIsSeparator(inputStream);
        float a = readHexFloat4(inputStream, 0);
        checkIsSeparator(inputStream);
        float speed = readHexFloat4(inputStream, 0);

        MotionParameter* motionParameter = getMotionParameters(motionParameterType);
        motionParameter->a = a;
        motionParameter->speed = speed;
    }
    else if (commandHeader == COMMAND_GET_PID_PARAMETERS) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_PID_PARAMETERS);

        // PID Index => 0..n char index
        unsigned int pidIndex = readHex2(inputStream);

        // we test all pid value (test mode included)
        PidParameter* localPidParameter = getPidParameterByIndex(pidMotion, pidIndex);
        appendHex2(outputStream, pidIndex);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->p, PID_VALUE_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->i, PID_VALUE_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->d, PID_VALUE_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->maxIntegral, PID_VALUE_DIGIT_PRECISION);
    // PID PARAMETERS
    }
    else if (commandHeader == COMMAND_GET_PID_PARAMETERS) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_PID_PARAMETERS);

        // PID Index => 0..n char index
        unsigned int pidIndex = readHex2(inputStream);

        // we test all pid value (test mode included)
        PidParameter* localPidParameter = getPidParameterByIndex(pidMotion, pidIndex);
        appendHex2(outputStream, pidIndex);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->p, PID_VALUE_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->i, PID_VALUE_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->d, PID_VALUE_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localPidParameter->maxIntegral, PID_VALUE_DIGIT_PRECISION);
    }
    else if (commandHeader == COMMAND_SET_PID_PARAMETERS) {
        // PID Index
        char pidIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        // PID Values
        float p = readHexFloat4(inputStream, PID_VALUE_DIGIT_PRECISION);
        checkIsSeparator(inputStream);
        float i = readHexFloat4(inputStream, PID_VALUE_DIGIT_PRECISION);
        checkIsSeparator(inputStream);
        float d = readHexFloat4(inputStream, PID_VALUE_DIGIT_PRECISION);
        checkIsSeparator(inputStream);
        float maxI = readHexFloat4(inputStream, PID_VALUE_DIGIT_PRECISION);

        if (pidIndex >= 0 && pidIndex < PID_TYPE_COUNT) {
            setPidParameter(pidMotion, pidIndex, p, i, d, maxI);
        } else {
            // All Values
            if (pidIndex == -1) {
                unsigned int pidIndex2;
                for (pidIndex2 = 0; pidIndex2 < PID_TYPE_COUNT; pidIndex2++) {
                    setPidParameter(pidMotion, pidIndex2, p, i, d, maxI);
                }
            } else {
                writeError(PID_INDEX_INCORRECT);
            }
        }
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_SET_PID_PARAMETERS);

    // PERSISTENCE
    } else if (commandHeader == COMMAND_LOAD_PID_PARAMETERS_DEFAULT_VALUES) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_LOAD_PID_PARAMETERS_DEFAULT_VALUES);

        // Load Motion Parameters (speed / acceleration)
        loadMotionParameters(pidMotion->pidPersistenceEeprom, true);

        // Load Pid Parameters default Values (and erase previous values)
        loadPidParameters(pidMotion, true);
    } else if (commandHeader == COMMAND_SAVE_PID_PARAMETERS) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_SAVE_PID_PARAMETERS);
        savePidParameters(pidMotion);
    }
    // TRAJECTORY
    // pg01-1001-000020-005678-4000-2000-5000-8000
    else if (commandHeader ==  COMMAND_GET_COMPUTATION_VALUES_DATA_PID) {
        enum InstructionType instructionType = readHex2(inputStream);

        PidComputationValues* computationValues = &(pidMotion->computationValues);
        PidComputationInstructionValues* computationInstructionValues = &(computationValues->values[instructionType]);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_COMPUTATION_VALUES_DATA_PID);

        // InstructionType
        appendHex2(outputStream, instructionType);
        appendSeparator(outputStream);

        // pidType
        appendHexFloat4(outputStream, computationValues->pidTime, PID_TIME_SECOND_DIGIT_PRECISION);
        appendSeparator(outputStream);

        // normalPosition
        appendHexFloat4(outputStream, computationInstructionValues->normalPosition, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);

        // position
        appendHexFloat4(outputStream, computationInstructionValues->currentPosition, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);

        // error
        appendHexFloat4(outputStream, computationInstructionValues->error, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);

        // u
        appendHexFloat4(outputStream, computationInstructionValues->u, PID_VALUE_DIGIT_PRECISION);
        appendSeparator(outputStream);

        // Motion End
        // TODO : Compute End Motion Computation
        /*
        MotionEndInfo* motionEnd = &(computationValues->values[instructionType].motionEnd);
        appendHex4(outputStream, motionEnd->integralTime);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) motionEnd->absSpeedIntegral);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) motionEnd->absUIntegral);
        */
    }
    else if (commandHeader == COMMAND_GET_MOTION_DEFINITION_TRAJECTORY) {
        enum InstructionType instructionType = (enum InstructionType) readHex2(inputStream);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_MOTION_DEFINITION_TRAJECTORY);

		PidMotionDefinition* motionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
        // TODO : Manage if motionDefinition is NULL
		MotionInstruction* localInst = &(motionDefinition->inst[instructionType]);

        appendHex2(outputStream, instructionType);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localInst->a, MOTION_PARAMETERS_ACCELERATION_DIGIT);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localInst->speed, MOTION_PARAMETERS_SPEED_DIGIT);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localInst->speedMax, MOTION_PARAMETERS_SPEED_DIGIT);
        
        appendSeparator(outputStream);

        // t1/t2/t3
        appendHexFloat4(outputStream, localInst->t1, PID_TIME_SECOND_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localInst->t2, PID_TIME_SECOND_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localInst->t3, PID_TIME_SECOND_DIGIT_PRECISION);
        appendSeparator(outputStream);

        // p1/p2/nextPosition
        appendHexFloat4(outputStream, localInst->p1, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localInst->p2, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, localInst->nextPosition, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);

        // types
        appendHex(outputStream, localInst->profileType);
        appendSeparator(outputStream);
        appendHex(outputStream, localInst->motionParameterType);
        appendSeparator(outputStream);
        appendHex(outputStream, localInst->initialPidType);
    }   
    // End Detection Parameter
    else if (commandHeader == COMMAND_GET_END_DETECTION_PARAMETER) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter(pidMotion);
        appendHexFloat4(outputStream, motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, motionEndDetectionParameter->maxUIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, motionEndDetectionParameter->maxUIntegralConstantThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, motionEndDetectionParameter->timeRangeAnalysisInSecond, MOTION_END_DETECTION_PARAMETER_DIGIT);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, motionEndDetectionParameter->noAnalysisAtStartupTimeInSecond, MOTION_END_DETECTION_PARAMETER_DIGIT);
    }
    else if (commandHeader == COMMAND_SET_END_DETECTION_PARAMETER) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter(pidMotion);

        motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = readHexFloat4(inputStream, MOTION_END_DETECTION_PARAMETER_DIGIT);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->maxUIntegralFactorThreshold = readHexFloat4(inputStream, MOTION_END_DETECTION_PARAMETER_DIGIT);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->maxUIntegralConstantThreshold = readHexFloat4(inputStream, MOTION_END_DETECTION_PARAMETER_DIGIT);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->timeRangeAnalysisInSecond = readHexFloat4(inputStream, MOTION_END_DETECTION_PARAMETER_DIGIT);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->noAnalysisAtStartupTimeInSecond = readHexFloat4(inputStream, MOTION_END_DETECTION_PARAMETER_DIGIT);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initPidDevice,
    .deviceShutDown = &stopPidDevice,
    .deviceIsOk = &isPidDeviceOk,
    .deviceHandleRawData = &devicePidHandleRawData,
};

DeviceDescriptor* getPidDeviceDescriptor(PidMotion* pidMotionParam) {
	pidMotion = pidMotionParam;
    return &descriptor;
}
