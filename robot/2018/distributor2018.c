#include "distributor2018.h"

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

#include "../../robot/match/teamColor.h"


enum ColorType colorSensorFindColorType2018(ColorSensor* colorSensor) {
    Color* color = colorSensor->colorSensorReadValue(colorSensor);
    
    if (isColorInRange(color, 
        DISTRIBUTOR_2018_GREEN_R_LOW_THRESHOLD, 
        DISTRIBUTOR_2018_GREEN_R_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_G_LOW_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_G_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_B_LOW_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_B_HIGH_THRESHOLD)
        && (color->G > color->R)    
            ) {
        return COLOR_TYPE_GREEN;
        }
    else if (isColorInRange(color,
        DISTRIBUTOR_2018_ORANGE_R_LOW_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_R_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_G_LOW_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_G_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_B_LOW_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_B_HIGH_THRESHOLD)
        && (color->R > 2 * color->G)    
            ) {
        return COLOR_TYPE_ORANGE;
    }
    return COLOR_TYPE_UNKNOWN;
}

void initDistributor(Distributor* distributor, enum TeamColor teamColor, ColorSensor* colorSensor) {
    distributor->teamColor = teamColor;
    distributor->colorSensor = colorSensor;
}

void cleanDistributor(Distributor* distributor) {
    distributor->launcherContent = SQUARE_CONTENT_EMPTY;
    unsigned int i;
    for (i = 0; i < 8; i++) {
        distributor->squares[i] = SQUARE_CONTENT_EMPTY;
    }
}

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
}

void updateDistributorStateWhenTurnRight(Distributor* distributor) {
    // If we have something just in the square before the hole for the launcher
    if (distributor->squares[6] != SQUARE_CONTENT_EMPTY) {
        // The launcher will take the content of the square
        distributor->launcherContent = distributor->squares[6];
    }
    // In all cases, squares becomes empty when turning to the right
    distributor->squares[5] = SQUARE_CONTENT_EMPTY;
    distributor->squares[6] = distributor->squares[7];
    distributor->squares[7] = distributor->squares[0];
    distributor->squares[0] = distributor->squares[1];
    distributor->squares[1] = distributor->squares[2];
    distributor->squares[2] = distributor->squares[3];
    distributor->squares[3] = distributor->squares[4];
    distributor->squares[4] = distributor->squares[5];
}

void loadUnicolorDistributor(Distributor* distributor) {
    unsigned int i;
    
    // Clean to avoid problem when we do lots of trial
    cleanDistributor(distributor);
    
    unsigned int ballHandledCount = 0;
    ColorSensor* colorSensor = distributor->colorSensor;
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    if (distributor->teamColor == TEAM_COLOR_GREEN) {
        // Load -> color device
        for (i = 0; i < 20; i++) {
            println(debugOutputStream);
            println(debugOutputStream);
            appendString(debugOutputStream, "iteration : ");
            appendDec(debugOutputStream, i);
            println(debugOutputStream);
            // In all cases, prepare the launcher even if it's empty, because it does not take time unless if it is needed
            clientLaunch2018(LAUNCHER_RIGHT_INDEX, true);
            
            // Rotate the distributor 
            clientDistributor2018CleanNext(LAUNCHER_LEFT_INDEX);
            
            // Update the internal representation of the distributor
            updateDistributorStateWhenTurnRight(distributor);
            
            // Determine the color
            if (colorSensor->colorSensorFindColorType(colorSensor) == COLOR_TYPE_GREEN) {
                distributor->squares[0] = SQUARE_CONTENT_OK;
            }
            printColorSensorTable(debugOutputStream, colorSensor);

            printDistributor2018(debugOutputStream, distributor);
            
            if (distributor->launcherContent == SQUARE_CONTENT_OK) {
                clientLaunch2018(LAUNCHER_RIGHT_INDEX, false);
                distributor->launcherContent = SQUARE_CONTENT_EMPTY;
                ballHandledCount++;
            }
            // delaymSec(300);
            if (ballHandledCount >= 8) {
                break;
            }
        }
    }
}

void loadMixedDistributor(Distributor* distributor) {
   
}
