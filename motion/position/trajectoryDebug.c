#include "trajectoryDebug.h"
#include "trajectory.h"

#include "../../common/math/cenMath.h"

#include "../../common/2d/2d.h"

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../motion/position/coders.h"

#define TRAJECTORY_X_DEC_COLUMN_LENGTH	                12
#define TRAJECTORY_Y_DEC_COLUMN_LENGTH	                12
#define TRAJECTORY_X_HEX_COLUMN_LENGTH	                12
#define TRAJECTORY_Y_HEX_COLUMN_LENGTH	                12
#define TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH	            16
#define TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH	        16

#define TRAJECTORY_LEFT_DEC_COLUMN_LENGTH	            11
#define TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH	            12
#define TRAJECTORY_LEFT_HEX_COLUMN_LENGTH	            11
#define TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH	            12
#define TRAJECTORY_LAST_LEFT_COLUMN_LENGTH	            17
#define TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH	            18
#define TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH	            16
#define TRAJECTORY_LAST_COLUMN_LENGTH					0

void printDebugPosition(OutputStream* outputStream) {
	// HEADER
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "x (Dec) mm", TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y (Dec) mm", TRAJECTORY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "x (Hex) mm", TRAJECTORY_X_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y (Hex) mm", TRAJECTORY_Y_HEX_COLUMN_LENGTH);

	appendStringHeader(outputStream, "angle (deg)", TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "angle init (deg)", TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);

	// VALUES
    Position* position = getPosition();
	Point* point = &(position->pos);

	// X / Y
	appendDecfTableData(outputStream, point->x, TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, point->y, TRAJECTORY_Y_DEC_COLUMN_LENGTH);

	appendHexFloat4TableData(outputStream, point->x, POSITION_DIGIT_MM_PRECISION, TRAJECTORY_X_HEX_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, point->y, POSITION_DIGIT_MM_PRECISION, TRAJECTORY_Y_HEX_COLUMN_LENGTH);

	// Angle / Last Angle
	appendDecfTableData(outputStream, radToDeg(position->orientation), TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, radToDeg(position->initialOrientation), TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, 0);

	// END OF TABLE
	appendTableHeaderSeparatorLine(outputStream);
}

void printDebugCoderHistory(OutputStream* outputStream) {

	// HEADER
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);

	appendStringHeader(outputStream, "left (Dec)", TRAJECTORY_LEFT_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "right (Dec)", TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "left (Hex)", TRAJECTORY_LEFT_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "right (Hex)", TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH);

	appendStringHeader(outputStream, "lastLeft (pulse)", TRAJECTORY_LAST_LEFT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "lastRight (pulse)", TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "lastAngle (deg)", TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, TRAJECTORY_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);

	// VALUES
	// Left / Right
	appendDecTableData(outputStream, getCoderValue(CODER_LEFT), TRAJECTORY_LEFT_DEC_COLUMN_LENGTH);
	appendDecTableData(outputStream, getCoderValue(CODER_RIGHT), TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH);

	appendHex4TableData(outputStream, getCoderValue(CODER_LEFT), TRAJECTORY_LEFT_HEX_COLUMN_LENGTH);
	appendHex4TableData(outputStream, getCoderValue(CODER_RIGHT), TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH);

	// Last left / Right / Angle
    TrajectoryInfo* trajectoryInfo = getTrajectory();
	appendDecfTableData(outputStream, trajectoryInfo->lastLeft, TRAJECTORY_LAST_LEFT_COLUMN_LENGTH);
	appendDecfTableData(outputStream, trajectoryInfo->lastRight, TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH);
	appendDecfTableData(outputStream, radToDeg(trajectoryInfo->lastAngle), TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, TRAJECTORY_LAST_COLUMN_LENGTH);

	// END OF TABLE
	appendTableHeaderSeparatorLine(outputStream);
}
