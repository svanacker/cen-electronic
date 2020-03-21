#include "gameboardBSplinePrint.h"

#include "gameboard.h"
#include "gameboardElement.h"

#include "../../motion/extended/bspline.h"

/**
 * BSpline print function.
 */
void bSplinePrint(GameBoard* gameBoard, BSplineCurve* bSplineCurve, unsigned char c) {
    Point p;
    float t;
    for (t = 0.0f; t < 1.0f; t += 0.01f) {
        computeBSplinePoint(gameBoard->gameBoardCurve, t, &p);
        drawPointCoordinates(gameBoard, p.x, p.y, c);
    }
}