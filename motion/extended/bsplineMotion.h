#ifndef B_SPLINE_MOTION_H
#define B_SPLINE_MOTION_H

#include <stdbool.h>

#include "../pid/pidMotion.h"
#include "../extended/bspline.h"

// SPEED FACTOR

#define    MOTION_SPEED_FACTOR_MAX                15
#define    MOTION_SPEED_FACTOR_HIGH               10
#define    MOTION_SPEED_FACTOR_NORMAL            7
#define    MOTION_SPEED_FACTOR_LOW                4
#define    MOTION_SPEED_FACTOR_MIN                1

// ACCELERATION FACTOR

#define    MOTION_ACCELERATION_FACTOR_MAX        15
#define    MOTION_ACCELERATION_FACTOR_HIGH        10
#define    MOTION_ACCELERATION_FACTOR_NORMAL    7
#define    MOTION_ACCELERATION_FACTOR_LOW        4
#define    MOTION_ACCELERATION_FACTOR_MIN        1

void updateSimpleSplineWithDistance(BSplineCurve* spline, 
									float destX, float destY,
                                    float destAngle,
                                    float distance1, float distance2,
                                    unsigned char accelerationFactor, unsigned char speedFactor,
                                    bool relative);

/**
 * Go from the relative destination to the initial Position of the robot
 * Computes the bezier Point so that the curve is not to huge
 * @param relativeDestX the relative X destination point
 * @param relativeDestY the relative Y destination point
 * @param relativeDestAngle the relative Angle 
 * @param controlPointDistance1 the distance of P0->P1. If egal to 0.0f, the 
 * system determines the best distance to avoid too huge curve
 * @param controlPointDistance2 the distance of P2->P3. If egal to 0.0f, the 
 * system determines the best distance to avoid too huge curve
 */
void gotoSimpleSpline(PidMotion* pidMotion,
					  float relativeDestX,
                      float relativeDestY,
                      float relativeDestAngle,
                      float controlPointDistance1,
                      float controlPointDistance2,
                      unsigned int accelerationFactor,
                      unsigned int speedFactor,
                      bool relative
                    );

/**
* Go to a spline with indication of maxDerivative which indicates how the curve is huge
*/
void gotoSpline(PidMotion* pidMotion);


#endif