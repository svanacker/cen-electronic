#include "distributor2018.h"
#include "distributorDebug2018.h"

#include "../../common/color/color.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../client/robot/2018/launcherClient2018.h"
#include "../../robot/2018/score2018.h"
#include "../../robot/2018/launcherDeviceInterface2018.h"

#include "../../drivers/colorSensor/colorSensor.h"
#include "../../drivers/colorSensor/colorSensorDebug.h"

#include "../../robot/strategy/teamColor.h"


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

void cleanDistributor(Distributor* distributor) {
    distributor->launcherContent = SQUARE_CONTENT_EMPTY;
    unsigned int i;
    for (i = 0; i < 8; i++) {
        distributor->squares[i] = SQUARE_CONTENT_EMPTY;
    }
}

void initDistributor(Distributor* distributor, enum TeamColor teamColor, ColorSensor* colorSensor) {
    distributor->teamColor = teamColor;
    distributor->colorSensor = colorSensor;
    distributor->score = 0;
    distributor->loadedBallCount = 0;
    distributor->sentBallCount = 0;
    cleanDistributor(distributor);
}


/** Distributor Index (from Behind Robot and not in Front of) */
//                                             [0]
//                                           [1] [7]
//  => Blocked by Item to avoid ejection <= [2]   [6]
//                                           [3] [5] => RIGHT EJECTOR
//                                             [4]
void updateDistributorStateClockWise(Distributor* distributor) {
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

/** Distributor Index (from Behind Robot and not in Front of) */
//                     [0]
//                   [1] [7]
//                  [2]   [6] => Blocked by Item to avoid ejection
// LEFT EJECTOR <=   [3] [5]
//                     [4]]

void updateDistributorStateAntiClockWise(Distributor* distributor) {
    // If we have something just in the square before the hole for the launcher
    if (distributor->squares[2] != SQUARE_CONTENT_EMPTY) {
        // The launcher will take the content of the square
        distributor->launcherContent = distributor->squares[2];
    }
    // In all cases, squares becomes empty when turning to the left
    distributor->squares[3] = SQUARE_CONTENT_EMPTY;
    distributor->squares[2] = distributor->squares[1];
    distributor->squares[1] = distributor->squares[0];
    distributor->squares[0] = distributor->squares[7];
    distributor->squares[7] = distributor->squares[6];
    distributor->squares[6] = distributor->squares[5];
    distributor->squares[5] = distributor->squares[4];
    distributor->squares[4] = distributor->squares[3];
}

void loadUnicolorDistributorSimple(enum TeamColor teamColor) {
    appendString(getDebugOutputStreamLogger(), "loadUnicolorDistributorSimple");
    unsigned int i;
    unsigned direction = 0;
    if (teamColor == TEAM_COLOR_GREEN) {
        direction = LAUNCHER_RIGHT_INDEX;
    }
    else {
        direction = LAUNCHER_LEFT_INDEX; 
    }        
    for (i = 0; i < 8; i++) {
        // In all cases, prepare the launcher even if it's empty, because it does not take time unless if it is needed
        clientLaunch2018(direction, LAUNCHER_PREPARE_ON);

        // Rotate the distributor 
        clientDistributor2018CleanNext(direction);

        // Send the ball
        clientLaunch2018(direction, LAUNCHER_LAUNCH);
    }
}

void loadUnicolorDistributorWithColorCheck(Distributor* distributor) {
    unsigned int i;
    
    // Clean to avoid problem when we do lots of trial
    cleanDistributor(distributor);
    
    ColorSensor* colorSensor = distributor->colorSensor;
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    if (distributor->teamColor == TEAM_COLOR_GREEN) {
        // Load -> color device
        for (i = 0; i < 8; i++) {
            println(debugOutputStream);
            println(debugOutputStream);
            appendString(debugOutputStream, "iteration : ");
            appendDec(debugOutputStream, i);
            println(debugOutputStream);
            // In all cases, prepare the launcher even if it's empty, because it does not take time unless if it is needed
            clientLaunch2018(LAUNCHER_RIGHT_INDEX, LAUNCHER_PREPARE_ON);
            
            // Rotate the distributor 
            clientDistributor2018CleanNext(LAUNCHER_LEFT_INDEX);
            
            // Update the internal representation of the distributor
            updateDistributorStateClockWise(distributor);
            
            // Determine the color
            if (colorSensor->colorSensorFindColorType(colorSensor) == COLOR_TYPE_GREEN) {
                distributor->squares[0] = SQUARE_CONTENT_OK;
            }
            printColorSensorTable(debugOutputStream, colorSensor);

            printDistributor2018(debugOutputStream, distributor);
            
            if (distributor->launcherContent == SQUARE_CONTENT_OK) {
                sendBallAndCountScore(distributor, LAUNCHER_RIGHT_INDEX);
            }
            // delaymSec(300);
            if (distributor->sentBallCount >= SCORE_POINT_2018_DISTRIBUTOR_UNICOLOR_BALL_COUNT) {
                break;
            }
        }
    }
}

void loadMixedDistributor(enum TeamColor teamColor) {
    appendString(getDebugOutputStreamLogger(), "loadMixedDistributor");
    unsigned int i;
    // Load -> color device
    for (i = 0; i < 4; i++) {

        if (teamColor == TEAM_COLOR_GREEN) {
            // Rotate the distributor 
            clientDistributor2018CleanNext(LAUNCHER_LEFT_INDEX);
        }
        else if (teamColor == TEAM_COLOR_ORANGE) {
            // Rotate the distributor 
            clientDistributor2018CleanNext(LAUNCHER_RIGHT_INDEX);
        }
    }
}

void ejectMixedDistributor(enum TeamColor teamColor) {
    appendString(getDebugOutputStreamLogger(), "ejectMixedDistributor");
    unsigned int i;

    if (teamColor == TEAM_COLOR_GREEN) {
        for (i = 0; i < 8; i++) {
            clientDistributor2018EjectDirty();
            // Rotate the distributor in other direction
            clientDistributor2018CleanNext(LAUNCHER_LEFT_INDEX);
        }
    }
    else if (teamColor == TEAM_COLOR_ORANGE) {
        for (i = 0; i < 8; i++) {
            clientDistributor2018EjectDirty();
            // Rotate the distributor in other direction
            clientDistributor2018CleanNext(LAUNCHER_RIGHT_INDEX);
        }
    }
}


void sendBallAndCountScore(Distributor* distributor, unsigned int launcherIndex) {
    clientLaunch2018(LAUNCHER_RIGHT_INDEX, LAUNCHER_LAUNCH);
    distributor->launcherContent = SQUARE_CONTENT_EMPTY;
    distributor->loadedBallCount++;
    distributor->score += SCORE_POINT_2018_CLEAN_BALL_POINT;
}
