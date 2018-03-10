#include "motionInstructionDebug.h"

#include "../../common/timer/cenTimer.h"

#include "computer/pidComputer.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../robot/kinematics/robotKinematics.h"

// PID GENERAL DATA
#define MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH                          6
#define MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH                       10
#define MOTION_INSTRUCTION_TABLE_TIME_IN_SECOND__COLUMN_LENGTH                12
#define MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_ACCELERATION_COLUMN_LENGTH  12
#define MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH         12
#define MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH             12
#define MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH                   12
#define MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH                           10

/**
 * Print the motion Instruction Table Header.
 * @private
 * @param outputStream
 */
void printMotionInstructionTableTrajectoryHeader(OutputStream* outputStream, enum InstructionType instructionType) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    addInstructionTypeTableData(outputStream, instructionType, MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, 0);
    appendTableHeaderSeparatorLine(outputStream);

    // First Header Line
    appendStringHeader(outputStream, "Index", MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pid", MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_ACCELERATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);
    
    // Second Header Line
    appendStringHeader(outputStream, "", MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Time", MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Acceleration", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_ACCELERATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Speed", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Position", MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "U", MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);
    
    // Third Header line 
    appendStringHeader(outputStream, "", MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(second)", MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm/sec^2)", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_ACCELERATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm/sec)", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "[0..255]", MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);

	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Print a motion Instruction
 * @param outputStream
 * @param index
 * @param pidTime
 * @param mmBySecondNormalSpeed the speed in mm / second
 */
void printMotionInstructionTableTrajectoryLine(OutputStream* outputStream,
                                               unsigned int index,
                                               float pidTime,
                                               float normalAcceleration,
                                               float normalSpeed,
                                               float normalPosition,
                                               float pwmNormalU) {
    appendDecTableData(outputStream, index, MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pidTime, MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, normalAcceleration, MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_ACCELERATION_COLUMN_LENGTH);
    appendDecfTableData(outputStream, normalSpeed, MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendDecfTableData(outputStream, normalPosition, MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pwmNormalU, MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);
}

/**
 * Print a trajectory from a Motion Instruction with a maxPidTime.
 */
void printMotionInstructionTableTrajectory(OutputStream* outputStream, enum InstructionType instructionType, MotionInstruction* instruction, float pidInterval) {
    printMotionInstructionTableTrajectoryHeader(outputStream, instructionType);
    float pidTime;
    unsigned int index = 0;
    RobotKinematics* robotKinematics = getRobotKinematics();
    for (pidTime = 0.0f; pidTime < instruction->t3 + pidInterval; pidTime += pidInterval) {
        float pulseNormalAcceleration = computeNormalAcceleration(instruction, pidTime);
        float pulseNormalSpeed = computeNormalSpeed(instruction, pidTime);
        float pulseNormalPosition = computeNormalPosition(instruction, pidTime);
        float pwmNormalU = getNormalU(pulseNormalSpeed);
        index++;
        printMotionInstructionTableTrajectoryLine(outputStream, index, pidTime, pulseNormalAcceleration, pulseNormalSpeed, pulseNormalPosition, pwmNormalU);
    }
    appendTableHeaderSeparatorLine(outputStream);
}