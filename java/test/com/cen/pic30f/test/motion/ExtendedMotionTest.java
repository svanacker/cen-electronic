/*
 * $Id$
 * Ce fichier est confidentiel. Il est la propriété de :
 * Oalia SA
 * 38 Boulevard Henri Sellier
 * 92150 Suresnes, France
 * Tous droits réservés.
 */
package com.cen.pic30f.test.motion;

import com.cen.pic30f.common.emulator.PicEmulator;
import com.cen.pic30f.common.math.Point;
import com.cen.pic30f.common.motion.ExtendedMotion;
import com.cen.pic30f.common.motion.ExtendedMotionImpl;

/**
 * Implémentation d'un test sur les courbes de bézier avec un émulateur basique.
 */
public class ExtendedMotionTest extends PicEmulator {

    protected ExtendedMotion extendedMotion;

    public ExtendedMotionTest() {
        extendedMotion = new ExtendedMotionImpl();
    }

    public void test() {
        Point[] bezierPoints = new Point[4];
        bezierPoints[0] = new Point(0, 0);
        bezierPoints[1] = new Point(-1, 4);
        bezierPoints[2] = new Point(12, 5);
        bezierPoints[3] = new Point(10, 7);

        putString("bezierArcDistances:");
        println();
        putString("t\tx\ty\tdist\tdistAdd");
        println();
        float bezierArcLength = extendedMotion.computeBezierArcLength(bezierPoints);

        putString("bezierArcLength:");
        sendDecf(bezierArcLength);
        println();

        putString("Bezier points:");
        println();
        extendedMotion.writeBezierSpline(bezierPoints);

        putString("Distances");
        println();

        putString("IndexOfLargestValue");
        println();

        float distance1;
        float t1;
        putString("dist\tt1\tdist");
        println();
        for (distance1 = 0; distance1 < bezierArcLength; distance1 += bezierArcLength / 20.0f) {
            sendDec((long) (distance1 * 1000));
            putc('\t');

            // returns the time at the distance
            t1 = extendedMotion.computeBezierTimeAtDistance(distance1);
            sendDec((long) (t1 * 1000000));
            putc('\t');

            // computes the distance at t1 (inverse function)
            float distance = extendedMotion.getDistanceLengths(t1, bezierPoints);
            sendDec((long) (distance * 1000000));
            putc('\t');

            println();
        }
    }

    public static void main(String[] args) {
        ExtendedMotionTest test = new ExtendedMotionTest();
        test.test();
    }
}
