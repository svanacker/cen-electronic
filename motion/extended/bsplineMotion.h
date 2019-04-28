#ifndef B_SPLINE_MOTION_H
#define B_SPLINE_MOTION_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"

#include "../pid/pidMotion.h"
#include "../extended/bspline.h"

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
void gotoSpline(PidMotion* pidMotion,
					  float relativeDestX,
                      float relativeDestY,
                      float relativeDestAngle,
                      float controlPointDistance1,
                      float controlPointDistance2,
                      float accelerationFactor,
                      float speedFactor,
                      bool relative,
                      OutputStream* notificationOutputStream
                    );

#endif