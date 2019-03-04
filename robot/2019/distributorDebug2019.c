#include "distributorDebug2019.h"

#include "../../common/color/color.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../drivers/colorSensor/colorSensor.h"
#include "../../drivers/colorSensor/colorSensorDebug.h"

#include "../../robot/strategy/teamColor.h"

void printDistributor2019SquareContent(OutputStream* outputStream, enum PuckPlaceHolder puckPlaceHolder) {
    if (puckPlaceHolder == PUCK_PLACE_HOLDER_EMPTY) {
        append(outputStream, 'O');        
    }
    else if (puckPlaceHolder == PUCK_PLACE_HOLDER_COLOR_UNKNOWN) {
        append(outputStream, '?');
    }
    else if (puckPlaceHolder == PUCK_PLACE_HOLDER_REDIUM) {
        append(outputStream, 'R');
    }
    else if (puckPlaceHolder == PUCK_PLACE_HOLDER_BLUEIUM) {
        append(outputStream, 'B');
    }
    else if (puckPlaceHolder == PUCK_PLACE_HOLDER_GREENIUM) {
        append(outputStream, 'G');
    }
}

/**
 * Print the content of the distributor
 * @param outputStream
 * @param distributor
 */
void printBigDistributor2019(OutputStream* outputStream, BigDistributor* distributor) {
    // TODO
}

void printDistributor2019Score(OutputStream* outputStream, BigDistributor* distributor) {
    // TODO
}
