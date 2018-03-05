#include "motionInstructionDebug.h"

#include "computer/pidComputer.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// PID GENERAL DATA
#define MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH                           5
#define MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH                       15
#define MOTION_INSTRUCTION_TABLE_NORMAL_SPEED_COLUMN_LENGTH                   15
#define MOTION_INSTRUCTION_TABLE_NORMAL_POSITION_COLUMN_LENGTH                15
#define MOTION_INSTRUCTION_TABLE_NORMAL_U_COLUMN_LENGTH                       15
#define MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH                           15

/**
 * Print the motion Instruction Table Header.
 * @private
 * @param outputStream
 */
void printMotionInstructionTableTrajectoryHeader(OutputStream* outputStream) {
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Index", MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pid Time", MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal Speed", MOTION_INSTRUCTION_TABLE_NORMAL_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal Position", MOTION_INSTRUCTION_TABLE_NORMAL_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal U", MOTION_INSTRUCTION_TABLE_NORMAL_U_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Print a motion Instruction
 * @param outputStream
 * @param index
 * @param pidTime
 * @param normalSpeed
 * @param normalPosition
 * @param normalU
 */
void printMotionInstructionTableTrajectoryLine(OutputStream* outputStream, unsigned int index, float pidTime, float normalSpeed, float normalPosition, float normalU) {
    appendDecTableData(outputStream, index, MOTION_INSTRUCTION_TABLE_INDEX_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pidTime, MOTION_INSTRUCTION_TABLE_PID_TIME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, normalSpeed, MOTION_INSTRUCTION_TABLE_NORMAL_SPEED_COLUMN_LENGTH);
    appendDecfTableData(outputStream, normalPosition, MOTION_INSTRUCTION_TABLE_NORMAL_POSITION_COLUMN_LENGTH);
    appendDecfTableData(outputStream, normalU, MOTION_INSTRUCTION_TABLE_NORMAL_U_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_INSTRUCTION_TABLE_LAST_COLUMN_LENGTH);
}

/**
 * Print a trajectory from a Motion Instruction with a maxPidTime.
 */
void printMotionInstructionTableTrajectory(OutputStream* outputStream, MotionInstruction* instruction) {
    printMotionInstructionTableTrajectoryHeader(outputStream);
    float pidTime;
    unsigned int index = 0;
    for (pidTime = 0.0f; pidTime < instruction->t3 + 1.0f; pidTime += 1.0f) {
        float normalSpeed = computeNormalSpeed(instruction, pidTime);
        float normalPosition = computeNormalPosition(instruction, pidTime);
        float normalU = 0.0f;
        index++;
        printMotionInstructionTableTrajectoryLine(outputStream, index, pidTime, normalSpeed, normalPosition, normalU);
    }
    appendTableHeaderSeparatorLine(outputStream);
}