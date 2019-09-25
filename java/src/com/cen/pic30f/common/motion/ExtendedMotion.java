/*
 * $Id$
 * Ce fichier est confidentiel. Il est la propriété de :
 * Oalia SA
 * 38 Boulevard Henri Sellier
 * 92150 Suresnes, France
 * Tous droits réservés.
 */
package com.cen.pic30f.common.motion;

import com.cen.pic30f.common.math.Point;

/**
 * Interface corresponding to extendedMotion.h
 */
public interface ExtendedMotion {

    /**
     * Compute the value of bezier points, with the parametric value t.
     * 
     * @param bezierPoints the point which define the bezier curve
     * @param t value in [0..1]
     */
    Point computeBezierPoint(Point bezierPoints[], float t);

    /**
     * Compute the orientation of bezier points at the parametric value t.
     * 
     * @param bezierPoints the point which define the bezier curve
     * @param currentPoint the point which is already calculated
     * @param t value in [0..1]
     */
    float computeBezierOrientation(Point bezierPoints[], Point currentPoint, float t);

    /**
     * Compute the length of a bezier arc curve
     * 
     * @param bezierPoints the point which define the bezier curve
     */
    float computeBezierArcLength(Point bezierPoints[]);

    /**
     * Computes the distance between 2 points.
     * 
     * @param p0 the first point
     * @param p1 the second point
     */
    float distanceBetweenPoints(Point p0, Point p1);

    /**
     * Returns the distance length
     * 
     * @param t t between 0 and 1
     */
    float getDistanceLengths(float t, Point bezierPoints[]);

    /**
     * Computes the time at the distance.
     * 
     * @param distance the distance from which we must know the time
     * @return a value between 0 and 1 corresponding to the t parameter
     */
    float computeBezierTimeAtDistance(float distance);

    // DEBUG FUNCTION

    /**
     * Write into the serial port a point with the associated t value. It's very useful to debug.
     */
    void writePointAndDistance(float t, Point p, float d);

    /**
     * Write into the serial port the list of point for the bezier spline. It's very useful to debug.
     */
    void writeBezierSpline(Point bezierPoints[]);

}
