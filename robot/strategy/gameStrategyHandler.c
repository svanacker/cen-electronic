#include <math.h>
#include <stdlib.h>

#include "gameStrategyHandler.h"

#include "gameStrategyContext.h"

#include "nextGameStrategyItemComputer.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/singleBSpline.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/navigation.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../drivers/motion/motionDriver.h"

#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/2012/strategy2012Utils.h"

// Strategy Context
static GameStrategyContext strategyContext;

// Strategy timer
static Timer* strategyTimer;

/** The index of the timer (used to manage path availability). */
#define STRATEGY_TIMER_INDEX 18

GameStrategyContext* getStrategyContext() {
	return &strategyContext;
}

#define ANGLE_180 1800
#define ANGLE_360 3600

void strategyTimerCallback() {
	if (strategyTimer->time > strategyContext.timeSinceLastCollision + RESET_OBSTACLE_COLLISION_TIME_SECOND) {
		#ifdef DEBUG_OPPONENT_ROBOT
			OutputStream* logStream = getOutputStreamLogger(INFO);
			appendString(logStream, "resetAllPathsAsAvailable\n");
		#endif
		resetAllPathsAsAvailable();
		// remove the last Obstacle position
		strategyContext.lastObstaclePosition.x = 0;
		strategyContext.lastObstaclePosition.y = 0;
	}
}

void initStrategyHandler() {
	// strategyTimer = addTimer(STRATEGY_TIMER_INDEX, TIME_DIVISER_1_HERTZ, &strategyTimerCallback);
}

/**
 * Clears the current path and actions.
 * Useful when we want to cancel a target or go out from a target.
 */
void clearCurrentTarget() {
	clearLocationList(&(strategyContext.currentTrajectory));
	strategyContext.currentTarget = NULL;
	strategyContext.currentTargetAction = NULL;
}

/**
 * @private
 */
void findNextTarget() {
	appendString(getOutputStreamLogger(DEBUG), "findNextTarget\n");

	unsigned int targetHandledCount = getTargetHandledCount();
	if (targetHandledCount >= strategyContext.maxTargetToHandle) {
		clearCurrentTarget();
		appendStringAndDec(getOutputStreamLogger(DEBUG), "Reach Max Target To Handle:", targetHandledCount);
		println(getOutputStreamLogger(DEBUG));
		return;
	}

	// global points
	LocationList* navigationLocationList = getNavigationLocationList();

	Point* robotPosition = &(strategyContext.robotPosition);
	// Find nearest location
	strategyContext.nearestLocation = getNearestLocation(navigationLocationList, robotPosition->x, robotPosition->y);

	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "\tNearest Location:");	
		printLocation(getOutputStreamLogger(DEBUG), strategyContext.nearestLocation);
		appendString(getOutputStreamLogger(DEBUG), "\tcomputeBestNextTargetAction:\n");	
	#endif

	// Find best Target, store LocationList in the context in currentTrajectory
	computeBestNextTarget(&strategyContext);

	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "\t\tbestTarget:");
		if (strategyContext.currentTarget != NULL) {
			printGameTarget(getOutputStreamLogger(DEBUG), strategyContext.currentTarget, FALSE);
		}
		else {
			appendString(getOutputStreamLogger(DEBUG), "NULL\n");
		}
		appendString(getOutputStreamLogger(DEBUG), "\t\tbestTargetAction:");
		if (strategyContext.currentTargetAction != NULL) {
			printGameTargetAction(getOutputStreamLogger(DEBUG), strategyContext.currentTargetAction, FALSE);
		}
		else {
			appendString(getOutputStreamLogger(DEBUG), "NULL\n");
		}
	#endif
}

void markTargetAsHandled() {
	// mark the target as unavailable
	strategyContext.currentTarget->status = TARGET_HANDLED;
	// reset current Target
	strategyContext.currentTarget = NULL;
	strategyContext.currentTargetAction = NULL;
	incTargetHandledCount();
}

void markTargetInUse() {
	// mark the target as being used
	strategyContext.currentTarget->status = TARGET_INUSE;
}

/**
 * Execute the target actions, and return TRUE if there is a an action called, FALSE else
 * @private
 */
BOOL executeTargetActions() {
	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "executeTargetActions\n");
	#endif

	markTargetInUse();

	GameTargetAction* targetAction = strategyContext.currentTargetAction;
	GameTargetActionItemList* actionItemList = targetAction->actionItemList;
	if (actionItemList == NULL) {
		#ifdef DEBUG_STRATEGY_HANDLER
			appendString(getOutputStreamLogger(DEBUG), "-> no actions for this target\n");
		#endif
		markTargetAsHandled();
		return FALSE;
	}

	// There is actionItem in progress
	if (actionItemList != NULL && targetActionItemListHasNext(actionItemList)) {
		GameTargetActionItem* actionItem = targetActionItemListNext(actionItemList);

		#ifdef DEBUG_STRATEGY_HANDLER
			printGameTargetActionItem(getOutputStreamLogger(DEBUG), actionItem);
		#endif

		// Do the action item
		actionItem->actionItemFunction();
		return TRUE;
	}
	else {
		markTargetAsHandled();
		// we do nothing
		return FALSE;
	}
	return TRUE;
}

void motionGoLocation(Location* location, 
					int angle,
					int controlPointDistance1, int controlPointDistance2,
					int accelerationFactor, int speedFactor ) {

	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "motionGoLocation:goto:");	
		printLocation(getOutputStreamLogger(DEBUG), location);
	#endif

	angle = changeAngleForColor(angle);
	motionDriverBSplineAbsolute(location->x, location->y,
								angle, 
								controlPointDistance1, controlPointDistance2,
								accelerationFactor, speedFactor);

	// Simulate as if the robot goes to the position with a small error
	#ifdef SIMULATE_ROBOT
		strategyContext.robotPosition.x = location->x + 1;
		strategyContext.robotPosition.y = location->y + 1;
	#endif
}

int mod3600(int value) {
	if (value < - ANGLE_180) {
		return (value + ANGLE_360);
	} else if (value >= ANGLE_180) {
		return (value - ANGLE_360);
	}
	return value;
}

void rotateAbsolute(int angle) {
	angle = changeAngleForColor(angle);
	GameStrategyContext* strategyContext = getStrategyContext();
	int robotAngle = strategyContext->robotAngle;
	int diff = mod3600(angle - robotAngle);
	/*
	if (abs(diff) < ANGLE_ROTATION_MIN) {
		return;
	}
	*/

	#ifdef DEBUG_STRATEGY_HANDLER
		appendStringAndDec(getOutputStreamLogger(DEBUG), "rotateAbsolute:angle:", diff);	
		appendString(getOutputStreamLogger(DEBUG), " ddeg\n");
	#endif
	if (diff == 0) {
		// instruction with 0 does not notify position.
		diff = 1;
	}
	if (diff > 0) {
		motionDriverLeft(diff);
	} else {
		motionDriverRight(-diff);
	}

	// Simulate as if the robot goes to the position with a small error
	#ifdef SIMULATE_ROBOT
		strategyContext->robotAngle += diff;
	#endif
}

BOOL motionRotateToFollowPath(PathDataFunction* pathDataFunction, BOOL reversed) {
	pathDataFunction();

	int angle;
	if (reversed) {
		PathData* pathData = getTmpPathData();
		if (pathData->mustGoBackward) {
			angle = getAngle2Path(pathDataFunction);
		} else {
			angle = mod3600(ANGLE_180 + getAngle2Path(pathDataFunction));
		}
	} else {
		angle = getAngle1Path(pathDataFunction);
	}

	int diff = mod3600(angle - strategyContext.robotAngle);
	if (abs(diff) < ANGLE_ROTATION_MIN) {
		return FALSE;
	}

	#ifdef DEBUG_STRATEGY_HANDLER
		appendStringAndDec(getOutputStreamLogger(DEBUG), "motionRotateToFollowPath:angle:", diff);	
		appendString(getOutputStreamLogger(DEBUG), " ddeg\n");
	#endif

	if (diff > 0) {
		motionDriverLeft(diff);
	} else {
		motionDriverRight(-diff);
	}

	// Simulate as if the robot goes to the position with a small error
	#ifdef SIMULATE_ROBOT
		strategyContext.robotAngle += diff;
	#endif

	return TRUE;
}

void motionFollowPath(PathDataFunction* pathDataFunction, BOOL reversed) {
	pathDataFunction();
	PathData* pathData = getTmpPathData();

	Location* location;
	int angle;
	signed char cp1;
	signed char cp2;
	if (reversed) {
		location = pathData->location1;
		if (pathData->mustGoBackward) {
			// reverse the trajectory by going backward
			angle = getAngle1Path(pathDataFunction);
			cp1 = -pathData->controlPointDistance2;
			cp2 = -pathData->controlPointDistance1;
		} else {
			// reverse the trajectory symmetrically
			angle = mod3600(ANGLE_180 + getAngle1Path(pathDataFunction));
			cp1 = pathData->controlPointDistance2;
			cp2 = pathData->controlPointDistance1;
		}
	} else {
		location = pathData->location2;
		angle = getAngle2Path(pathDataFunction);
		cp1 = pathData->controlPointDistance1;
		cp2 = pathData->controlPointDistance2;
	}

	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "motionFollowPath:goto:");	
		printLocation(getOutputStreamLogger(DEBUG), location);
	#endif

	// cast to unsigned, negative signed char send 00
	motionDriverBSplineAbsolute(location->x, location->y, angle, (unsigned char) cp1, (unsigned char) cp2,
								pathData->accelerationFactor, pathData->speedFactor);

	// Simulate as if the robot goes to the position with a small error
	#ifdef SIMULATE_ROBOT
		strategyContext.robotPosition.x = location->x + 1;
		strategyContext.robotPosition.y = location->y + 1;
		strategyContext.robotAngle = angle;
	#endif
}

/**
* Handle the trajectory and return TRUE if we go to a location, FALSE else.
* @private
*/
BOOL handleCurrentTrajectory() {
	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "handleCurrentTrajectory\n");	
	#endif

	LocationList* currentTrajectory = &(strategyContext.currentTrajectory);

	#ifdef DEBUG_STRATEGY_HANDLER
		// printLocationList(getOutputStreamLogger(DEBUG), "currentTrajectory:", currentTrajectory);	
	#endif

	if (currentTrajectory == NULL || currentTrajectory->size < 2) {
		#ifdef DEBUG_STRATEGY_HANDLER
			appendString(getOutputStreamLogger(DEBUG), "no more locations to reach\n");	
		#endif

		// no more locations to reach
		clearLocationList(currentTrajectory);
		return FALSE;
	}

	Location* start = getLocation(currentTrajectory, 0);
	Location* end = getLocation(currentTrajectory, 1);
	BOOL reversed;
	PathDataFunction* pathDataFunction = getPathOfLocations(getNavigationPathList(), start, end, &reversed);

	// Follows the path
	if (!motionRotateToFollowPath(pathDataFunction, reversed)) {
		motionFollowPath(pathDataFunction, reversed);
		removeFirstLocation(currentTrajectory);
	}
	return TRUE;
}

inline float deciDegreesToRad(int ddegrees) {
	return ddegrees * (PI / 1800.0);
}

void computePoint(Point* ref, Point* cp, int distance, int angle) {
	float a = deciDegreesToRad(angle);
	float dca = cosf(a) * distance;
	float dsa = sinf(a) * distance;
	cp->x = ref->x + dca;
	cp->y = ref->y + dsa;
}

BOOL isColliding(Point* path, Point* obstacle) {
	float d = distanceBetweenPoints(path, obstacle);
	BOOL result = (d < DISTANCE_OPPONENT_TO_PATH);
	return result;
}

BOOL isValidLocation(Point* p) {
	return (p->x !=0) && (p->y != 0);
}

/**
 * Control point distance to mm.
 */
inline int cpToDistance(signed char d) {
	return (d * 10);
}

/**
 * Loop on a pathDataFunction, to know if the path has an intersection with the opponentRobotPosition.
 * @private
 */
BOOL isPathAvailable(PathDataFunction* pathDataFunction) {
	pathDataFunction();
	PathData* pathData = getTmpPathData();
	BSplineCurve* curve = getSingleBSplineCurve();
	Point* p0 = curve->p0;
	p0->x = pathData->location1->x;
	p0->y = pathData->location1->y;
	Point* p3 = curve->p3;
	p3->x = pathData->location2->x;
	p3->y = pathData->location2->y;
	int angle1 = getAngle1Path(pathDataFunction);
	int angle2 = getAngle2Path(pathDataFunction);
	int d1 = cpToDistance(pathData->controlPointDistance1);
	int d2 = cpToDistance(-pathData->controlPointDistance2);
	computePoint(p0, curve->p1, d1, angle1);
	computePoint(p3, curve->p2, d2, angle2);

	int i;
	Point p;
	Point* opponentRobotPosition = &(strategyContext.opponentRobotPosition);
	Point* lastObstaclePosition = &(strategyContext.lastObstaclePosition);
	BOOL opponentPresent = isValidLocation(opponentRobotPosition);
	BOOL obstaclePresent = isValidLocation(lastObstaclePosition);
	for (i = 0; i < 10; i++) {
		computeBSplinePoint(curve, 0.1 * i, &p);
		// checking opponent
		if (opponentPresent && isColliding(&p, opponentRobotPosition)) {
			return FALSE;
		}
		// checking last obstacle
		if (obstaclePresent && isColliding(&p, lastObstaclePosition)) {
			return FALSE;
		}
	}
	return TRUE;
}

BOOL mustComputePaths() {
	Point* opponentRobotPosition = &(strategyContext.opponentRobotPosition);
	Point* lastObstaclePosition = &(strategyContext.lastObstaclePosition);
	BOOL opponentPresent = isValidLocation(opponentRobotPosition);
	BOOL obstaclePresent = isValidLocation(lastObstaclePosition);

	return opponentPresent || obstaclePresent;

	// TODO
	// Case when the robot position is detected himself as the opponent robot !!!
	// All paths will be marked as unavailable, but the robot will try the path even (cost is only more huge)
}

void updatePathsAvailability() {
	#ifdef DEBUG_OPPONENT_ROBOT
		OutputStream* logStream = getOutputStreamLogger(INFO);
		appendString(logStream, "\nUpdating available paths");
	//	printGameStrategyContext(logStream, getStrategyContext());
	#endif

	BOOL computePath = mustComputePaths();
	if (!computePath) {
		appendString(logStream, "\nDon't compute Path !");
	}	
	PathList* paths = getNavigationPathList();
	int i;
	for (i = 0; i < paths->size; i++) {
		PathDataFunction* pathDataFunction = paths->paths[i];
		// by default, path is available
		BOOL available = TRUE;
		// Don't do the compute if it's not necessary
		if (computePath) {	
			available = isPathAvailable(pathDataFunction);
		}
		setPathAvailability(i, available);
	}

	#ifdef DEBUG_OPPONENT_ROBOT
		// LOG
		int k;
		for (k = 0; k < paths->size; k++) {
			PathDataFunction* pathDataFunction = paths->paths[k];
			pathDataFunction();
			PathData* data = getTmpPathData();
			if (!getPathAvailability(k)) {
				appendString(logStream, "\n");
				appendString(logStream, data->location1->name);
				appendString(logStream, "->");
				appendString(logStream, data->location2->name);
				appendString(logStream, ": UNAVAILABLE");		
			}
		}
		appendString(logStream, "\n");
	#endif
}

void setLastObstaclePosition() {
	Point* robotPosition = &(strategyContext.robotPosition);
	Point* lastObstaclePosition = &(strategyContext.lastObstaclePosition);
	int angle = strategyContext.robotAngle;
	computePoint(robotPosition, lastObstaclePosition, DISTANCE_OBSTACLE, angle);
}

void handleCollision() {
	// Mark the timer.
	if (strategyTimer != NULL) {
		strategyContext.timeSinceLastCollision = strategyTimer->time;
	}
	#ifdef DEBUG_STRATEGY_HANDLER
		appendStringAndDec(getOutputStreamLogger(DEBUG), "\nCollision at time:", strategyContext.timeSinceLastCollision);	
		appendString(getOutputStreamLogger(DEBUG), "\nhandleCollision");	
	#endif
	
	// Clears the current path and actions
	clearCurrentTarget();

	setLastObstaclePosition();
	updatePathsAvailability();
}

BOOL nextStep() {
	unsigned int counter = 0;
	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "nextStep\n");	
	#endif
	while (1) {
		counter++;
		#ifdef DEBUG_STRATEGY_HANDLER
			appendStringAndDec(getOutputStreamLogger(DEBUG), "nextStep=>", counter);	
			println(getOutputStreamLogger(DEBUG));
		#endif
		GameTargetAction* targetAction = strategyContext.currentTargetAction;
	
		if (getLocationCount(&(strategyContext.currentTrajectory)) != 0) {
			if (!handleCurrentTrajectory()) {
				continue;
			}
			return TRUE;
		}
		else if (targetAction != NULL) {
			if (!executeTargetActions()) {
				// we will return on a different condition.
				continue;
			}
			return TRUE;
		}
		else if (targetAction == NULL) {
			// no target, search a new one
			findNextTarget();
			if (strategyContext.currentTarget == NULL) {
				#ifdef DEBUG_STRATEGY_HANDLER
					appendString(getOutputStreamLogger(DEBUG), "no more targets -> stopping");
				#endif
				clearCurrentTarget();
				return FALSE;
			}
			// Next target created a new current trajectory
			if (getLocationCount(&(strategyContext.currentTrajectory)) != 0) {
				if (!handleCurrentTrajectory()) {
					continue;
				}
				return TRUE;
			}
		} else {
			if (!executeTargetActions()) {
				// we will return on a different condition.
				continue;
			}
			return TRUE;
		}
	}
	return TRUE;
}


