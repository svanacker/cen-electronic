#include "homologation2012.h"

#include "../../common/delay/delay30F.h"
#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../drivers/motion/motionDriver.h"

#include "../../robot/2012/armDeviceInterface2012.h"
#include "../../robot/2012/armDriver2012.h"
#include "../../robot/robotSonarDetectorDevice.h"

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

BOOL spline(int color, float x, float y, float angle, float dist0, float dist1) {
	// Violet = Bit set
	if (color) {
		return motionDriverBSplineAbsolute(x, y, angle, dist0, dist1);
	} else {
		return motionDriverBSplineAbsolute(x, GAME_BOARD_HEIGHT - y, 1800.0f - angle, dist0, dist1);
	}	
}

BOOL left(int color, float angle) {
	if (color) {
		return motionDriverLeft(angle);
	}
	else {
		return motionDriverRight(angle);
	}
}

BOOL right(int color, float angle) {
	if (color) {
		return motionDriverRight(angle);
	}
	else {
		return motionDriverLeft(angle);
	}
}


// ----------------------------------------------------------- Homologation 1 ---------------------------------------------------------

void homologation1(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            spline(color, 0x0370, 0x0156, 0xFC7C, 0x40, 0x40);
            break;
    }
}

// ----------------------------------------------------------- Homologation 2 ---------------------------------------------------------

void homologation2(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            spline(color, 0x0370, 0x0156, 0xFC7C, 0x40, 0x40);
            break;
        case 2:
			spline(color, 0x0730, 0x0280, 0x0708, 0xF0, 0xC0);
            break;
    }
}

// ----------------------------------------------------------- Homologation 3 ---------------------------------------------------------

void homologation3(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            spline(color, 0x0370, 0x0156, 0xFC7C, 0x40, 0x40);
            break;
        case 2:
			spline(color, 0x0730, 0x0280, 0x0708, 0xF0, 0xC0);
            break;
		case 3:
			setSonarStatus(1);
			spline(color, 0x0790, 0x076C, 0x0000, 0x22, 0x5A);
            break;
    }
}

// ----------------------------------------------------------- Homologation 4 ---------------------------------------------------------

void homologation4(int color) {
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            spline(color, 0x0370, 0x0156, 0xFC7C, 0x40, 0x40);
            break;
        case 2:
			// first bottle
			spline(color, 0x0720, 0x0280, 0x0708, 0xF0, 0xC0);
            break;
		case 3: // Goto near 2 bottle
			setSonarStatus(0); // TODO
			spline(color, 0x05DC, 0x0800, 0x0384, 0x57, 0x0A);
            break;
		case 4: // hit bottle 2
			setSonarStatus(0);
			spline(color, 0x07AF, 0x076C, 0xF8F8, 0xD8, 0xF8);
            break;
		case 5: // near lintel
			spline(color, 0x0560, 0x0580, 0xFC7C, 0x1E, 0x1E);
            break;
		// Open arm : TODO
		case 6:
			spline(color, 0x0402, 0x0115, 0xFC7C, 0x64, 0x32);
			break;
		// rotation of 170°
		case 7:
			// motionDriverRight(1600);
			spline(color, 0x0315, 0x01A2, 0x04BA, 0xD9, 0xEC);
			break;
			// TODO : Open arm
		case 8: // take the lintel 2
			spline(color, 0x025C, 0x055C, 0x0384, 0x0D, 0x46);
			break;
		case 9:
			left(color, 1800.0f);
			break;
		case 10:
			// go back home
			spline(color, 0x00F5, 0x016F, 0xFC7C, 0x33, 0x27);
			break;
		case 11:
			spline(color, 0x0208, 0x02C2, 0xFC7C, 0xB6, 0x35);
			break;
		case 12:
			// take lintel 3
			spline(color, 0x0282, 0x083C, 0x0384, 0x1E, 0x78);
			break;
		case 13:
			// take the 4 CD
			spline(color, 0x06A8, 0x05D5, 0x0FC7C, 0x3E, 0x53);
			break;
		case 14:
			// go back to sending zone
			spline(color, 0x038F, 0x00CF, 0x0FC7C, 0x3C, 0x1E);
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
			setReadyForNextMotion(TRUE);
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


void homologation(unsigned int homologationIndex, unsigned int color) {
	if (homologation != 0) {
        // Wait after flag
        if (!isReadyForNextMotion()) {
            return;
        }
        // avoid two movement at the same time
        setReadyForNextMotion(FALSE);

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
}

