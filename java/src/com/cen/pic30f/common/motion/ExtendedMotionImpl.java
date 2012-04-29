/*
 * $Id$
 * Ce fichier est confidentiel. Il est la propriété de :
 * Oalia SA
 * 38 Boulevard Henri Sellier
 * 92150 Suresnes, France
 * Tous droits réservés.
 */
package com.cen.pic30f.common.motion;

import com.cen.pic30f.common.emulator.PicEmulator;
import com.cen.pic30f.common.math.Point;

/**
 * extendedMotion.c implementation in java to do simple tests.
 */
public class ExtendedMotionImpl extends PicEmulator implements ExtendedMotion {

    public static final int MAX_POINTS_BEZIER = 1000;

    public static final char CSV_SEPARATOR = '\t';

    float[] distanceLengths = new float[MAX_POINTS_BEZIER + 1];

    // DEBUG FUNCTION

    public void writePoint(Point p) {
        sendDec((long) (p.x * 1000));
        putc(CSV_SEPARATOR);

        sendDec((long) (p.y * 1000));
        putc(CSV_SEPARATOR);
    }

    public void writePointAndDistance(float t, Point p, float d) {
        sendDec((long) (t * 1000));
        putc(CSV_SEPARATOR);

        writePoint(p);

        sendDec((long) (d * 1000));

        println();
    }

    /**
     * Write into the serial port the list of point for the bezier spline. It's very useful to debug.
     */
    public void writeBezierSpline(Point bezierPoints[]) {
        float t = 0;
        for (t = 0; t < 1; t += 0.020) {
            Point p = computeBezierPoint(bezierPoints, t);
            float distance = distanceLengths[(int) (t * MAX_POINTS_BEZIER)];
            writePointAndDistance(t, p, distance);
        }
    }

    public Point computeBezierPoint(Point bezierPoints[], float t) {
        Point result = new Point();

        float t2 = t * t;
        float t3 = t2 * t;
        float l_t = (1 - t);
        float l_t2 = l_t * l_t;
        float l_t3 = l_t2 * l_t;

        // http://en.wikipedia.org/wiki/B%C3%A9zier_curve
        result.x =
                (bezierPoints[0].x * l_t3) + (3 * bezierPoints[1].x * t * l_t2) + (3 * bezierPoints[2].x * t2 * l_t)
                        + (bezierPoints[3].x * t3);
        result.y =
                (bezierPoints[0].y * l_t3) + (3 * bezierPoints[1].y * t * l_t2) + (3 * bezierPoints[2].y * t2 * l_t)
                        + (bezierPoints[3].y * t3);

        return result;
    }

    public float computeBezierOrientation(Point bezierPoints[], Point currentPoint, float t) {
        // We compute the next very nearly point
        Point nearNextPoint = computeBezierPoint(bezierPoints, t + 0.0001f);

        // Warning about orientation
        float diffY = nearNextPoint.y - currentPoint.y;
        float diffX = nearNextPoint.x - currentPoint.x;

        // note that the atan2 is atan2(y, x) and not atan2(x, y)
        float result = atan2f(diffY, diffX);

        // There is another method to compute the tangent of a bezier curve
        // see http://www.planetclegg.com/projects/WarpingTextToSplines.html

        return result;
    }

    public float distanceBetweenPoints(Point p0, Point p1) {
        float result;

        float diffX = (p1.x - p0.x);
        float diffY = (p1.y - p0.y);

        result = sqrt(diffX * diffX + diffY * diffY);

        return result;
    }

    public float computeBezierArcLength(Point bezierPoints[]) {
        boolean debug = true;
        float result = 0;

        Point previousPoint = bezierPoints[0];
        distanceLengths[0] = 0;

        int i;
        for (i = 1; i <= MAX_POINTS_BEZIER; i++) {
            float t = (float) i / (float) MAX_POINTS_BEZIER;

            if (debug) {
                sendDec((long) (t * 1000));
                putc(CSV_SEPARATOR);
            }

            Point p = computeBezierPoint(bezierPoints, t);
            writePoint(p);

            float distance = distanceBetweenPoints(previousPoint, p);
            if (debug) {
                sendDec((long) (distance * 1000));
                putc(CSV_SEPARATOR);
            }
            result += distance;
            distanceLengths[i] = result;

            previousPoint = p;

            if (debug) {
                sendDec((long) (result * 1000));
                println();
            }
        }

        return result;
    }

    public float getDistanceLengths(float t, Point bezierPoints[]) {
        int index = (int) (t * MAX_POINTS_BEZIER);
        if (index < MAX_POINTS_BEZIER) {
            return distanceLengths[index];
        } else {
            return -1;
        }
    }

    /**
     * Find the index in an array to find the nearest index of t which corresponds to that distance. The algorithme use
     * binary search to find the good index. So it converges very quickly : 10 iterations for 1024 elements (2^10)
     * http://www.planetclegg.com/projects/WarpingTextToSplines.html Ex : [0->0, 1->30, 2->50, 3->70, 4->120, 5->135,
     * 6->155, 7-<160] and distance = 140 fn(140, 0, 7), index=3, 70 > 140 ? NO fn(140, 3, 7), index=5, 135 > 140 ? NO
     * fn(140, 5, 7), index=6, 155 > 140 ? YES fn(140, 5, 6), index=5, 6 = 5 - 1 => distances[6] = 155 > distance =>
     * return 5
     */
    public int findIndexOfLargestValueSmallerThan(float distance, int lowIndex, int highIndex) {
        if (lowIndex == highIndex) {
            return highIndex;
        }
        if (highIndex == lowIndex + 1) {
            if (distanceLengths[highIndex] >= distance) {
                return lowIndex;
            } else {
                return highIndex;
            }
        }

        int index = (lowIndex + highIndex) / 2;

        if (distanceLengths[index] > distance) {
            return findIndexOfLargestValueSmallerThan(distance, lowIndex, index);
        } else {
            return findIndexOfLargestValueSmallerThan(distance, index, highIndex);
        }
    }

    /**
     * We want to compute the bezier time for a particular distance
     */
    public float computeBezierTimeAtDistance(float distance) {
        float result; // we are attempting to find t for u

        // the next function would be a binary search, for efficiency
        int index = findIndexOfLargestValueSmallerThan(distance, 0, MAX_POINTS_BEZIER);

        // if exact match, return t based on exact index
        if (distanceLengths[index] == distance) {
            // we do the proportion compute to transform [0..MAX_POINTS_BEZIER] index in [0..1] for t
            result = index / (float) (MAX_POINTS_BEZIER);
        } else { // need to interpolate between two points
            // TODO : Use a best interpolation algorithm
            float lengthBefore = distanceLengths[index];
            float lengthAfter = distanceLengths[index + 1];
            float segmentLength = lengthAfter - lengthBefore;

            // determine where we are between the 'before' and 'after' points.
            float segmentFraction = (distance - lengthBefore) / segmentLength;

            // add that fractional amount to t
            result = (index + segmentFraction) / (MAX_POINTS_BEZIER);
        }
        return result;
    }

}
