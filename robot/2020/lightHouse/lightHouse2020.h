#ifndef LIGHT_HOUSE_2020_H
#define LIGHT_HOUSE_2020_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"
#include "../../../drivers/tof/tofList.h"

#include "../../../robot/config/robotConfig.h"
#include "../../../robot/match/endMatch.h"

// SERVO INDEX

#define LIGHT_HOUSE_2020_SERVO_INDEX                             0

// SERVO VALUE
#define LIGHT_HOUSE_2020_SERVO_LEFT_VALUE                        500
#define LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE                       2500
#define LIGHT_HOUSE_2020_SERVO_SPEED                             10

// DISTANCE
#define LIGHT_HOUSE_2020_ROBOT_NO_TOUCH_DISTANCE_MIN                      10
#define LIGHT_HOUSE_2020_ROBOT_NO_TOUCH_DISTANCE_MAX                      30

#define LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MIN                         50
#define LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MAX                         100

// CHECK / THRESHOLD
#define LIGHT_HOUSE_2020_THRESHOLD_COUNT                                5
#define LIGHT_HOUSE_2020_MISSED_DECREMENT_VALUE                         5

// RELEASE TRY COUNT 
#define LIGHT_HOUSE_2020_RELEASE_TRY_COUNT                              2

// PWM FOR LIGHT
#define LIGHT_HOUSE_2020_LIGHT_ON_VALUE                                 0x60

// PWM FOR MOTOR
#define LIGHT_HOUSE_2020_MOTOR_FORWARD_SPEED                            40
#define LIGHT_HOUSE_2020_MOTOR_BACKWARD_SPEED                          -20

/**
 * Define the state of the LightHouse.
 */
enum LightHouse2020State {
    // Unknown (to avoid that we forget to init it by error)
    LIGHT_HOUSE_STATE_UNKNOWN = 0,
    // The Launcher is initialized
    LIGHT_HOUSE_STATE_INITIALIZED = 1,

    // PLACED
    // Check if the tof Sensor is ok
    LIGHT_HOUSE_STATE_SEARCH_IF_PLACED = 2,
    // The light House tof Sensor was found
    LIGHT_HOUSE_STATE_PLACED = 3,
    // We search if we need to launch
    LIGHT_HOUSE_STATE_SEARCH = 4,
    // The light search is ok
    LIGHT_HOUSE_STATE_SEARCH_OK = 5,
    
    // The launcher must be launch
    LIGHT_HOUSE_STATE_TO_LAUNCH = 6,
    // The launcher was launched
    LIGHT_HOUSE_STATE_LAUNCHED = 7,

    // SHOW REMAINING TIME
    LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME = 8
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
} LightHouse2020;

/**
 * Initialize the Electron Launcher 2019 and add a timer to check every 100 ms
 */
void initLightHouse2020(LightHouse2020* lightHouse,
        EndMatch* endMatch,
        RobotConfig* robotConfig,
        ServoList* servoList,
        TofSensorList* tofSensorList);

/**
 * Main method which must be called in the main processing loop so that
 * we could manage the state and find actions to do.
 */
void handleElectronLauncherActions(LightHouse2020* lightHouse);

/**
 * Handle all Change of state to be able to debug the workflow.
 */
void updateElectronLauncherState(LightHouse2020* lightHouse, enum LightHouse2020State newState);

// ACTIONS

void lightHouse2020Up(LightHouse2020* lightHouse);

void lightHouse2020Bottom(LightHouse2020* lightHouse);

void lightHouse2020Reset(LightHouse2020* lightHouse);

void lightHouse2020On(LightHouse2020* lightHouse);

void lightHouse2020Off(LightHouse2020* lightHouse);

#endif
