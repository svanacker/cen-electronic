#include "gameboardBSplinePrint.h"

#include "gameboard.h"
#include "gameboardElement.h"

#include "../../motion/extended/bspline.h"

/**
* BSpline print function.
*/
char bSplinePrint(int column, int line, BSplineCurve* bSplineCurve, char c) {
    Point p;
    float t;
    char result = CHAR_NO_DRAW;
    for (t = 0.0f; t < 1.0f; t += 0.01f) {
        computeBSplinePoint(bSplineCurve, t, &p);
        result = pointPrint(column, line, (int) p.x, (int) p.y, c);
        if (result != CHAR_NO_DRAW) {
            return result;
        }
    }
    return result;
}