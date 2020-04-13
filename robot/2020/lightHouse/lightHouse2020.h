#ifndef LIGHT_HOUSE_2020_H
#define LIGHT_HOUSE_2020_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"
#include "../../../drivers/tof/tofList.h"

#include "../../../robot/config/robotConfig.h"
#include "../../../robot/match/endMatch.h"


/**
 * Define the state of the LightHouse.
 */
enum LightHouse2020State {
    // Unknown (to avoid that we forget to init it by error)
    LIGHT_HOUSE_STATE_UNKNOWN = 0,

    // INIT
    // The Launcher is initialized
    LIGHT_HOUSE_STATE_INITIALIZED = 1,

    // GO TO BOTTOM
    // The robot is going down
    LIGHT_HOUSE_STATE_INIT_GOING_DOWN = 2,
    // The robot is at the bottom
    LIGHT_HOUSE_STATE_INIT_POSITION_BOTTOM = 3,
    
    // PLACED
    // Check if the tof Sensor is ok
    LIGHT_HOUSE_STATE_SEARCH_IF_PLACED = 4,
    // The light House tof Sensor was found
    LIGHT_HOUSE_STATE_PLACED = 5,
    
    // TOUCH
    // We search after a touch
    LIGHT_HOUSE_STATE_SEARCH_TOUCH = 6,
    // The lightHouse was touch
    LIGHT_HOUSE_STATE_TOUCHED = 7,
    
    // LAUNCH
    // The launcher must be launch
    LIGHT_HOUSE_STATE_TO_LAUNCH = 8,
    // The launcher was launched
    LIGHT_HOUSE_STATE_LAUNCHED = 9,

    // SHOW REMAINING TIME
    LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME = 11
};

/**
 * The struct defining the Light House 2020 Robot.
 */
typedef struct {
    /** The state of the Light house 2020 . */
    enum LightHouse2020State state;
    /** If we must do the next action or not in the main Loop. */
    bool doNextAction;
    /** The End Match object. */
    EndMatch* endMatch;
    /** The robot Config. */
    RobotConfig* robotConfig;
    /** The tof Index. */
    unsigned int tofIndex;
    /** The tof sensor to use */
    TofSensor* tofSensor;
    /** Servo List */
    ServoList* servoList;
    /** Tof List */
    TofSensorList* tofSensorList;
    /** How many analysis of Robot Placed was done (to detect if we do the check */
    signed int robotPlacedAnalysisCount;
    /** How many analysis of Robot Placed was done (to detect if we do the check */
    signed int robotNearAnalysisCount;
    /** How many times the robot Moved was found for the last check */
    signed int robotNearDetectionCount;
    /** Internal timer (to avoid to show more than 10x by second) */
    unsigned int timerCount;
    /** Rotation of Servo. */
    bool rotateServo;
} LightHouse2020;

/**
 * Initialize the Electron Launcher 2019 and add a timer to check every 100 ms
 */
void initLightHouse2020(LightHouse2020* lightHouse,
        EndMatch* endMatch,
        RobotConfig* robotConfig,
        ServoList* servoList,
        TofSensorList* tofSensorList);

// OTHER

void lightHouse2020Reset(LightHouse2020* lightHouse);

#endif
