#ifndef MOTION_END_DETECTION_DEBUG_H
#define MOTION_END_DETECTION_DEBUG_H

#include "../../../common/io/outputStream.h"
#include "../pidMotion.h"
#include "../parameters/pidParameter.h"
#include "motionEndDetection.h"
#include "parameters/motionEndDetectionParameter.h"

/**
 * Print a table with all end Motion Detection Parameter
 * @param outputStream the stream in which we write
 * @param parameter the pointer on the structure containing the parameters
 */
void printMotionEndDetectionParameter(OutputStream* outputStream, MotionEndDetectionParameter* parameter);

/**
 * Print an end detection status as a String of chars with a fixed length.
 * @param outputStream the stream in which we write
 * @param motionEndDetectionRegister the register to write
 * @return number of char written
 */
unsigned int appendMotionEndDetectionStatusRegister(OutputStream* outputStream, MotionEndDetectionStatusRegister motionEndDetectionStatusRegister);

/**
 * Print an end detection status as a String of chars with a fixed length in a table data compatible way
 * @param outputStream the stream in which we write
 * @param motionEndDetectionRegister the register to write
 * @param columnSize the width of the column to align data
 * @return number of char written
 */
unsigned int appendMotionEndDetectionStatusRegisterTableData(OutputStream* outputStream,
        MotionEndDetectionStatusRegister motionEndDetectionStatusRegister,
        unsigned int columnSize);

#endif
