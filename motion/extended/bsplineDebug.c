#include "bsplineDebug.h"

// For debug
#include "../../common/2d/2d.h"
#include "../../common/2d/2dDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#define SPLINE_DEFINITION_INDEX_COLUMN_LENGTH				4
#define SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH				8
#define SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH				8
#define SPLINE_DEFINITION_CURVE_LENGTH_COLUMN_LENGTH		9
#define SPLINE_DEFINITION_ACC_FACTOR_COLUMN_LENGTH		    4
#define SPLINE_DEFINITION_SPEED_FACTOR_COLUMN_LENGTH		3
#define SPLINE_DEFINITION_BACKWARD_COLUMN_LENGTH			3
#define SPLINE_DEFINITION_LAST_COLUMN_LENGTH		 	    0

void writeBSplineDefinitionTableHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Idx", SPLINE_DEFINITION_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P0.X", SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P0.Y", SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P1.X", SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P1.Y", SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P2.X", SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P2.Y", SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P3.X", SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendStringHeader(outputStream, "P3.Y", SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Lgth(mm)", SPLINE_DEFINITION_CURVE_LENGTH_COLUMN_LENGTH);
	appendStringHeader(outputStream, "a", SPLINE_DEFINITION_ACC_FACTOR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "s", SPLINE_DEFINITION_SPEED_FACTOR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Back", SPLINE_DEFINITION_BACKWARD_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SPLINE_DEFINITION_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void writeBSplineDefinitionRow(OutputStream* outputStream, unsigned int index, BSplineCurve* bSplineCurve) {
	appendDecTableData(outputStream, index, SPLINE_DEFINITION_INDEX_COLUMN_LENGTH);
	
	appendDecfTableData(outputStream, bSplineCurve->p0.x, SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->p0.y, SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->p1.x, SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->p1.y, SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->p2.x, SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->p2.y, SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->p3.x, SPLINE_DEFINITION_POINT_X_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->p3.y, SPLINE_DEFINITION_POINT_Y_COLUMN_LENGTH);

	appendDecfTableData(outputStream, bSplineCurve->curveLength, SPLINE_DEFINITION_CURVE_LENGTH_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->accelerationFactor, SPLINE_DEFINITION_ACC_FACTOR_COLUMN_LENGTH);
	appendDecfTableData(outputStream, bSplineCurve->speedFactor, SPLINE_DEFINITION_SPEED_FACTOR_COLUMN_LENGTH);
	appendBoolTableData(outputStream, bSplineCurve->backward, SPLINE_DEFINITION_BACKWARD_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SPLINE_DEFINITION_LAST_COLUMN_LENGTH);
}

