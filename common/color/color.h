#ifndef COLOR_H
#define COLOR_H

#include <stdbool.h>

/**
* Define a Color structure.
*/
typedef struct Color {
    unsigned int R;
    unsigned int G;
    unsigned int B;
} Color;

/**
 * Define a type of color which was detected.
 */
enum ColorType {
    /** No color was detected. */
    COLOR_TYPE_UNKNOWN = 0,
    /** Color is mainly "Red". */
    COLOR_TYPE_RED = 1,
    /** Color is mainly "Green". */
    COLOR_TYPE_GREEN = 2,
    /** Color is mainly "Orange" */
    COLOR_TYPE_ORANGE = 3,
    /** Color is mainly "Blue". */
    COLOR_TYPE_BLUE = 4
};

/**
* Determine if a color is in the Threshold values.
*/
bool isColorInRange(Color* color, 
    unsigned int rLowThreshold, unsigned int rHighThreshold,
    unsigned int gLowThreshold, unsigned int gHighThreshold,
    unsigned int bLowThreshold, unsigned int bHighThreshold);


#endif