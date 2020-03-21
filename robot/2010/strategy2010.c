/**
 * Strategy for 2010 edition of robot cup.
 */
#include "strategy2010.h"

#include "../../common/delay/delay30F.h"
#include "../../device/drivers/lcd.h"
#include "../../main/motorClient/motorClient.h"
#include "../../motion/simple/motion.h"
#include "../match/strategy.h"
#include "../robot.h"

#include "tomatoe2010.h"
#include "pliers2010.h"


// All distances are in mm

/** Distance between corn when we take a diagonale. */
#define DISTANCE_BETWEEN_CORN_MM 515

#define DISTANCE_BETWEEN_CORN_LEFT_RIGHT_MM     DISTANCE_BETWEEN_CORN_MM / 2

/** Distance to go between the mettalic sensor and plier. */
#define DISTANCE_SENSOR_PLIER       67

#define DISTANCE_TO_NEXT_CORN_IF_TAKEN      DISTANCE_BETWEEN_CORN_MM - DISTANCE_SENSOR_PLIER

/** Distance from the center point (start of every strategy) and the last point */
// #define DISTANCE_CENTER_LAST_POINT 2338 (OLD TRAJECTOIRE)
#define DISTANCE_CENTER_LAST_POINT 2672

#define DISTANCE_TO_FIRST_CORN 334

/** Time to down the sensor */
#define DOWN_SENSOR_TIME_MS 300

void unLoadTomatoeAndCorn() {

}

void goStartPoint() {
    // The robot is 
    // x : at 308 / 2 = 154
    // y : at 170 mm + 308 / 2 = 324
    // 

    // Old trajectoire
    /*
    forwardSimpleMMAndWait(622);
    rightSimpleMilliDegreeAndWait(15920 * getMatchSide());
     */
    forwardSimpleMMAndWait(415);
    rightSimpleMilliDegreeAndWait(60998 * getMatchSide());
}

void unLoadFromLastPoint() {
    leftSimpleDegreeAndWait(61 * getMatchSide());
    forwardSimpleMMAndWait(150);
    handleAndWaitMSec(2000);
    backwardSimpleMMAndWait(100);
    //    setTomatoeEnabled(0);
    if (isRobotMustStop()) {
        return;
    }

    unLoadTomatoeAndCorn();
}

void homologation2010() {
    goStartPoint();

    setTomatoeEnabled(1);

    // Go at the LAST_POINT
    forwardSimpleMMAndWait(DISTANCE_CENTER_LAST_POINT);

    unLoadFromLastPoint();

    stopRobot();
}

unsigned char takeCornIfNotBlack(int plierIndex) {
    downSensor(plierIndex);
    preparePlier(plierIndex);
    delaymSec(DOWN_SENSOR_TIME_MS);
    unsigned detected = isMetalDetected(plierIndex);
    upSensor(plierIndex);
    if (!detected) {
        //        setTomatoeEnabled(1);
        forwardSimpleMMAndWait(DISTANCE_SENSOR_PLIER);
        //        setTomatoeEnabled(0);
        if (isRobotMustStop()) {
            return CORN_BLACK_NOT_TAKEN;
        }

        takeAndLoadCorn(plierIndex);

        //        setTomatoeEnabled(1);

        return CORN_WHITE_TAKEN;
    } else {
        upPlier(plierIndex);
        notifyReached();
        return CORN_BLACK_NOT_TAKEN;
    }
}

/**
 * Detect a corn, take if white, and go forward if specified
 * Returns distance
 * @param forward if we go forward after
 */
signed long goDetectCornAndTakeLeftAndRight(unsigned char forward, unsigned char takeRight) {
    if (isRobotMustStop()) {
        return 0;
    }
    signed long result = 0;
    unsigned char leftPlierIndex = PLIER_LEFT_INDEX;
    unsigned char rightPlierIndex = PLIER_RIGHT_INDEX;
    // inverse the plier Index
    if (getMatchSide() == SIDE_BLUE) {
        leftPlierIndex = PLIER_RIGHT_INDEX;
        rightPlierIndex = PLIER_LEFT_INDEX;
    }

    // try to take the left corn
    unsigned char wasTaken = takeCornIfNotBlack(leftPlierIndex);
    if (!forward) {
        return result;
    }
    if (wasTaken == CORN_WHITE_TAKEN) {
        result += DISTANCE_SENSOR_PLIER;
        // We have advance of DISTANCE_SENSOR_PLIER
        if (takeRight) {
            // go to the right to detect plier
            result += forwardSimpleMMAndWait(DISTANCE_BETWEEN_CORN_LEFT_RIGHT_MM - DISTANCE_SENSOR_PLIER);
            wasTaken = takeCornIfNotBlack(rightPlierIndex);
            if (wasTaken == CORN_WHITE_TAKEN) {
                result += DISTANCE_SENSOR_PLIER;
                // right has been taken : go to the next left - SENSOR_PLIER
                result += forwardSimpleMMAndWait(DISTANCE_BETWEEN_CORN_LEFT_RIGHT_MM - DISTANCE_SENSOR_PLIER);
            } else {
                // right has not been taken : go to the next left 
                result += forwardSimpleMMAndWait(DISTANCE_BETWEEN_CORN_LEFT_RIGHT_MM);
            }
        }// we don't take the right
        else {
            // go to the next plier
            result += forwardSimpleMMAndWait(DISTANCE_TO_NEXT_CORN_IF_TAKEN);
        }
    }// we do not take the left
    else {
        if (takeRight) {
            result += forwardSimpleMMAndWait(DISTANCE_BETWEEN_CORN_LEFT_RIGHT_MM);
            wasTaken = takeCornIfNotBlack(rightPlierIndex);
            if (wasTaken) {
                result += DISTANCE_SENSOR_PLIER;
                // right has been taken : go to the next left - SENSOR_PLIER
                result += forwardSimpleMMAndWait(DISTANCE_BETWEEN_CORN_LEFT_RIGHT_MM - DISTANCE_SENSOR_PLIER);
            } else {
                // right has not been taken : go to the next left 
                result += forwardSimpleMMAndWait(DISTANCE_BETWEEN_CORN_LEFT_RIGHT_MM);
            }
        } else {
            // we do not take the right
            result += forwardSimpleMMAndWait(DISTANCE_BETWEEN_CORN_MM);
        }
    }

    return result;
}

void goNextCorn() {
    // TODO
}

void strategy2() {
    goStartPoint();

    forwardSimpleMMAndWait(DISTANCE_TO_FIRST_CORN);

    int i = 0;
    signed long distance = 0;
    for (i = 0; i < CORN_TO_TAKE_COUNT; i++) {
        distance += goDetectCornAndTakeLeftAndRight(i < CORN_TO_TAKE_COUNT - 1, i == 2 || i == 3);
    }
    forwardSimpleMMAndWait(DISTANCE_CENTER_LAST_POINT - DISTANCE_TO_FIRST_CORN - distance);

    if (isRobotMustStop()) {
        return;
    }

    unLoadFromLastPoint();

    stopRobot();
}

void strategy2010(unsigned char strategyIndex) {
    if (strategyIndex == STRATEGY_HOMOLOGATION) {
        homologation2010();
    } else if (strategyIndex == STRATEGY_2) {
        strategy2();
    } else {
        writeString("UNKNOWN STRATEGY !");
    }
}
