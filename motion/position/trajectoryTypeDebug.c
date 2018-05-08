#include "trajectoryTypeDebug.h"
#include "trajectoryType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned int appendTrajectoryTypeAsString(OutputStream* outputStream, enum TrajectoryType trajectoryType) {
    switch (trajectoryType) {
        case TRAJECTORY_TYPE_NONE: return appendString(outputStream, "NONE");
        case TRAJECTORY_TYPE_FORWARD: return appendString(outputStream, "FORWARD");
        case TRAJECTORY_TYPE_BACKWARD: return appendString(outputStream, "BACKWARD");
        case TRAJECTORY_TYPE_ROTATION: return appendString(outputStream, "ROTATION");
    }
    return appendString(outputStream, "UNKNOWN TRAJECTORY TYPE");
}

unsigned int addTrajectoryTypeTableData(OutputStream* outputStream,  enum TrajectoryType trajectoryType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendTrajectoryTypeAsString(outputStream, trajectoryType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}