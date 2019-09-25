#include "homologation2011.h"

#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../drivers/motion/motionDriver.h"

#include "../../robot/2011/pliersDeviceInterface2011.h"

void homologationRed() {
    // OutputStream* outputStream;

    unsigned int index = getMotionInstructionIndex();
    switch (index) {
        case 1:
            motionDriverLeftOneWheel(225.0f);
            break;
        case 2:
            // Opens pliers
            // outputStream = getDriverRequestOutputStream();
            // append(outputStream, COMMAND_PLIERS_2011_OPEN);
            // transmitFromDriverRequestBuffer();
            motionDriverForward(1.0f);
            break;
        case 3:
            motionDriverForward(1670.0f);
            break;
        case 4:
            motionDriverBackward(175.0f);
            break;
        case 5:
            motionDriverRight(900.0f);
            break;
        case 6:
            motionDriverForward(690.0f);
            break;
        case 7:
            motionDriverRight(450.0f);
            break;
        case 8:
            motionDriverForward(345.0f);
            break;
        case 9:
            motionDriverBackward(210.0f);
            break;
        case 10:
            motionDriverRight(772.0f);
            break;
        case 11:
            motionDriverForward(507.0f);
            break;
        case 12:
            motionDriverRight(129.0f);
            break;
        case 13:
            motionDriverForward(247.0f);
            break;
    }
}

void homologationBlue() {
    //     OutputStream* outputStream;
    unsigned int index = getMotionInstructionIndex();

    switch (index) {
        case 1:
            motionDriverRightOneWheel(225.0f);
            break;
        case 2:
            // Opens pliers
            //            outputStream = getDriverRequestOutputStream();
            //            append(outputStream, COMMAND_PLIERS_2011_OPEN);
            //            transmitFromDriverRequestBuffer();
            motionDriverForward(1.0f);
            break;
        case 3:
            motionDriverForward(1670.0f);
            break;
        case 4:
            motionDriverBackward(175.0f);
            break;
        case 5:
            motionDriverLeft(900.0f);
            break;
        case 6:
            motionDriverForward(690.0f);
            break;
        case 7:
            motionDriverLeft(450.0f);
            break;
        case 8:
            motionDriverForward(345.0f);
            break;
        case 9:
            motionDriverBackward(210.0f);
            break;
        case 10:
            motionDriverLeft(772.0f);
            break;
        case 11:
            motionDriverForward(507.0f);
            break;
        case 12:
            motionDriverLeft(129.0f);
            break;
        case 13:
            motionDriverForward(247.0f);
            break;
    }
}

void homologation(unsigned int homologationIndex, unsigned int color) {
    if (homologationIndex == 1) {
        // Wait after flag
        if (!isReadyForNextMotion()) {
            return;
        }
        // avoid two movement at the same time
        setReadyForNextMotion(false);

        // for next instruction
        incMotionInstructionIndex();

        // Blue = Bit set
        if (color) {
            homologationBlue();
        } else {
            homologationRed();
        }
    }
}

