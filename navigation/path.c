#include <stdlib.h>

#include "path.h"
#include "location.h"

#include "../common/commons.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

static PathData tmpPathData;

PathData* getTmpPathData() {
	return &tmpPathData;
}

inline void fillPathData(Location* location1,
					 Location* location2, 
					 int cost,
					 int controlPointDistance1,
					 int controlPointDistance2,
					 int angle1,
					 int angle2,
					 unsigned char accelerationFactor,
					 unsigned char speedFactor) {
	tmpPathData.location1 = location1;
	tmpPathData.location2 = location2;
	tmpPathData.controlPointDistance1 = controlPointDistance1;
	tmpPathData.controlPointDistance2 = controlPointDistance2;
	tmpPathData.angle1 = angle1;
	tmpPathData.angle2 = angle2;
	tmpPathData.cost = cost;
	tmpPathData.accelerationFactor = accelerationFactor;
	tmpPathData.speedFactor = speedFactor;
	tmpPathData.tmpOutgoing = FALSE;
}


BOOL pathContainsLocation(Path* path, Location* location) {
	// fill temporary values
	path->pathDataFunction();

	return tmpPathData.location1 == location || tmpPathData.location2 == location;
}

Location* getOtherEnd(Path* path, Location* location) {
	// fill temporary values
	path->pathDataFunction();
	if (tmpPathData.location1 == location) {
		return tmpPathData.location2;
	}
	if (tmpPathData.location2 == location) {
		return tmpPathData.location1;
	}
	return NULL;
}

void printPath(OutputStream* outputStream, Path* path) {
	// fill temporary values
	path->pathDataFunction();

	appendString(outputStream, "pathName=");
	appendString(outputStream, tmpPathData.location1->name);
	appendString(outputStream, "->");
	appendString(outputStream, tmpPathData.location2->name);

	appendStringAndDec(outputStream, ", cost=", tmpPathData.cost);
	appendStringAndDec(outputStream, ", outgoing=", path->tmpOutgoing);

	appendStringAndDec(outputStream, ", cp1=", tmpPathData.controlPointDistance1);
	appendStringAndDec(outputStream, ", cp2=", tmpPathData.controlPointDistance2);

	appendStringAndDec(outputStream, ", angle1=", getAngle1Path(path));
	appendStringAndDec(outputStream, ", angle2=", getAngle2Path(path));

	appendStringAndDec(outputStream, ", accFactor=", tmpPathData.accelerationFactor);
	appendStringAndDec(outputStream, ", speedFactor=", tmpPathData.speedFactor);

	println(outputStream);
}
