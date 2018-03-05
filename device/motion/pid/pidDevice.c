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
    if (commandHeader == COMMAND_MOTION_LOAD_DEFAULT_PARAMETERS) {
		// send acknowledge
		ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_MOTION_LOAD_DEFAULT_PARAMETERS);
		loadMotionParameters(pidMotion->pidPersistenceEeprom, true);
	}
    else if (commandHeader == COMMAND_GET_MOTION_PARAMETERS) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_MOTION_PARAMETERS);
        enum MotionParameterType motionParameterType = (enum MotionParameterType) readHex2(inputStream);

        MotionParameter* motionParameter = getMotionParameters(motionParameterType);
        appendHex2(outputStream, (int) motionParameter->a);
        appendHex2(outputStream, (int) motionParameter->speed);

    } else if (commandHeader == COMMAND_SET_MOTION_PARAMETERS) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_SET_MOTION_PARAMETERS);
        enum MotionParameterType motionParameterType = (enum MotionParameterType) readHex2(inputStream);
        float a = (float) readHex2(inputStream);
        float speed = (float) readHex2(inputStream);

        MotionParameter* motionParameter = getMotionParameters(motionParameterType);
        motionParameter->a = a;
        motionParameter->speed = speed;
    } else if (commandHeader == COMMAND_MOTION_SAVE_TO_EEPROM_PARAMETERS) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_MOTION_SAVE_TO_EEPROM_PARAMETERS);

        saveMotionParameters(pidMotion->pidPersistenceEeprom);
    }
    // PID PARAMETERS
    else if (commandHeader == COMMAND_WRITE_PID_PARAMETERS) {
        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        // PID Value => 2..9 char index
        float p = (float) readHex2(inputStream);
        checkIsSeparator(inputStream);
        float i = (float) readHex2(inputStream);
        checkIsSeparator(inputStream);
        float d = (float) readHex2(inputStream);
        checkIsSeparator(inputStream);
        float maxI = (float) readHex2(inputStream);

        if (pidIndex >= 0 && pidIndex < PID_COUNT) {
            setPidParameter(pidMotion, pidIndex, p, i, d, maxI);
        } else {
            // All Values
            if (pidIndex == -1) {
                int pidIndex2;
                for (pidIndex2 = 0; pidIndex2 < PID_COUNT; pidIndex2++) {
                    setPidParameter(pidMotion, pidIndex2, p, i, d, maxI);
                }
            } else {
                writeError(PID_INDEX_INCORRECT);
            }
        }
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_WRITE_PID_PARAMETERS);
    } else if (commandHeader == COMMAND_READ_PID_PARAMETERS) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_READ_PID_PARAMETERS);

        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);

        // we test all pid value (test mode included)
        PidParameter* localPidParameter = getPidParameter(pidMotion, pidIndex, 0);
        appendHex2(outputStream, pidIndex);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->p);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->i);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->d);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->maxIntegral);
    } else if (commandHeader == COMMAND_LOAD_PID_PARAMETERS_DEFAULT_VALUES) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_LOAD_PID_PARAMETERS_DEFAULT_VALUES);
        
        // Load default Values (and erase previous values)
        loadPidParameters(pidMotion, true);
    } else if (commandHeader == COMMAND_SAVE_PID_PARAMETERS) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_SAVE_PID_PARAMETERS);
        savePidParameters(pidMotion);
    } // End Detection Parameter
    else if (commandHeader ==  COMMAND_GET_END_DETECTION_PARAMETER) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter(pidMotion);
        appendHex2(outputStream, (unsigned char) motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold);
        appendSeparator(outputStream);
        appendHex2(outputStream, (unsigned char)motionEndDetectionParameter->maxUIntegralFactorThreshold);
        appendSeparator(outputStream);
        appendHex2(outputStream, (unsigned char)motionEndDetectionParameter->maxUIntegralConstantThreshold);
        appendSeparator(outputStream);
        appendHex2(outputStream, (unsigned int)motionEndDetectionParameter->timeRangeAnalysis);
        appendSeparator(outputStream);
        appendHex2(outputStream, (unsigned int)motionEndDetectionParameter->noAnalysisAtStartupTime);
    }
    else if (commandHeader ==  COMMAND_SET_END_DETECTION_PARAMETER) {
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter(pidMotion);

        motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = (float) readHex2(inputStream);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->maxUIntegralFactorThreshold = (float)readHex2(inputStream);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->maxUIntegralConstantThreshold = (float)readHex2(inputStream);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->timeRangeAnalysis = (unsigned int)readHex2(inputStream);
        checkIsSeparator(inputStream);
        motionEndDetectionParameter->noAnalysisAtStartupTime = (unsigned int)readHex2(inputStream);
    }
    // Debug : pg01-1001-000020-005678-4000-2000-5000-8000
    else if (commandHeader ==  COMMAND_GET_DEBUG_DATA_PID) {
        enum InstructionType instructionType = readHex2(inputStream);

        PidComputationValues* computationValues = &(pidMotion->computationValues);
        PidComputationInstructionValues* computationInstructionValues = &(computationValues->values[instructionType]);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_DEBUG_DATA_PID);

        // InstructionType
        appendHex2(outputStream, instructionType);
        appendSeparator(outputStream);

        // pidType
        appendHex4(outputStream, (int) computationValues->pidTime);
        appendSeparator(outputStream);

        // normalPosition
        appendHex6(outputStream, (int)computationInstructionValues->normalPosition);
        appendSeparator(outputStream);

        // position
        appendHex6(outputStream, (int) computationInstructionValues->currentPosition);
        appendSeparator(outputStream);

        // error
        appendHex4(outputStream, (int) computationInstructionValues->error);
        appendSeparator(outputStream);

        // u
        appendHex4(outputStream, (int) computationInstructionValues->u);
        appendSeparator(outputStream);

        // Motion End
        /*
        MotionEndInfo* motionEnd = &(computationValues->values[instructionType].motionEnd);
        appendHex4(outputStream, motionEnd->integralTime);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) motionEnd->absSpeedIntegral);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) motionEnd->absUIntegral);
        */
    }
    else if (commandHeader == COMMAND_GET_MOTION_PARAMETER) {
        enum InstructionType instructionType = (enum InstructionType) readHex2(inputStream);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_MOTION_PARAMETER);

		PidMotionDefinition* motionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
        // TODO : Manage if motionDefinition is NULL
		MotionInstruction* localInst = &(motionDefinition->inst[instructionType]);

        appendHex2(outputStream, instructionType);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localInst->a);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localInst->speed);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localInst->speedMax);
        
        appendSeparator(outputStream);

        // t1/t2/t3
        appendHex4(outputStream, (int) localInst->t1);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) localInst->t2);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) localInst->t3);
        appendSeparator(outputStream);

        // p1/p2/nextPosition
        appendHex6(outputStream, (int) localInst->p1);
        appendSeparator(outputStream);
        appendHex6(outputStream, (int) localInst->p2);
        appendSeparator(outputStream);
        appendHex6(outputStream, (int)localInst->nextPosition);
        appendSeparator(outputStream);

        // types
        appendHex(outputStream, localInst->profileType);
        appendSeparator(outputStream);
        appendHex(outputStream, localInst->motionParameterType);
        appendSeparator(outputStream);
        appendHex(outputStream, localInst->pidType);
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
