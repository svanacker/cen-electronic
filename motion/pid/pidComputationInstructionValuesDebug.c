#include "pidComputationInstructionValuesDebug.h"

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "instructionType.h"
#include "motionInstruction.h"
#include "pid.h"
#include "pidType.h"
#include "pidTypeDebug.h"
#include "pidMotion.h"
#include "pidMotionDefinitionState.h"
#include "computer/pidComputer.h"
#include "../parameters/motionParameterTypeDebug.h"
#include "../extended/bsplineDebug.h"
#include "endDetection/motionEndDetectionDebug.h"

#define PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH                     6

#define PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH                             6
#define PID_DEBUG_DATA_PID_TYPE_COLUMN_LENGTH                             8

#define PID_DEBUG_DATA_NORMAL_SPEED_COLUMN_LENGTH                         7
#define PID_DEBUG_DATA_SPEED_COLUMN_LENGTH                                9

#define PID_DEBUG_DATA_NORMAL_ACCELERATION_COLUMN_LENGTH                  7
#define PID_DEBUG_DATA_ACCELERATION_COLUMN_LENGTH                         9

#define PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH                      8
#define PID_DEBUG_DATA_POSITION_COLUMN_LENGTH                             9

#define PID_DEBUG_DATA_P_ERROR_COLUMN_LENGTH                              6
#define PID_DEBUG_DATA_I_ERROR_COLUMN_LENGTH                              6
#define PID_DEBUG_DATA_D_ERROR_COLUMN_LENGTH                              6

#define PID_DEBUG_DATA_P_ERROR_X_P_COLUMN_LENGTH                          6
#define PID_DEBUG_DATA_I_ERROR_X_I_COLUMN_LENGTH                          6
#define PID_DEBUG_DATA_D_ERROR_X_D_COLUMN_LENGTH                          6

#define PID_DEBUG_DATA_NORMAL_U_COLUMN_LENGTH                             7
#define PID_DEBUG_DATA_U_COLUMN_LENGTH                                    6

#define PID_DEBUG_DATA_MOTION_END_DETECTION_STATUS_COLUMN_LENGTH          5

#define PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH		              0

/**
* Private.
*/
void printDebugDataHeader(OutputStream* outputStream) {
	println(outputStream);
    // FIRST line
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Instr.", PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pid", PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pid", PID_DEBUG_DATA_PID_TYPE_COLUMN_LENGTH);

    // -> Acceleration
    appendStringHeader(outputStream, "Normal", PID_DEBUG_DATA_NORMAL_ACCELERATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Real", PID_DEBUG_DATA_ACCELERATION_COLUMN_LENGTH);
    // -> Speed
    appendStringHeader(outputStream, "Normal", PID_DEBUG_DATA_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Real", PID_DEBUG_DATA_SPEED_COLUMN_LENGTH);
    // -> Position
	appendStringHeader(outputStream, "Normal", PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Real", PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);
    // -> Error
    appendStringHeader(outputStream, "Prop.", PID_DEBUG_DATA_P_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Int.", PID_DEBUG_DATA_I_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Deriv.", PID_DEBUG_DATA_D_ERROR_COLUMN_LENGTH);

    appendStringHeader(outputStream, "PE x P", PID_DEBUG_DATA_P_ERROR_X_P_COLUMN_LENGTH);
    appendStringHeader(outputStream, "IE x I", PID_DEBUG_DATA_I_ERROR_X_I_COLUMN_LENGTH); 
    appendStringHeader(outputStream, "DE x D", PID_DEBUG_DATA_D_ERROR_X_D_COLUMN_LENGTH);

    // -> U
    appendStringHeader(outputStream, "Normal", PID_DEBUG_DATA_NORMAL_U_COLUMN_LENGTH);
    appendStringHeader(outputStream, "U", PID_DEBUG_DATA_U_COLUMN_LENGTH);

    // -> End Detection
	appendStringHeader(outputStream, "End", PID_DEBUG_DATA_MOTION_END_DETECTION_STATUS_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);
    
    // SECOND line
    appendStringHeader(outputStream, "Type", PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Time", PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Type", PID_DEBUG_DATA_PID_TYPE_COLUMN_LENGTH);
    // -> Acceleration
    appendStringHeader(outputStream, "Acc.", PID_DEBUG_DATA_NORMAL_ACCELERATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Acc.", PID_DEBUG_DATA_ACCELERATION_COLUMN_LENGTH);
    // -> Speed
    appendStringHeader(outputStream, "Speed", PID_DEBUG_DATA_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Speed", PID_DEBUG_DATA_SPEED_COLUMN_LENGTH);
    // -> Position
	appendStringHeader(outputStream, "Position", PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Position", PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);
	// -> Error
    appendStringHeader(outputStream, "Error", PID_DEBUG_DATA_P_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Error", PID_DEBUG_DATA_I_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Error", PID_DEBUG_DATA_D_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_P_ERROR_X_P_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_I_ERROR_X_I_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_D_ERROR_X_D_COLUMN_LENGTH);
    // -> U
    appendStringHeader(outputStream, "U", PID_DEBUG_DATA_NORMAL_U_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_U_COLUMN_LENGTH);
    // End Detection
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_MOTION_END_DETECTION_STATUS_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);

    // THIRD line
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_PID_TYPE_COLUMN_LENGTH);
    // -> Speed
    appendStringHeader(outputStream, "mm/s^2", PID_DEBUG_DATA_NORMAL_ACCELERATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm/s^2", PID_DEBUG_DATA_ACCELERATION_COLUMN_LENGTH);
    // -> Speed
    appendStringHeader(outputStream, "mm / s", PID_DEBUG_DATA_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm / s", PID_DEBUG_DATA_SPEED_COLUMN_LENGTH);
    // -> Position
    appendStringHeader(outputStream, "mm", PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm", PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);
    // -> Error
    appendStringHeader(outputStream, "mm", PID_DEBUG_DATA_P_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm * s", PID_DEBUG_DATA_I_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm / s", PID_DEBUG_DATA_D_ERROR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_P_ERROR_X_P_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_I_ERROR_X_I_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_D_ERROR_X_D_COLUMN_LENGTH);
    // -> U
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_NORMAL_U_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_U_COLUMN_LENGTH);
    // End Detection
    appendStringHeader(outputStream, "", PID_DEBUG_DATA_MOTION_END_DETECTION_STATUS_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);

	appendTableHeaderSeparatorLine(outputStream);
}


/**
 * Print a line of data for a specific Instruction Type.
 */
void printDebugDataInstructionTypeLine(OutputStream* outputStream, PidMotion* pidMotion, enum InstructionType instructionType) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* computationInstructionValues = &(computationValues->values[instructionType]);

    PidMotionDefinition* pidMotionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
    
    unsigned int i;
    for (i = 0; i < computationInstructionValues->historyCount; i++) {
        // THETA / ALPHA
        addInstructionTypeTableData(outputStream, instructionType, PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);

        // pid Time
        float pidTime = computationInstructionValues->pidTimeHistory[i];
        appendDecfTableData(outputStream, pidTime, PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);

        // Pid Type
        enum PidType pidType = computationInstructionValues->pidTypeHistory[i];
        addPidTypeTableData(outputStream, pidType, PID_DEBUG_DATA_PID_TYPE_COLUMN_LENGTH);

        // Normal Acceleration & Acceleration
        if (pidMotionDefinition != NULL) {
            float normalAcceleration = computeNormalAcceleration(&(pidMotionDefinition->inst[instructionType]), pidTime);
            appendDecfTableData(outputStream, normalAcceleration, PID_DEBUG_DATA_NORMAL_ACCELERATION_COLUMN_LENGTH);
        }
        else {
            appendStringTableData(outputStream, "-", PID_DEBUG_DATA_NORMAL_ACCELERATION_COLUMN_LENGTH);
        }
        appendDecfTableData(outputStream, computationInstructionValues->accelerationHistory[i], PID_DEBUG_DATA_ACCELERATION_COLUMN_LENGTH);
        
        // Normal Speed & Speed
        if (pidMotionDefinition != NULL) {
            float normalSpeed = computeNormalSpeed(&(pidMotionDefinition->inst[instructionType]), pidTime);
            appendDecfTableData(outputStream, normalSpeed, PID_DEBUG_DATA_NORMAL_SPEED_COLUMN_LENGTH);
        }
        else {
            appendStringTableData(outputStream, "-", PID_DEBUG_DATA_NORMAL_SPEED_COLUMN_LENGTH);
        }
        appendDecfTableData(outputStream, computationInstructionValues->speedHistory[i], PID_DEBUG_DATA_SPEED_COLUMN_LENGTH);

        // Normal Position & Position
        if (pidMotionDefinition != NULL) {
            float normalPosition = computeNormalPosition(&(pidMotionDefinition->inst[instructionType]), pidTime);
            appendDecfTableData(outputStream, normalPosition, PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
        }
        else {
            appendStringTableData(outputStream, "-", PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
        }
        appendDecfTableData(outputStream, computationInstructionValues->positionHistory[i], PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);

        // Error
        appendDecfTableData(outputStream, computationInstructionValues->errorHistory[i], PID_DEBUG_DATA_P_ERROR_COLUMN_LENGTH);
        appendDecfTableData(outputStream, computationInstructionValues->integralErrorHistory[i], PID_DEBUG_DATA_I_ERROR_COLUMN_LENGTH);
        appendDecfTableData(outputStream, computationInstructionValues->derivativeErrorHistory[i], PID_DEBUG_DATA_D_ERROR_COLUMN_LENGTH);

        // Get the pid Parameter used for this historized pidType
        PidParameter* pidParameter = getPidParameterByPidType(pidMotion, pidType);
        appendDecfTableData(outputStream, computationInstructionValues->errorHistory[i] * pidParameter->p, PID_DEBUG_DATA_P_ERROR_COLUMN_LENGTH);
        appendDecfTableData(outputStream, computationInstructionValues->integralErrorHistory[i] * pidParameter->i, PID_DEBUG_DATA_I_ERROR_COLUMN_LENGTH);
        appendDecfTableData(outputStream, computationInstructionValues->derivativeErrorHistory[i] * pidParameter->d, PID_DEBUG_DATA_D_ERROR_COLUMN_LENGTH);

        // U
        if (pidMotionDefinition != NULL) {
            float normalSpeed = computeNormalSpeed(&(pidMotionDefinition->inst[instructionType]), pidTime);
            float normalU = getNormalU(normalSpeed);
            appendDecfTableData(outputStream, normalU, PID_DEBUG_DATA_NORMAL_U_COLUMN_LENGTH);
        }
        else {
            appendStringTableData(outputStream, "-", PID_DEBUG_DATA_NORMAL_U_COLUMN_LENGTH);
        }
        appendDecfTableData(outputStream, computationInstructionValues->uHistory[i], PID_DEBUG_DATA_U_COLUMN_LENGTH);

        // Status
        appendMotionEndDetectionStatusRegisterTableData(outputStream, computationInstructionValues->statusHistory[i], PID_DEBUG_DATA_MOTION_END_DETECTION_STATUS_COLUMN_LENGTH);

        appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);
    }
}

void printPidDataDebugTable(OutputStream* outputStream, PidMotion* pidMotion) {
	printDebugDataHeader(outputStream);
	printDebugDataInstructionTypeLine(outputStream, pidMotion, THETA);
	printDebugDataInstructionTypeLine(outputStream, pidMotion, ALPHA);
	appendTableHeaderSeparatorLine(outputStream);
}
