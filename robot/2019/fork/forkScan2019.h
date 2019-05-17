#ifndef FORK_SCAN_2019_H
#define FORK_SCAN_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"

#include "../../../drivers/tof/tofList.h"

// TOF INDEX
#define FORK_2019_LEFT_TOF_INDEX                                               6
#define FORK_2019_RIGHT_TOF_INDEX                                              7

// TOF THRESHOLD
#define FORK_2019_SCAN_DISTANCE_LEFT_THRESHOLD                                35
#define FORK_2019_SCAN_DISTANCE_RIGHT_THRESHOLD                               35
#define FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION                             30
#define FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS                               20
#define FORK_2019_SCAN_MEASURE_COUNT                                           3
#define FORK_2019_SCAN_MATCH_COUNT                                             2

#define FORK_2019_SCAN_TIME_BETWEEN_MEASURE_MILLISECONDS                      10

// Scan Servo Value
#define FORK_2019_SCAN_SPEED_FACTOR                                         0xFF
// TODO : To change
#define FORK_2019_SCAN_MIDDLE_SERVO_VALUE                                   1400
#define FORK_2019_SCAN_LEFT_SERVO_VALUE                                     1800
#define FORK_2019_SCAN_RIGHT_SERVO_VALUE                                    1100


// FORK SCAN

void setForkTofListNameAndThreshold(TofSensorList* tofSensorList);

bool forkScan(ServoList* servoList, TofSensorList* tofSensorList, unsigned int leftRight);

bool forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList);

bool forkScanFromRightToLeft(ServoList* servoList, TofSensorList* tofSensorList);

#endif
