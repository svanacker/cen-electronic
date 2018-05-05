#include "asciiUtils.h"

#include "../../common/math/cenMath.h"

#include "../../common/error/error.h"

// Array of chars to do transformation
static char LINE_CHARS_ASCII_ARRAY[4] = { '|', '\\', '-', '/' };

/**
 * @private
*/
unsigned int getQuadran(float angleInRadian) {
    float angleBetween0AndPI = modPI(angleInRadian);

    // To get the quadran by cutting the float value
    unsigned int quadran = (unsigned int) (angleBetween0AndPI / (0.25f* PI));

    if (quadran < 0 || quadran >= 4) {
        quadran = 0;
    }

    return quadran;
}

char transformVerticalChar(float angleInRadian) {
    unsigned int quadran = getQuadran(angleInRadian);
    return LINE_CHARS_ASCII_ARRAY[quadran];
}

char transformAntiSlashChar(float angleInRadian) {
    unsigned int quadran = getQuadran(angleInRadian + 0.25f * PI);
    return LINE_CHARS_ASCII_ARRAY[quadran];
}

char transformHorizontalChar(float angleInRadian) {
    unsigned int quadran = getQuadran(angleInRadian + 0.5f * PI);
    return LINE_CHARS_ASCII_ARRAY[quadran];
}

char transformSlashChar(float angleInRadian) {
    unsigned int quadran = getQuadran(angleInRadian + 0.75f * PI);
    return LINE_CHARS_ASCII_ARRAY[quadran];
}