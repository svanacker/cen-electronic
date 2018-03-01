#ifndef MOTION_PARAMETER_TYPE_H
#define MOTION_PARAMETER_TYPE_H

#define MOTION_PARAMETERS_COUNT            4

#include "../../common/io/outputStream.h"

/**
 * Defines the type of Motion Parameter (Forward / Backward / Rotation / One Wheel / Maintain Position)
 */
enum MotionParameterType {
    /** 
     * If the value is undefined
     */
    MOTION_PARAMETER_TYPE_UNDEFINED = -1,
    /**
     * The robot goes forward or backward.
     */
    MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD = 0,

    /**
     * The robot do a rotation.
     */
    MOTION_PARAMETER_TYPE_ROTATION = 1,

    /**
     * The robot do a rotation with One Wheel.
     */
    MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL = 2,

    /**
     * The robot must maintain a position.
     */
    MOTION_PARAMETER_TYPE_MAINTAIN_POSITION = 3
};

/**
 * Determine the type of motion by analysis of left and right instruction.
 * @param left instruction for left wheel
 * @param right instruction for right wheel
 * @return a type of Motion (Ex: MOTION_TYPE_ROTATION)
 */
enum MotionParameterType getMotionParameterType(float left, float right);

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
