#ifndef MOTION_PARAMETER_TYPE_DEBUG_H
#define MOTION_PARAMETER_TYPE_DEBUG_H

#include "motionParameterType.h"

#include "../../common/io/outputStream.h"

/**
 * Append the MotionParameterType as a string into an outputStream
 * @param motionParameterType the type of motionParameter
 * @param outputStream the output stream
 * @return how many char have been written in the outputStream
 */
unsigned char appendMotionParameterTypeAsString(OutputStream* outputStream, enum MotionParameterType motionParameterType);

/**
 * Add a motion Parameter Type value in a column.
 */
unsigned int addMotionParameterTypeTableData(OutputStream* outputStream, enum MotionParameterType motionParameterType, int columnSize);

#endif
