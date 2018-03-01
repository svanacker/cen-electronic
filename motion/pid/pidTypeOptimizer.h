#ifndef PID_TYPE_OPTIMIZER_H
#define PID_TYPE_OPTIMIZER_H

/**
 * Change the type of Pid for final approach so that we will be more accurate at the end
 * @param pidMotion
 * @param motionDefinition
 */
void changePidTypeIfFinalApproach(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
