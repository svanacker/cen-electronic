#ifndef PID_MOTION_TYPE_H
#define PID_MOTION_TYPE_H

/**
 * Store if the motion is a bspline curve or a classical (rotation / forward) move.
 */
enum PidMotionType {
	/**
	* The type is not defined so that we could know if pidMotionDefinition is not defined.
	*/
	MOTION_TYPE_UNDEFINED,

	/**
	* Classical Move: rotation / forward
	*/
	MOTION_TYPE_NORMAL,

	/**
	* Use of BSpline.
	*/
	MOTION_TYPE_BSPLINE
};

#endif

