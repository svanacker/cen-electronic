#include "bsplineList.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/error/error.h"

/**
* Private Functions.
* @returns true if there is a problem, false else
*/
bool checkCurveListNotNull(const BSplineCurveList* curveList) {
    if (curveList == NULL) {
        writeError(MOTION_BSPLINE_LIST_NULL);
        return false;
    }
    return true;
}

void initCurveList(BSplineCurveList* curveList, BSplineCurve(*curves)[], unsigned int length) {
    if (!checkCurveListNotNull(curveList)) {
        return;
    }
    curveList->curves = curves;
    curveList->length = length;
}

bool isCurveListInitialized(BSplineCurveList* curveList) {
    if (curveList == NULL) {
        return false;
    }
    return curveList->length > 0;
}

bool isCurveListFull(const BSplineCurveList* curveList) {
    if (!checkCurveListNotNull(curveList)) {
        return false;
    }
    return ((curveList->writeIndex + 1) % curveList->length) == curveList->readIndex;
}

bool isCurveListEmpty(const BSplineCurveList* curveList) {
    return curveList->readIndex == curveList->writeIndex;
}

int getCurveListElementsCount(const BSplineCurveList* curveList) {
    int result = curveList->writeIndex - curveList->readIndex;
    if (result < 0) {
        result += curveList->length;
    }
    return result;
}

int getCurveListCapacity(const BSplineCurveList* curveList) {
    return curveList->length - 1;
}

BSplineCurve* getNextCurveToWrite(BSplineCurveList* curveList) {
    int isFull = isCurveListFull(curveList);
    if (!isFull) {
        BSplineCurve* result = (BSplineCurve*) curveList->curves;

        // Reset the BSpline
        initFirstTimeBSplineCurve(result);

        // Shift to the right cell index
        result += curveList->writeIndex;

        curveList->writeIndex++;
        curveList->writeIndex %= curveList->length;

        return result;
    }
    else {
        // We must log the problem
        writeError(MOTION_BSPLINE_LIST_FULL);
        // Print Curve List
        // printDebugBuffer(getErrorOutputStreamLogger(), buffer);
        return NULL;
    }
}

void removeCurrentCurve(BSplineCurveList* curveList) {
    if (isCurveListEmpty(curveList)) {
        return;
    }
    curveList->readIndex++;
    curveList->readIndex %= curveList->length;
}

BSplineCurve* getCurrentCurve(const BSplineCurveList* curveList) {
    int isEmpty = isCurveListEmpty(curveList);
    if (!isEmpty) {
        BSplineCurve* result = (BSplineCurve*)curveList->curves;
        result += curveList->readIndex;

        return result;
    }
    else {
        // We must log the problem
        writeError(MOTION_BSPLINE_LIST_EMPTY);
        return NULL;
    }
}

void clearCurveList(BSplineCurveList* curveList) {
    if (!checkCurveListNotNull(curveList)) {
        return;
    }
    curveList->writeIndex = 0;
    curveList->readIndex = 0;
}
