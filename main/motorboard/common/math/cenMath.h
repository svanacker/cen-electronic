#ifndef CEN_MATH_H
#define CEN_MATH_H

#include <stdbool.h>
#include "../../common/commons.h"

#define PI 					3.1415926535f

#define _2_PI 				PI * 2.0f

#define PI_DIVIDE_BY_2 		PI / 2.0f

#define PI_DIVIDE_180 0.0174532925f
#define PI_DIVIDE_1800 0.00174532925f

#define DEG_90 900.0f

/**
 * Returns the absolute value of a value.
 * @param value the signed value
 * @return the absolute value of the value
 */
long absLong(signed long value);

/**
 * Limit the value by the maxValue either in positive or negative.
 * Ex: limit(100, 75) => 75
 * Ex: limit(40, 60) => 40
 * Ex: limit(-63, 50) => -50
 * @param value the value that we want to limit
 * @param maxValue the max Value which is the limit either positive or negative
 * @return the value limited by the maxValue either in positive or negative
 */
signed long limit(long value, long maxValue);

/**
 * Compares two float values and returns 1, 0 or -1 if a is
 * greater, equal or lower than b.
 * @param a a float value
 * @param b a float value
 * @return 1, 0 or -1
 */
signed int compareFloat(float a, float b);

/**
 * Returns the sign of a float value.
 * @param a a float value
 * @return -1 for a negative value, 1 for a positive value, 0 for a null value
 */
signed int getSign(float a);

/**
* Returns the min value
*/
int minInt(int value1, int value2);

/**
* Returns the max value
*/
int maxInt(int value1, int value2);

bool floatEquals(float value1, float value2);

bool floatEqualsZero(float value1);

/**
 * Do the modulo of a value between -PI and PI.
 */
float mod2PI(float value);

/**
 * Simple check sum.
 */
int stringChecksum(char* string);

#endif
