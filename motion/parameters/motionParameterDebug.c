#include "motionParameterDebug.h"
#include "motionParameterTypeDebug.h"
#include "motionParameter.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// DEBUG

#define MOTION_PARAMETERS_DEBUG_IDX_COLUMN_LENGTH	            5
#define MOTION_PARAMETERS_DEBUG_MOTION_TYPE_COLUMN_LENGTH	    25
#define MOTION_PARAMETERS_DEBUG_SPEED_HEX_COLUMN_LENGTH	        12
#define MOTION_PARAMETERS_DEBUG_ACCELERATION_HEX_COLUMN_LENGTH	12
#define MOTION_PARAMETERS_DEBUG_SPEED_DEC_COLUMN_LENGTH	        12
#define MOTION_PARAMETERS_DEBUG_ACCELERATION_DEC_COLUMN_LENGTH	12
#define MOTION_PARAMETERS_DEBUG_LAST_COLUMN_LENGTH	            20

/**
* Private.
*/
void printMotionParameterHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);

    // First Header Line
	appendStringHeader(outputStream, "idx", MOTION_PARAMETERS_DEBUG_IDX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "motionType", MOTION_PARAMETERS_DEBUG_MOTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "speed (Hex)", MOTION_PARAMETERS_DEBUG_SPEED_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "a (Hex)", MOTION_PARAMETERS_DEBUG_ACCELERATION_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "speed (Dec)", MOTION_PARAMETERS_DEBUG_SPEED_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "a (Dec)", MOTION_PARAMETERS_DEBUG_ACCELERATION_DEC_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_PARAMETERS_DEBUG_LAST_COLUMN_LENGTH);

    // Second Header Line
    appendStringHeader(outputStream, "", MOTION_PARAMETERS_DEBUG_IDX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", MOTION_PARAMETERS_DEBUG_MOTION_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm / sec", MOTION_PARAMETERS_DEBUG_SPEED_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm / sec^2", MOTION_PARAMETERS_DEBUG_ACCELERATION_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm / sec", MOTION_PARAMETERS_DEBUG_SPEED_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm / sec^2", MOTION_PARAMETERS_DEBUG_ACCELERATION_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_PARAMETERS_DEBUG_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}

void printMotionParameter(OutputStream* outputStream, int index, MotionParameter* motionParameter) {
	appendDecTableData(outputStream, index, MOTION_PARAMETERS_DEBUG_IDX_COLUMN_LENGTH);
	enum MotionParameterType motionParameterType = (enum MotionParameterType) index;
	addMotionParameterTypeTableData(outputStream, motionParameterType, MOTION_PARAMETERS_DEBUG_MOTION_TYPE_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, motionParameter->speed, MOTION_PARAMETERS_SPEED_DIGIT, MOTION_PARAMETERS_DEBUG_SPEED_HEX_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, motionParameter->a, MOTION_PARAMETERS_ACCELERATION_DIGIT, MOTION_PARAMETERS_DEBUG_ACCELERATION_HEX_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionParameter->speed, MOTION_PARAMETERS_DEBUG_SPEED_HEX_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionParameter->a, MOTION_PARAMETERS_DEBUG_ACCELERATION_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_PARAMETERS_DEBUG_LAST_COLUMN_LENGTH);
}

void printMotionParameterList(OutputStream* outputStream) {
	printMotionParameterHeader(outputStream);
	enum MotionParameterType motionType;
	int i = 0;
	for (motionType = 0; motionType < MOTION_PARAMETERS_COUNT; motionType++) {
		MotionParameter* motionParameter = getMotionParameters(motionType);
		printMotionParameter(outputStream, i, motionParameter);
		i++;
	}
	appendTableHeaderSeparatorLine(outputStream);
}