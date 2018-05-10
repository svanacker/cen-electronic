#ifndef DISTRIBUTOR_2018_H
#define DISTRIBUTOR_2018_H

#include "../../common/color/color.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/colorSensor/colorSensor.h"

#include "distributor2018.h"

#include "../../robot/strategy/teamColor.h"
#include "../../robot/strategy/teamColor.h"
/**
 * Determine the type of content in the distributor
 */
enum DistributorSquareContent {
    /** The square is empty */
    SQUARE_CONTENT_EMPTY,
    /** The square is filled but color unknown */
    SQUARE_CONTENT_COLOR_UNKNOWN,
    /** The square contains a Ball OK */
    SQUARE_CONTENT_OK,
    /** The square contains a Dirty Ball */
    SQUARE_CONTENT_DIRTY,
};

struct Distributor;
typedef struct Distributor Distributor;

#define DISTRIBUTOR_ITEM_COUNT 8

/**
 * Store the distributor "Shadow object".
 */
struct Distributor {
    /** The color that we must handle */
    enum TeamColor teamColor;
    /** The sensor for color */
    ColorSensor* colorSensor;
    /** The square array */
    enum DistributorSquareContent (squares)[DISTRIBUTOR_ITEM_COUNT];
    /** The index of the square */
    unsigned int squareIndex;
    /** The launcher square Content*/
    enum DistributorSquareContent launcherContent;
    /** How many ball was loaded in the distributor */
    unsigned int loadedBallCount;
    /** How many balls are sent */
    unsigned int sentBallCount;
    /** How many points we have done via the launcher .*/
    unsigned int score;
};

// COLOR DETECTION

/** Threshold for GREEN DETECTION */
#define DISTRIBUTOR_2018_GREEN_R_LOW_THRESHOLD          0
#define DISTRIBUTOR_2018_GREEN_R_HIGH_THRESHOLD        15
#define DISTRIBUTOR_2018_GREEN_G_LOW_THRESHOLD         5
#define DISTRIBUTOR_2018_GREEN_G_HIGH_THRESHOLD       255
#define DISTRIBUTOR_2018_GREEN_B_LOW_THRESHOLD          0
#define DISTRIBUTOR_2018_GREEN_B_HIGH_THRESHOLD        12

/** Threshold for ORANGE DETECTION */
#define DISTRIBUTOR_2018_ORANGE_R_LOW_THRESHOLD         5
#define DISTRIBUTOR_2018_ORANGE_R_HIGH_THRESHOLD        255
#define DISTRIBUTOR_2018_ORANGE_G_LOW_THRESHOLD         0
#define DISTRIBUTOR_2018_ORANGE_G_HIGH_THRESHOLD        20
#define DISTRIBUTOR_2018_ORANGE_B_LOW_THRESHOLD          0
#define DISTRIBUTOR_2018_ORANGE_B_HIGH_THRESHOLD        12

/**
 * Init the distributor.
 */
void initDistributor(Distributor* distributor, enum TeamColor teamColor, ColorSensor* colorSensor);

/**
 * Update the state of the distributor when we do a rotation clock wise (Point of view = Behind Robot)
 * @param distributor
 */
void updateDistributorStateClockWise(Distributor* distributor);

/**
 * Update the state of the distributor when we do a rotation anticlock wise (Point of view = Behind Robot)
 * @param distributor
 */
void updateDistributorStateAntiClockWise(Distributor* distributor);

/**
 * Implementation of a color detection for 2018
 */
enum ColorType colorSensorFindColorType2018(ColorSensor* colorSensor);

// UNICOLOR

/**
 * Load and send all balls of an unicolor distributor with a system of color check
 * @param distributor
 */
void loadUnicolorDistributorWithColorCheck(Distributor* distributor);

/**
 * Load the ball of the distributor but very easily, next to the launcher
 */
void loadUnicolorDistributorSimple(enum TeamColor teamColor);

/**
 * Load all balls of the distributor, but do not send them.
 * @param distributor
 */
void loadMixedColorPhase1Distributor(Distributor* distributor);

/**
 * Interceptor to compute the score and update Distributor State
 */
void sendBallAndCountScore(Distributor* distributor, unsigned int launcherIndex);

#endif
