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
#define MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_SPEED_COLUMN_LENGTH             15
#define MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_POSITION_COLUMN_LENGTH          10
#define MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH                   10
#define MOTION_INSTRUCTION_TABLE_TIME_IN_SECOND__COLUMN_LENGTH                10
#define MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH         10
#define MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH             10
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
	appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Time", MOTION_INSTRUCTION_TABLE_TIME_IN_SECOND__COLUMN_LENGTH);
    appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Normal", MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);
    
    // Second Header Line
    appendStringHeader(outputStream, "", MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Time", MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Speed", MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Position", MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "U", MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", MOTION_INSTRUCTION_TABLE_TIME_IN_SECOND__COLUMN_LENGTH);
    appendStringHeader(outputStream, "Speed", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Position", MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);
    
    // Third Header line 
    appendStringHeader(outputStream, "", MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(pulse/pidTime)", MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(pulse)", MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "[0..255]", MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(second)", MOTION_INSTRUCTION_TABLE_TIME_IN_SECOND__COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm/sec)", MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm", MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);

	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Print a motion Instruction
 * @param outputStream
 * @param index
 * @param pidTime
 * @param pulseNormalSpeed the speed in coder pulse / PID FREQUENCY TIME
 * @param pulseNormalPosition the normal position in pulse (coder)
 * @param normalU the PWM Value (between 0 and 255)
 * @param mmBySecondNormalSpeed the speed in mm / second
 */
void printMotionInstructionTableTrajectoryLine(OutputStream* outputStream,
                                               unsigned int index,
                                               float pidTime,
                                               float pulseNormalSpeed,
                                               float pulseNormalPosition,
                                               float pwmNormalU,
                                               float mmBySecondNormalSpeed,
                                               float mmNormalPosition) {
    appendDecTableData(outputStream, index, MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    // PID TIME / Pulse
    appendDecfTableData(outputStream, pidTime, MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pulseNormalSpeed, MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_SPEED_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pulseNormalPosition, MOTION_INSTRUCTION_TABLE_PULSE_NORMAL_POSITION_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pwmNormalU, MOTION_INSTRUCTION_TABLE_PWM_NORMAL_U_COLUMN_LENGTH);
    // SECOND / MM 
    appendDecfTableData(outputStream, pidTime / PID_UPDATE_MOTORS_FREQUENCY_HERTZ, MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, mmBySecondNormalSpeed, MOTION_INSTRUCTION_TABLE_MM_SECOND_NORMAL_SPEED_COLUMN_LENGTH);
    appendDecfTableData(outputStream, mmNormalPosition, MOTION_INSTRUCTION_TABLE_MM_NORMAL_POSITION_COLUMN_LENGTH);
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
    for (pidTime = 0.0f; pidTime < instruction->t3 + 1.0f; pidTime += pidInterval) {
        float pulseNormalSpeed = computeNormalSpeed(instruction, pidTime);
        float pulseNormalPosition = computeNormalPosition(instruction, pidTime);
        float pwmNormalU = getNormalU(pulseNormalSpeed);
        float mmBySecondNormalSpeed = pulseByPidTimeSpeedToMMBySecondSpeed(pulseNormalSpeed);
        float mmNormalPosition = pulseNormalPosition * getCoderAverageWheelLengthForOnePulse(robotKinematics);
        index++;
        printMotionInstructionTableTrajectoryLine(outputStream, index, pidTime, pulseNormalSpeed, pulseNormalPosition, pwmNormalU, mmBySecondNormalSpeed, mmNormalPosition);
    }
    appendTableHeaderSeparatorLine(outputStream);
}