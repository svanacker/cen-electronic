#ifndef ALPHA_THETA_H
#define ALPHA_THETA_H

/**
 * Compute the Theta value from the left and right values of the wheel.
 * The Theta value is the average length of the robot (average of the left and right)
 * @param left the left value (in pulse) of the left wheel
 * @return theta value
 */
float computeTheta(float left, float right);

/**
 * Compute the Alpha value from the left and right values of the wheel.
 * The Alpha value is the average angle of the robot (difference between left and right)
 * @param left the left value (in pulse) of the left wheel
 * @param right the left value (in pulse) of the right wheel
 * @return alpha value
 */
float computeAlpha(float left, float right);

#endif
