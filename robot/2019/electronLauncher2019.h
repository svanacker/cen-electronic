#ifndef ELECTRON_LAUNCHER_2019_H
#define ELECTRON_LAUNCHER_2019_H

#include <stdbool.h>

#include "../../common/pwm/servo/servoList.h"
#include "../../drivers/tof/tofList.h"

#include "../../robot/config/robotConfig.h"

// SERVO INDEX

#define ELECTRON_LAUNCHER_2019_ELECTRON_SERVO_INDEX                             0
#define ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_SERVO_INDEX                      1

// SERVO VALUE
#define ELECTRON_LAUNCHER_2019_ELECTRON_RELEASE_SERVO_VALUE                    650
#define ELECTRON_LAUNCHER_2019_ELECTRON_LOCKED_SERVO_VALUE                    1500
#define ELECTRON_LAUNCHER_2019_EXPERIENCE_INIT_VALUE                          1500
#define ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_VALUE                           800

// DISTANCE
#define ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MIN                        450
#define ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MAX                        600
#define ELECTRON_LAUNCHER_2019_ROBOT_MOVED_DISTANCE_MIN                         800

// CHECK / THRESHOLD
#define ELECTRON_LAUNCHER_2019_CHECK_COUNT                                      10
#define ELECTRON_LAUNCHER_2019_THRESHOLD_COUNT                                   9

// RELEASE TRY COUNT 
#define ELECTRON_LAUNCHER_2019_RELEASE_TRY_COUNT                                1

/**
 * The struct defining the electron Launcher.
 */
typedef struct {
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
    /** Is the Robot placed. */
    bool robotPlaced;
    /** Is the robot Moved. */
    bool robotMoved;
    /** How many times the robot Moved was found for the last check */
    unsigned int robotMovedDetectionCount;
} ElectronLauncher2019;

/**
* Initialize the Electron Launcher 2019 and add a timer to check every 100 ms
*/
void initElectronLauncher2019(ElectronLauncher2019* launcher,
                              RobotConfig* robotConfig,
                              ServoList* servoList,
                              TofSensorList* tofSensorList);

// ACTIONS

void electronLauncher2019Launch(ElectronLauncher2019* launcher);

void electronLauncher2019Show(ElectronLauncher2019* launcher);

void electronLauncher2019Init(ElectronLauncher2019* launcher);

// DEBUG


/**
* Debug the launcher
*/
void electronLauncher2019Debug(ElectronLauncher2019* launcher, OutputStream* outputStream);


#endif
