#include "distributorDebug2018.h"

#include "../../common/color/color.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../client/robot/2018/launcherClient2018.h"
#include "../../robot/2018/launcherDeviceInterface2018.h"

#include "../../drivers/colorSensor/colorSensor.h"
#include "../../drivers/colorSensor/colorSensorDebug.h"

#include "../../robot/strategy/teamColor.h"

void printDistributorSquareContent(OutputStream* outputStream, enum DistributorSquareContent squareContent) {
    if (squareContent == SQUARE_CONTENT_EMPTY) {
        append(outputStream, 'O');        
    }
    else if (squareContent == SQUARE_CONTENT_COLOR_UNKNOWN) {
        append(outputStream, '?');
    }
    else if (squareContent == SQUARE_CONTENT_DIRTY) {
        append(outputStream, 'H');
    }
    else if (squareContent == SQUARE_CONTENT_OK) {
        append(outputStream, 'X');
    }
}

/**
 * Print the content of the distributor
 * @param outputStream
 * @param distributor
 */
void printDistributor2018(OutputStream* outputStream, Distributor* distributor) {
    // First line
    println(outputStream);
    appendString(outputStream, "  ");
    printDistributorSquareContent(outputStream, distributor->squares[0]);
    println(outputStream);

    // Second line
    appendString(outputStream, " ");
    printDistributorSquareContent(outputStream, distributor->squares[7]);
    appendString(outputStream, " ");
    printDistributorSquareContent(outputStream, distributor->squares[1]);
    println(outputStream);

    // Third line
    printDistributorSquareContent(outputStream, distributor->squares[6]);
    appendString(outputStream, "   ");
    printDistributorSquareContent(outputStream, distributor->squares[2]);
    println(outputStream);

    // Line 4
    appendString(outputStream, " ");
    printDistributorSquareContent(outputStream, distributor->squares[5]);
    appendString(outputStream, " ");
    printDistributorSquareContent(outputStream, distributor->squares[3]);
    println(outputStream);

    // Last line
    appendString(outputStream, "  ");
    printDistributorSquareContent(outputStream, distributor->squares[4]);
    println(outputStream);
    
    // Launcher square content
    appendString(outputStream, "Launcher:");
    printDistributorSquareContent(outputStream, distributor->launcherContent);
    println(outputStream);

    // Print the score
}

void printDistributor2018Score(OutputStream* outputStream, Distributor* distributor) {
    appendString(outputStream, "Score (Dec):");
    append(outputStream, distributor->score);
    println(outputStream);
}
