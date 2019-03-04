#ifndef DISTRIBUTOR_2019_H
#define DISTRIBUTOR_2019_H

#include "../../common/color/color.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/colorSensor/colorSensor.h"

#include "distributor2019.h"

#include "../../robot/strategy/teamColor.h"

/**
 * Determine the type of content in the distributor
 */
enum PuckPlaceHolder {
    /** The puck place holder is empty */
    PUCK_PLACE_HOLDER_EMPTY,
    /** The puck place holder is filled but color unknown */
    PUCK_PLACE_HOLDER_COLOR_UNKNOWN,
    /** The puck place holder is filled with Redium */
    PUCK_PLACE_HOLDER_REDIUM,
    /** The puck place holder is filled with Greenium */
    PUCK_PLACE_HOLDER_GREENIUM,
    /** The puck place holder is filled with Blueium */
    PUCK_PLACE_HOLDER_BLUEIUM,
};

struct BigDistributor;
typedef struct BigDistributor BigDistributor;

#define BIG_DISTRIBUTOR_ITEM_COUNT    6

/**
 * Store the big distributor "Shadow object".
 */
struct BigDistributor {
    /** The color that we must handle */
    enum TeamColor teamColor;
    /** The content of the BigDistributor  */
    enum PuckPlaceHolder(placeHolders)[BIG_DISTRIBUTOR_ITEM_COUNT];
};

// COLOR DETECTION

/** Threshold for GREENIUM DETECTION */
#define PUCK_2019_GREENIUM_R_LOW_THRESHOLD          0
#define PUCK_2019_GREENIUM_R_HIGH_THRESHOLD        15
#define PUCK_2019_GREENIUM_G_LOW_THRESHOLD          5
#define PUCK_2019_GREENIUM_G_HIGH_THRESHOLD       255
#define PUCK_2019_GREENIUM_B_LOW_THRESHOLD          0
#define PUCK_2019_GREENIUM_B_HIGH_THRESHOLD        12

/** Threshold for BLUEIUM DETECTION */
#define PUCK_2019_BLUEIUM_R_LOW_THRESHOLD         5
#define PUCK_2019_BLUEIUM_R_HIGH_THRESHOLD        15
#define PUCK_2019_BLUEIUM_G_LOW_THRESHOLD         20
#define PUCK_2019_BLUEIUM_G_HIGH_THRESHOLD        255
#define PUCK_2019_BLUEIUM_B_LOW_THRESHOLD          0
#define PUCK_2019_BLUEIUM_B_HIGH_THRESHOLD        12

/** Threshold for REDIUM DETECTION */
#define PUCK_2019_REDIUM_R_LOW_THRESHOLD         5
#define PUCK_2019_REDIUM_R_HIGH_THRESHOLD        255
#define PUCK_2019_REDIUM_G_LOW_THRESHOLD         0
#define PUCK_2019_REDIUM_G_HIGH_THRESHOLD        20
#define PUCK_2019_REDIUM_B_LOW_THRESHOLD          0
#define PUCK_2019_REDIUM_B_HIGH_THRESHOLD        12

/**
 * Init the distributor.
 */
void initDistributor2019(BigDistributor* bigDistributor, enum TeamColor teamColor);

#endif
