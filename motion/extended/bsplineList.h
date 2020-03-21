#ifndef B_SPLINE_LIST_H
#define B_SPLINE_LIST_H

#include "bspline.h"

#include "../../common/2d/2d.h"

typedef struct {
    /** A pointer on an array of BSplineCurve. */
    BSplineCurve(*curves)[];
    /** The max length of the list. */
    unsigned int length;
    /** The pointer used to write Data (we write at the end). */
    unsigned int writeIndex;
    /** The pointer used to read (we read at the begin). */
    unsigned int readIndex;
} BSplineCurveList;

/**
 * Init the BSpline.
 * @param curveList the pointer on the curveList (simulates object programming)
 * @param curves an array of BSplineCurve to store value into the Curve List
 * @param length the length of the array
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 */
void initCurveList(BSplineCurveList* curveList, BSplineCurve(*curves)[], unsigned int length);

/**
 * Returns if a curve List is initialized or not.
 * @param curveList the pointer on curve List (simulates object programming)
 * @return true if the curve List is initialized, false else
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 */
bool isCurveListInitialized(BSplineCurveList* curveList);

/**
 * Clears the Curve List.
 * @param curveList the Curve List to clear (simulates object programming)
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 */
void clearCurveList(BSplineCurveList* curveList);

/**
 * Returns true if the curveList is full, false else.
 * @param curveList the Curve List (simulates object programming)
 * @return true if the curve List is full, false else
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 */
bool isCurveListFull(const BSplineCurveList* curveList);

/**
 * Returns true if the curveList is empty, false else.
 * @param curveList the Curve List (simulates object programming)
 * @return true if the curve List is empty, false else
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 */
bool isCurveListEmpty(const BSplineCurveList* curveList);

/**
 * Returns the number of elements.
 * @param curveList the Curve List (simulates object programming)
 * @return the number of elements.
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 */
int getCurveListElementsCount(const BSplineCurveList* curveList);

/**
 * Returns the total capacity to store Elements.
 * As we use a circular buffer, we only store n - 1 elements (where n is the size of the array), and not n, because if we use n, we cannot distinguish when buffer is empty or full (if readIndex == writeIndex).
 * @param curveList the Curve List (simulates object programming)
 * @return the total capacity to store Elements.
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 */
int getCurveListCapacity(const BSplineCurveList* curveList);

/**
 * Get and result the current Curve. Do not remove the current Curve (contrary to the buffer which removes when read)
 * @param curveList the Curve List (simulates object programming)
 * @return the current Curve
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 * @throws MOTION_BSPLINE_LIST_EMPTY if not enough Curve in the List
 */
BSplineCurve* getCurrentCurve(const BSplineCurveList* curveList);

/**
 * Shift the current read Pointer on the list to the next Curve.
 * @param curveList the Curve List (simulates object programming)
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 * @throws MOTION_BSPLINE_LIST_EMPTY if not enough Curve in the List
 */
void removeCurrentCurve(BSplineCurveList* curveList);

/**
 * Get the next curve, and shift the write Pointer.
 * @param curveList the Curve List (simulates object programming)
 * @return the next BSpline in which we must write
 * @throws MOTION_BSPLINE_LIST_NULL if the pointer is NULL
 * @throws MOTION_BSPLINE_LIST_FULL if not enough space
 */
BSplineCurve* getNextCurveToWrite(BSplineCurveList* curveList);

#endif
