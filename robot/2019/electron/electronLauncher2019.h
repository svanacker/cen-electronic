#ifndef ELECTRON_LAUNCHER_2019_H
#define ELECTRON_LAUNCHER_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"
#include "../../../drivers/tof/tofList.h"

#include "../../../robot/config/robotConfig.h"
#include "../../../robot/match/endMatch.h"

// SERVO INDEX

#define ELECTRON_LAUNCHER_2019_ELECTRON_SERVO_INDEX                             0
#define ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_SERVO_INDEX                      1

// SERVO VALUE
#define ELECTRON_LAUNCHER_2019_ELECTRON_RELEASE_SERVO_VALUE                    650
#define ELECTRON_LAUNCHER_2019_ELECTRON_LOCKED_SERVO_VALUE                    1500
#define ELECTRON_LAUNCHER_2019_EXPERIENCE_INIT_VALUE                          1500
#define ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_VALUE                          2500

// DISTANCE
#define ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MIN                        450
#define ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MAX                        600

#define ELECTRON_LAUNCHER_2019_ROBOT_MOVED_DISTANCE_MIN                         650
#define ELECTRON_LAUNCHER_2019_ROBOT_MOVED_DISTANCE_MAX                        10000

// CHECK / THRESHOLD
// #define ELECTRON_LAUNCHER_2019_CHECK_COUNT                                      3
#define ELECTRON_LAUNCHER_2019_THRESHOLD_COUNT                                  2

// RELEASE TRY COUNT 
#define ELECTRON_LAUNCHER_2019_RELEASE_TRY_COUNT                                2

/**
 * Define the state of the Electron Launcher.
 */
enum ElectronLauncher2019State {
    // Unknown (to avoid that we forget to init it by error)
    LAUNCHER_STATE_UNKNOWN = 0,
    // The Launcher is initialized
    LAUNCHER_STATE_INITIALIZED = 1,

    // PLACED
    // We search if the robot is placed
    LAUNCHER_STATE_SEARCH_ROBOT_PLACED = 2,
    // The robot is placed
    LAUNCHER_STATE_ROBOT_PLACED = 3,

    // MOVED
    // We search 
    // We search if the robot is moved
    LAUNCHER_STATE_SEARCH_ROBOT_MOVED = 4,
    // The robot is moved
    LAUNCHER_STATE_ROBOT_MOVED = 5,

    // LAUNCH
    // We must launch the launcher
    LAUNCHER_STATE_TO_LAUNCH = 6,
    // The launcher was launched
    LAUNCHER_STATE_LAUNCHED = 7,
    
    // SHOW REMAINING TIME
    LAUNCHER_STATE_SHOW_REMAINING_TIME = 8
};


/**
 * The struct defining the electron Launcher.
 */
typedef struct {
    /** The state of the electron Launcher 2019 . */
    enum ElectronLauncher2019State state;
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
    unsigned int robotPlacedAnalysisCount;
    /** How many analysis of Robot Placed was done (to detect if we do the check */
    unsigned int robotMovedAnalysisCount;
    /** How many times the robot Moved was found for the last check */
    unsigned int robotMovedDetectionCount;
} ElectronLauncher2019;

/**
* Initialize the Electron Launcher 2019 and add a timer to check every 100 ms
*/
void initElectronLauncher2019(ElectronLauncher2019* launcher,
                              EndMatch* endMatch,
                              RobotConfig* robotConfig,
                              ServoList* servoList,
                              TofSensorList* tofSensorList);

/**
* Main method which must be called in the main processing loop so that
* we could manage the state and find actions to do.
*/
void handleElectronLauncherActions(ElectronLauncher2019* launcher);

/**
* Handle all Change of state to be able to debug the workflow.
*/
void updateElectronLauncherState(ElectronLauncher2019* launcher, enum ElectronLauncher2019State newState);

// ACTIONS

void electronLauncher2019Launch(ElectronLauncher2019* launcher);

void electronLauncher2019Show(ElectronLauncher2019* launcher);

void electronLauncher2019Reset(ElectronLauncher2019* launcher);

// SIMULATION

void electronLauncher2019SimulateRobotPlaced(ElectronLauncher2019* launcher);

void electronLauncher2019SimulateRobotPlacedAndMoved(ElectronLauncher2019* launcher);

#endif
