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
#include "../../../motion/pid/pid.h"
#include "../../../motion/pid/parameters/pidParameter.h"
#include "../../../motion/pid/pidMotion.h"
#include "../../../motion/pid/pidComputationValues.h"
#include "../../../motion/pid/pidCurrentValues.h"
#include "../../../motion/pid/motionInstruction.h"
#include "../../../motion/pid/pidMotionError.h"
#include "../../../motion/pid/pidMotionDefinition.h"
#include "../../../motion/pid/endDetection/motionEndDetection.h"
#include "../../../motion/pid/parameters/pidPersistence.h"

static Eeprom* pidDeviceEeprom;
static bool loadDefaultParameters;

bool isPIDDeviceOk(void) {
    return true;
}

void initPidDevice(void) {
    initPID(pidDeviceEeprom, loadDefaultParameters);
}

void stopPidDevice(void) {
    stopPID();
}

void devicePIDHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_WRITE_PID_PARAMETERS) {
        // send acknowledge
        appendAck(outputStream);
        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);
        checkIsChar(inputStream, '-');
        // PID Value => 2..9 char index
        float p = (float) readHex2(inputStream);
        checkIsChar(inputStream, '-');
        float i = (float) readHex2(inputStream);
        checkIsChar(inputStream, '-');
        float d = (float) readHex2(inputStream);
        checkIsChar(inputStream, '-');
        float maxI = (float) readHex2(inputStream);

        if (pidIndex >= 0 && pidIndex < PID_COUNT) {
            setPidParameter(pidIndex, p, i, d, maxI);
            savePidParameters();
        } else {
            // All Values
            if (pidIndex == -1) {
                int pidIndex2;
                for (pidIndex2 = 0; pidIndex2 < PID_COUNT; pidIndex2++) {
                    setPidParameter(pidIndex2, p, i, d, maxI);
                }
                savePidParameters();
            } else {
                writeError(PID_INDEX_INCORRECT);
            }
        }
        append(outputStream, PID_DEVICE_HEADER);
        append(outputStream, COMMAND_WRITE_PID_PARAMETERS);
    } else if (commandHeader == COMMAND_READ_PID_PARAMETERS) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_READ_PID_PARAMETERS);

        // PID Index => 0..n char index
        char pidIndex = readHex2(inputStream);

        // we test all pid value (test mode included)
        PidParameter* localPidParameter = getPidParameter(pidIndex, 0);
        appendHex2(outputStream, pidIndex);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->p);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->i);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->d);
        appendSeparator(outputStream);
        appendHex2(outputStream, (int) localPidParameter->maxIntegral);
    } else if (commandHeader == COMMAND_LOAD_PID_DEFAULT_VALUES) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_LOAD_PID_DEFAULT_VALUES);
        
        // Load default Values (and erase previous values)
        loadPidParameters(true);
        
        savePidParameters();
    }
    // End Detection Parameter
    else if (commandHeader ==  COMMAND_GET_END_DETECTION_PARAMETER) {
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter();
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
        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_END_DETECTION_PARAMETER);

        MotionEndDetectionParameter* motionEndDetectionParameter = getMotionEndDetectionParameter();

        motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = (float) readHex2(inputStream);
        checkIsChar(inputStream, '-');
        motionEndDetectionParameter->maxUIntegralFactorThreshold = (float)readHex2(inputStream);
        checkIsChar(inputStream, '-');
        motionEndDetectionParameter->maxUIntegralConstantThreshold = (float)readHex2(inputStream);
        checkIsChar(inputStream, '-');
        motionEndDetectionParameter->timeRangeAnalysis = (unsigned int)readHex2(inputStream);
        checkIsChar(inputStream, '-');
        motionEndDetectionParameter->noAnalysisAtStartupTime = (unsigned int)readHex2(inputStream);
    }
    // Debug : pg01-1001-000020-005678-4000-2000-5000-8000
    else if (commandHeader ==  COMMAND_GET_DEBUG_DATA_PID) {
        enum InstructionType instructionType = readHex2(inputStream);

        PidMotion* pidMotion = getPidMotion();
        PidComputationValues* computationValues = &(pidMotion->computationValues);
        MotionInstruction motionInstruction = pidMotion->currentMotionDefinition.inst[instructionType];
        PidMotionError* localError = &(computationValues->errors[instructionType]);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_DEBUG_DATA_PID);

        // InstructionType
        appendHex2(outputStream, instructionType);
        appendSeparator(outputStream);

        // pidType
        appendHex4(outputStream, computationValues->pidTime);
        appendSeparator(outputStream);

        // MotionParameterType
        appendHex2(outputStream, getPidType(motionInstruction.motionParameterType));
        appendSeparator(outputStream);

        PidCurrentValues* pidCurrentValues = &(computationValues->currentValues[instructionType]);

        // normalPosition
        appendHex6(outputStream, (int)pidCurrentValues->normalPosition);
        appendSeparator(outputStream);

        // position
        appendHex6(outputStream, (int) pidCurrentValues->position);
        appendSeparator(outputStream);

        // error
        appendHex4(outputStream, (int) localError->error);
        appendSeparator(outputStream);

        // u
        appendHex4(outputStream, (int) pidCurrentValues->u);
        appendSeparator(outputStream);

        // Motion End
        MotionEndInfo* motionEnd = &(computationValues->motionEnd[instructionType]);
        appendHex4(outputStream, motionEnd->integralTime);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) motionEnd->absDeltaPositionIntegral);
        appendSeparator(outputStream);
        appendHex4(outputStream, (int) motionEnd->absUIntegral);
    }
    else if (commandHeader == COMMAND_GET_MOTION_PARAMETER) {
        enum InstructionType instructionType = (enum InstructionType) readHex2(inputStream);

        // send acknowledgement
        ackCommand(outputStream, PID_DEVICE_HEADER, COMMAND_GET_MOTION_PARAMETER);

        PidMotion* pidMotion = getPidMotion();
        PidMotionDefinition* motionDefinition = &(pidMotion->currentMotionDefinition);
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

        // p1/p2
        appendHex6(outputStream, (int) localInst->p1);
        appendSeparator(outputStream);
        appendHex6(outputStream, (int) localInst->p2);
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
    .deviceIsOk = &isPIDDeviceOk,
    .deviceHandleRawData = &devicePIDHandleRawData,
};

DeviceDescriptor* getPIDDeviceDescriptor(Eeprom* pidPersistenceEeprom, bool loadDefaultValues) {
    pidDeviceEeprom = pidPersistenceEeprom;
    loadDefaultParameters = loadDefaultValues;
    return &descriptor;
}
