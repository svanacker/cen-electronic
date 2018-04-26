#ifndef DISTRIBUTOR_2018_H
#define DISTRIBUTOR_2018_H

#include "../../common/color/color.h"
#include "../../drivers/colorSensor/colorSensor.h"

/**
 * Determine the type of content in the distributor
 */
enum DistributorSquareContent {
    /** The square is empty */
    SQUARE_CONTENT_EMPTY,
    /** The square contains a Clean Ball */
    SQUARE_CONTENT_CLEAN,
    /** The square contains a Dirty Ball */
    SQUARE_CONTENT_DIRTY,
};

struct Distributor;
typedef struct Distributor Distributor;

struct Distributor {
    enum DistributorSquareContent (*squares)[];
    unsigned int squareIndex;
};

// COLOR DETECTION

/** Threshold for GREEN DETECTION */
#define DISTRIBUTOR_2018_GREEN_R_LOW_THRESHOLD          0
#define DISTRIBUTOR_2018_GREEN_R_HIGH_THRESHOLD        15
#define DISTRIBUTOR_2018_GREEN_G_LOW_THRESHOLD         15
#define DISTRIBUTOR_2018_GREEN_G_HIGH_THRESHOLD       255
#define DISTRIBUTOR_2018_GREEN_B_LOW_THRESHOLD          0
#define DISTRIBUTOR_2018_GREEN_B_HIGH_THRESHOLD        12

/** Threshold for ORANGE DETECTION */
#define DISTRIBUTOR_2018_ORANGE_R_LOW_THRESHOLD         15
#define DISTRIBUTOR_2018_ORANGE_R_HIGH_THRESHOLD        255
#define DISTRIBUTOR_2018_ORANGE_G_LOW_THRESHOLD         0
#define DISTRIBUTOR_2018_ORANGE_G_HIGH_THRESHOLD        20
#define DISTRIBUTOR_2018_ORANGE_B_LOW_THRESHOLD          0
#define DISTRIBUTOR_2018_ORANGE_B_HIGH_THRESHOLD        12

/**
 * Implementation of a color detection for 2018
 */
enum ColorType colorSensorFindColorType2018(ColorSensor* colorSensor);


#endif
