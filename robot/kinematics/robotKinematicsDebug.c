#include "robotKinematicsDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define ROBOT_KINEMATICS_KEY_COLUMN_LENGTH        38
#define ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH  10
#define ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH      10
#define ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH       12
#define ROBOT_KINEMATICS_LAST_COLUMN              35

void printRobotKinematicsTableHeader(OutputStream* outputStream) {
	println(outputStream);

	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Key", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Hex Value", ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Dec Value", ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Unit ", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
	appendTableHeaderSeparatorLine(outputStream);
}

void printRobotKinematicsTable(OutputStream* outputStream, RobotKinematics* robotKinematics) {
	printRobotKinematicsTableHeader(outputStream);
	appendStringTableData(outputStream, "wheels Distance", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHex6TableData(outputStream, (long) (robotKinematics->wheelsDistance * MILLI_TO_MICRO_FACTOR), ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (long) (robotKinematics->wheelsDistance * MILLI_TO_MICRO_FACTOR), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "microMM", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

	appendStringTableData(outputStream, "pulse By Rotation", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHex6TableData(outputStream, (long) robotKinematics->pulseByRotation, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (long) robotKinematics->pulseByRotation, ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "-", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

	appendStringTableData(outputStream, "wheel Average Length For One Pulse", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHex6TableData(outputStream, (long) (robotKinematics->wheelAverageLengthForOnePulse * MILLI_TO_NANO_FACTOR), ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (long)(robotKinematics->wheelAverageLengthForOnePulse * MILLI_TO_NANO_FACTOR), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "nano mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

	appendStringTableData(outputStream, "wheel Delta Length For One Pulse", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHex6TableData(outputStream, (long) (robotKinematics->wheelDeltaLengthForOnePulse * MILLI_TO_NANO_FACTOR), ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (long) (robotKinematics->wheelDeltaLengthForOnePulse * MILLI_TO_NANO_FACTOR), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "nano mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

	appendStringTableData(outputStream, "rotation By Sec At FullSpeed", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHex6TableData(outputStream, (long) robotKinematics->wheelRotationBySecondsAtFullSpeed, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (long) robotKinematics->wheelRotationBySecondsAtFullSpeed, ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "rot / sec", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

	appendTableHeaderSeparatorLine(outputStream);
}
