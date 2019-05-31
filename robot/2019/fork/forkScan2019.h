#ifndef FORK_SCAN_2019_H
#define FORK_SCAN_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"

#include "../../../drivers/tof/tof.h"
#include "../../../drivers/tof/tofList.h"

#include "../../../drivers/ioExpander/ioExpanderList.h"

#include "../../../drivers/i2c/multiplexer/multiplexerList.h"

// TOF INDEX
#define FORK_2019_LEFT_TOF_INDEX                                              12
#define FORK_2019_RIGHT_TOF_INDEX                                             11

#define FORK_2019_HARDWARE_IO_EXPANDER_INDEX                                   0

#define FORK_2019_LEFT_HARDWARE_IO_EXPANDER_IO_INDEX                           0
#define FORK_2019_RIGHT_HARDWARE_IO_EXPANDER_IO_INDEX                          1

// TOF THRESHOLD
#define FORK_2019_SCAN_GOLDENIUM_DISTANCE_LEFT_MIN_THRESHOLD                   5
#define FORK_2019_SCAN_GOLDENIUM_DISTANCE_LEFT_MAX_THRESHOLD                  35
#define FORK_2019_SCAN_GOLDENIUM_DISTANCE_RIGHT_MIN_THRESHOLD                  5
#define FORK_2019_SCAN_GOLDENIUM_DISTANCE_RIGHT_MAX_THRESHOLD                 45

#define FORK_2019_SCAN_DISTRIBUTOR_DISTANCE_LEFT_MIN_THRESHOLD                 5
#define FORK_2019_SCAN_DISTRIBUTOR_DISTANCE_LEFT_MAX_THRESHOLD                32
#define FORK_2019_SCAN_DISTRIBUTOR_DISTANCE_RIGHT_MIN_THRESHOLD                5
#define FORK_2019_SCAN_BIG_ROBOT_DISTRIBUTOR_DISTANCE_RIGHT_MAX_THRESHOLD     32
#define FORK_2019_SCAN_SMALL_ROBOT_DISTRIBUTOR_DISTANCE_RIGHT_MAX_THRESHOLD   42

#define FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION                             30
#define FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS                              100
#define FORK_2019_SCAN_MEASURE_COUNT                                           3
#define FORK_2019_SCAN_MATCH_COUNT                                             2

// VERY IMPORTANT to have more than 30 ms between calls, if not, the i2c link
// seems to be quickly blocked
#define FORK_2019_SCAN_TIME_BETWEEN_MEASURE_MILLISECONDS                      50

// Scan Servo Value
#define FORK_2019_SCAN_SPEED_FACTOR                                         0xFF

// BIG ROBOT
#define FORK_2019_BIG_ROBOT_SCAN_MIDDLE_SERVO_VALUE                         1500
#define FORK_2019_BIG_ROBOT_SCAN_LEFT_SERVO_VALUE                           1850
#define FORK_2019_BIG_ROBOT_SCAN_RIGHT_SERVO_VALUE                          1150

// SMALL ROBOT
#define FORK_2019_SMALL_ROBOT_SCAN_MIDDLE_SERVO_VALUE                       1410
#define FORK_2019_SMALL_ROBOT_SCAN_LEFT_SERVO_VALUE                         1860
#define FORK_2019_SMALL_ROBOT_SCAN_RIGHT_SERVO_VALUE                         960


// FORK SCAN
void forkScan2019ConfigTofList(TofSensor* leftForkScanSensor,
                              TofSensor* rightForkScanSensor,
                              MultiplexerList* multiplexerList,
                              IOExpanderList* ioExpanderList);

bool forkScan(ServoList* servoList, TofSensorList* tofSensorList, unsigned int retryCount, unsigned int leftRight);

bool forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList, unsigned int retryCount);

bool forkScanFromRightToLeft(ServoList* servoList, TofSensorList* tofSensorList, unsigned int retryCount);

void forkScan2019ConfigTofListForGoldenium(TofSensorList* tofSensorList);

void forkScan2019ConfigTofListForDistributor(TofSensorList* tofSensorList);

#endif
