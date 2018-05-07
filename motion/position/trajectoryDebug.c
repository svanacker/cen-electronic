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

#define TRAJECTORY_X_DEC_COLUMN_LENGTH	                             8
#define TRAJECTORY_Y_DEC_COLUMN_LENGTH	                             8
#define TRAJECTORY_X_HEX_COLUMN_LENGTH	                             7
#define TRAJECTORY_Y_HEX_COLUMN_LENGTH	                             7
#define TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH	                         9
#define TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH	                    11
// NOTIFICATION
// -> PARAMETERS
#define TRAJECTORY_LAST_NOTIFY_ENABLED_COLUMN_LENGTH                 7
#define TRAJECTORY_LAST_NOTIFY_DISTANCE_THRESHOLD_COLUMN_LENGTH      10
#define TRAJECTORY_LAST_NOTIFY_ANGLE_RADIAN_THRESHOLD_COLUMN_LENGTH  10
// -> VALUES
#define TRAJECTORY_LAST_NOTIFY_X_DEC_COLUMN_LENGTH                   8
#define TRAJECTORY_LAST_NOTIFY_Y_DEC_COLUMN_LENGTH                   8
#define TRAJECTORY_LAST_NOTIFY_ANGLE_DEC_COLUMN_LENGTH               8

#define TRAJECTORY_LEFT_DEC_COLUMN_LENGTH	                        11
#define TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH	                        12
#define TRAJECTORY_LEFT_HEX_COLUMN_LENGTH	                        11
#define TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH	                        12
#define TRAJECTORY_LAST_LEFT_COLUMN_LENGTH	                        17
#define TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH	                        18
#define TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH	                        16
#define TRAJECTORY_LAST_COLUMN_LENGTH					             0

void printDebugPosition(OutputStream* outputStream) {
	// HEADER
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
    
    // First line header
	appendStringHeader(outputStream, "x", TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y", TRAJECTORY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "orient.", TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "angle Ini.", TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "x", TRAJECTORY_X_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y", TRAJECTORY_Y_HEX_COLUMN_LENGTH);
    // -> Notification Parameters
	appendStringHeader(outputStream, "Notify", TRAJECTORY_LAST_NOTIFY_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Notify", TRAJECTORY_LAST_NOTIFY_DISTANCE_THRESHOLD_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Notify", TRAJECTORY_LAST_NOTIFY_ANGLE_RADIAN_THRESHOLD_COLUMN_LENGTH);
    // -> Notification Values
	appendStringHeader(outputStream, "Last not.", TRAJECTORY_LAST_NOTIFY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Last not.", TRAJECTORY_LAST_NOTIFY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Last not.", TRAJECTORY_LAST_NOTIFY_ANGLE_DEC_COLUMN_LENGTH);
    
	appendEndOfTableColumn(outputStream, 0);
    
    // Second line header
	appendStringHeader(outputStream, "mm", TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "mm", TRAJECTORY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(degree)", TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(degree)", TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "mm", TRAJECTORY_X_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "mm", TRAJECTORY_Y_HEX_COLUMN_LENGTH);
    // -> Notification Parameters
    appendStringHeader(outputStream, "On/Off", TRAJECTORY_LAST_NOTIFY_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Threshold", TRAJECTORY_LAST_NOTIFY_DISTANCE_THRESHOLD_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Threshold", TRAJECTORY_LAST_NOTIFY_ANGLE_RADIAN_THRESHOLD_COLUMN_LENGTH);
    // -> Notification Values
	appendStringHeader(outputStream, "x (mm)", TRAJECTORY_LAST_NOTIFY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y (mm)", TRAJECTORY_LAST_NOTIFY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "ang. (mm)", TRAJECTORY_LAST_NOTIFY_ANGLE_DEC_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
    
    // Third line header
	appendStringHeader(outputStream, "(Dec)", TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", TRAJECTORY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", TRAJECTORY_X_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", TRAJECTORY_Y_HEX_COLUMN_LENGTH);
    // -> Notification Threshold
    appendStringHeader(outputStream, "", TRAJECTORY_LAST_NOTIFY_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Dist(mm)", TRAJECTORY_LAST_NOTIFY_DISTANCE_THRESHOLD_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Angle(deg)", TRAJECTORY_LAST_NOTIFY_ANGLE_RADIAN_THRESHOLD_COLUMN_LENGTH);
    // -> Notification values
	appendStringHeader(outputStream, "(Dec)", TRAJECTORY_LAST_NOTIFY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", TRAJECTORY_LAST_NOTIFY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Degree)", TRAJECTORY_LAST_NOTIFY_ANGLE_DEC_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
    
	appendTableHeaderSeparatorLine(outputStream);

	// VALUES
    Position* position = getPosition();
	Point* point = &(position->pos);

	// X / Y
	appendDecfTableData(outputStream, point->x, TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, point->y, TRAJECTORY_Y_DEC_COLUMN_LENGTH);

	// Angle / Last Angle
	appendDecfTableData(outputStream, radToDeg(position->orientation), TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, radToDeg(position->initialOrientation), TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);

    // Hex
	appendHexFloat6TableData(outputStream, point->x, POSITION_DIGIT_MM_PRECISION, TRAJECTORY_X_HEX_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, point->y, POSITION_DIGIT_MM_PRECISION, TRAJECTORY_Y_HEX_COLUMN_LENGTH);
    
    // Notification
    TrajectoryInfo* trajectory = getTrajectory();
    // -> Parameters
    appendBoolAsStringTableData(outputStream, trajectory->notifyChange, TRAJECTORY_LAST_NOTIFY_ENABLED_COLUMN_LENGTH);
	appendDecfTableData(outputStream, trajectory->thresholdDistance, TRAJECTORY_LAST_NOTIFY_DISTANCE_THRESHOLD_COLUMN_LENGTH);
	appendDecfTableData(outputStream, radToDeg(trajectory->thresholdAngleRadian), TRAJECTORY_LAST_NOTIFY_ANGLE_RADIAN_THRESHOLD_COLUMN_LENGTH);
    // -> Values
    Position* lastNotificationPosition = &(trajectory->lastNotificationPosition);
    Point* lastNotificationPoint = &(lastNotificationPosition->pos);
	appendDecfTableData(outputStream, lastNotificationPoint->x, TRAJECTORY_LAST_NOTIFY_X_DEC_COLUMN_LENGTH);
    appendDecfTableData(outputStream, lastNotificationPoint->y, TRAJECTORY_LAST_NOTIFY_Y_DEC_COLUMN_LENGTH);
    appendDecfTableData(outputStream, lastNotificationPosition->orientation, TRAJECTORY_LAST_NOTIFY_ANGLE_DEC_COLUMN_LENGTH);

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

	appendStringHeader(outputStream, "lastLeft (pulse)", TRAJECTORY_LAST_LEFT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "lastRight (pulse)", TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "lastAngle (deg)", TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH);

    appendStringHeader(outputStream, "left (Hex)", TRAJECTORY_LEFT_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "right (Hex)", TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH);

    
	appendEndOfTableColumn(outputStream, TRAJECTORY_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);

	// VALUES
	// Left / Right
	appendDecTableData(outputStream, getCoderValue(CODER_LEFT), TRAJECTORY_LEFT_DEC_COLUMN_LENGTH);
	appendDecTableData(outputStream, getCoderValue(CODER_RIGHT), TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH);


	// Last left / Right / Angle
    TrajectoryInfo* trajectoryInfo = getTrajectory();
	appendDecfTableData(outputStream, trajectoryInfo->lastLeft, TRAJECTORY_LAST_LEFT_COLUMN_LENGTH);
	appendDecfTableData(outputStream, trajectoryInfo->lastRight, TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH);
	appendDecfTableData(outputStream, radToDeg(trajectoryInfo->lastAngle), TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH);

	appendHex6TableData(outputStream, getCoderValue(CODER_LEFT), TRAJECTORY_LEFT_HEX_COLUMN_LENGTH);
	appendHex6TableData(outputStream, getCoderValue(CODER_RIGHT), TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, TRAJECTORY_LAST_COLUMN_LENGTH);

	// END OF TABLE
	appendTableHeaderSeparatorLine(outputStream);
}
