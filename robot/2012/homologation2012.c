#include "homologation2012.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../drivers/motion/motionDriver.h"
#include "../../drivers/motion/trajectoryDriver.h"
#include "../../drivers/strategy/strategyDriver.h"
#include "../../drivers/beacon/beaconReceiverDriver.h"

#include "../../motion/extended/bsplineMotion.h"
#include "../../motion/simple/simpleMotion.h"

#include "../../robot/2012/armDeviceInterface2012.h"
#include "../../robot/2012/armDriver2012.h"
#include "../../robot/opponent/robotSonarDetectorDevice.h"
#include "../../robot/opponent/opponentRobot.h"

#define     ANGLE_90            0x0384
#define        ANGLE_135            0x0546
#define        ANGLE_150            0x05DC
#define        ANGLE_180            0x0708
#define        ANGLE_NEG_90        0xFC7C
#define        ANGLE_NEG_110        0xFBB4

#define     X_BOTTLE             0x0730

#define     X_LINTEL_LEFT        0x294

// Symetric
#define     X_LINTEL_RIGHT         2000 - X_LINTEL_LEFT

/**
 * Define the initial Position
 */
void setInitialPosition(unsigned int color) {
    if (color) {
        trajectoryDriverSetAbsolutePosition(ROBOT_POSITION_VIOLET_X, ROBOT_POSITION_VIOLET_Y, ROBOT_POSITION_VIOLET_ANGLE);
    }
    else {
        trajectoryDriverSetAbsolutePosition(ROBOT_POSITION_RED_X, ROBOT_POSITION_RED_Y, ROBOT_POSITION_RED_ANGLE);
    }
}

// ----------------------------------------------------------- Moving Primitives ------------------------------------------------------

bool spline(int color, float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor) {
    // Violet = Bit set
    if (color) {
        return motionDriverBSplineAbsolute(x, y, angle, dist0, dist1, accelerationFactor, speedFactor);
    } else {
        return motionDriverBSplineAbsolute(x, GAME_BOARD_HEIGHT - y, 1800.0f - angle, dist0, dist1, accelerationFactor, speedFactor);
    }    
}

bool left(int color, float angle) {
    if (color) {
        return motionDriverLeft(angle);
    }
    else {
        return motionDriverRight(angle);
    }
}

bool right(int color, float angle) {
    if (color) {
        return motionDriverRight(angle);
    }
    else {
        return motionDriverLeft(angle);
    }
}

bool armDown(int color, int index) {
    bool result;
    if (color) {
        result = armDriver2012Down(index);
    }
    else {
        result = armDriver2012Down(index);
    }
    delaymSec(500);
    setReadyForNextMotion(true);
    return result;
}

bool armUp(int color, int index) {
    bool result;
    if (color) {
        result = armDriver2012Up(index);
    }
    else {
        result = armDriver2012Up(index);
    }
    delaymSec(500);
    setReadyForNextMotion(true);
    return result;
}

// ----------------------------------------------------------- Common Move -----------------------------------------------------------

void takeBullion1(int color) {
    spline(color, 0x0370, 0x0156, ANGLE_NEG_90, 0x40, 0x40, MOTION_SPEED_FACTOR_HIGH, MOTION_SPEED_FACTOR_HIGH);
}

void bullion1ToBottle1(int color) {
    spline(color, X_BOTTLE, 0x0280, ANGLE_180, 0xEC, 0xC0, MOTION_SPEED_FACTOR_HIGH, MOTION_SPEED_FACTOR_HIGH);
}

void bottle1ToFrontBottle2(int color) {
    spline(color, 0x05DC, 0x0800, 0x0450, 0x57, 0x0A, MOTION_SPEED_FACTOR_HIGH, MOTION_SPEED_FACTOR_HIGH);
}

void frontBottle2ToBottle2(int color) {
    spline(color, X_BOTTLE + 10, 0x076C, 0xF8F8, 0xE0, 0xF0, MOTION_SPEED_FACTOR_LOW, MOTION_SPEED_FACTOR_LOW);
}

void bottle2TakeCD(int color) {
    spline(color, 0x05A8, 0x02C8, 0xFAF6, 0x1B, 0x30, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
}

void takeCDToDropZone1(int color) {
    spline(color, 0x02F5, 0x00D5, ANGLE_NEG_90, 0x11, 0x26, MOTION_SPEED_FACTOR_HIGH, MOTION_SPEED_FACTOR_HIGH);
}

void cleanLintel1First(int color) {
    spline(color, 0x0482, 0x0320, 0xF8F8, 0xE3, 0xDF, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
}

void cleanLintel1Second(int color) {
    spline(color, X_LINTEL_LEFT, 0x0448, ANGLE_90, 0x24, 0x21, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
}

void backToReadyForLintel1(int color) {
    spline(color, X_LINTEL_LEFT, 0x02A0, ANGLE_90, 0xF0, 0xF0, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
}    

void takeLintelLeft(int color) {
    spline(color, X_LINTEL_LEFT, 0x055C, ANGLE_90, 0x0D, 0x46, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
}

void strategyBoard() {
    // Send next Step
    robotNextStep();
}

// ----------------------------------------------------------- Homologation 1 ---------------------------------------------------------

void homologation1(int color) {
    strategyBoard();
    return;

    unsigned int index = getMotionInstructionIndex();

    switch (index) {

        case 1:
            takeBullion1(color);
            break;
    }
}

// ----------------------------------------------------------- Homologation 2 ---------------------------------------------------------

void homologation2(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            takeBullion1(color);
            break;
        case 2:
            bullion1ToBottle1(color);
            break;
    }
}

// ----------------------------------------------------------- Homologation 3 ---------------------------------------------------------

void homologation3(int color) {
    // Send the opponentRobot position if it has the information.        
    strategyBoard();    
    return;

    /*
    unsigned int index = getMotionInstructionIndex();
    switch (index) {
        case 1:
            takeBullion1(color);
            break;
        case 2:
            bullion1ToBottle1(color);
            break;
        case 3:
            setSonarStatus(1);
            bottle1ToFrontBottle2(color);
            break;
        case 4:
            setSonarStatus(1);
            frontBottle2ToBottle2(color);
            break;
    }
    */
}

// ----------------------------------------------------------- Homologation 4 ---------------------------------------------------------

void homologation4(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            takeBullion1(color);
            break;
        case 2:
            // first bottle
            bullion1ToBottle1(color);
            break;
        case 3: // Goto near 2 bottle
            // setSonarStatus(0); // TODO
            bottle1ToFrontBottle2(color);
            break;
        case 4: // hit bottle 2
            // setSonarStatus(0);
            frontBottle2ToBottle2(color);
            break;
        case 5: // near right Lintel 1
            spline(color, X_LINTEL_RIGHT, 0x0580, ANGLE_NEG_90, 0x1E, 0x1E, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 6: // Open arm
            armDown(color, ARM_RIGHT);
            break;
        case 7: // Go to Drop Zone 1
            spline(color, 0x0402, 0x0115, ANGLE_NEG_90, 0x64, 0x32, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 8: // Close Arm
            armUp(color, ARM_RIGHT);
            break;
        case 9: // Out from Drom Zone 1
            // spline(color, 0x0315, 0x01A2, 0x04BA, 0xD9, 0xEC);
            spline(color, 0x0480, 0x0230, ANGLE_NEG_110, 0xE0, 0xE0, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 10:
            // 100° rotation
            right(color, 1000.0f);
            break;
        case 11: // Clean the CD to be able to take Lintel
            spline(color, X_LINTEL_LEFT - 50, 0x0440, ANGLE_90, 0x1A, 0x20, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 12: // Go back to open ARM
            spline(color, X_LINTEL_LEFT, 0x02A0, ANGLE_90, 0xF0, 0xF0, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 13: // Open ARM
            armDown(color, ARM_RIGHT);
            break;
        case 14: // take the left Lintel 1
            spline(color, X_LINTEL_LEFT, 0x055C, ANGLE_90, 0x0D, 0x46, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 15: // Rotation
            left(color, 1700.0f);
            break;
        case 16: // Close ARM
            armUp(color, ARM_RIGHT);
            break;
        case 17:
            // go back home
            spline(color, 0x0118, 0x016F, 0xFC7C, 0x33, 0x27, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 18:
            // go front home 1
            spline(color, 0x0208, 0x02C2, 0xFC7C, 0xB6, 0x35, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 19: // Open ARM
            armDown(color, ARM_RIGHT);
            break;
        case 20:
            // take lintel left 2
            spline(color, X_LINTEL_LEFT, 0x083C, ANGLE_90, 0x1E, 0x78, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 21: // Close ARM
            armUp(color, ARM_RIGHT);
            break;
        case 22:
            // take the 4 CD
            spline(color, 0x06A8, 0x05D5, 0x0FC7C, 0x3E, 0x53, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 23:
            // go back to drop Zone 2
            spline(color, 0x038F, 0x00F0, 0x0FC7C, 0x3C, 0x1E, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
    }
}


// ----------------------------------------------------------- Homologation 5 ---------------------------------------------------------

void homologation5_Totem(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            armDriver2012Down(ARM_LEFT);
            armDriver2012Down(ARM_RIGHT);
            delaymSec(1000);
            setReadyForNextMotion(true);
            break;
        case 2:
            motionDriverForward(500.0f);
            break;
        case 3:
            armDriver2012Up(ARM_LEFT);
            armDriver2012Up(ARM_RIGHT);
            break;

    }
}

void homologation6(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            takeBullion1(color);
            break;
        case 2:
            // first bottle
            spline(color, X_BOTTLE, 0x0280, ANGLE_180, 0xEC, 0xC0, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;
        case 3: // Goto near 2 bottle
            // setSonarStatus(0); // TODO
            bottle1ToFrontBottle2(color);
            break;
        case 4: // hit bottle 2
            // setSonarStatus(0);
            frontBottle2ToBottle2(color);
            break;
        case 5:
            bottle2TakeCD(color);
            break;
        case 6:
            takeCDToDropZone1(color);
            break;
        case 7:
            cleanLintel1First(color);
            break;
        case 8:
            cleanLintel1Second(color);
            break;
    }
}

void homologation7(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            takeBullion1(color);
            break;
        case 2:
            cleanLintel1First( color);
            break;
        case 3:
            cleanLintel1Second(color);
            break;
        case 4:    
            backToReadyForLintel1(color);
            break;
        case 5: // Open arm
            armDown(color, ARM_RIGHT);
            break;
        case 6:
            takeLintelLeft(color);
            break;
        case 7: // Rotation
            left(color, 1700.0f);
            break;
        case 8: // Close ARM
            armUp(color, ARM_RIGHT);
            break;
        case 9:
            // go back home
            spline(color, 0x0118, 0x016F, 0xFC7C, 0x33, 0x27, MOTION_SPEED_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL);
            break;

    }
}

void homologation(unsigned int homologationIndex, unsigned int color) {
    if (homologationIndex != 0) {
        // Wait after flag
        if (!isReadyForNextMotion()) {
            return;
        }
        // avoid two movement at the same time
        setReadyForNextMotion(false);

        // for next instruction
        incMotionInstructionIndex();
    }
    if (homologationIndex == 1) {
        homologation1(color);
    }
    else if (homologationIndex == 2) {
        homologation2(color);
    }
    else if (homologationIndex == 3) {
        homologation3(color);
    }
    else if (homologationIndex == 4) {
        homologation4(color);
    }
    else if (homologationIndex == 5) {
        homologation5_Totem(color);
    }
    else if (homologationIndex == 6) {
        homologation6(color);
    }
    else if (homologationIndex == 7) {
        homologation7(color);
    }
}

