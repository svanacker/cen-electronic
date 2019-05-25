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
#define FORK_2019_SCAN_DISTANCE_LEFT_MIN_THRESHOLD                             5
#define FORK_2019_SCAN_DISTANCE_LEFT_MAX_THRESHOLD                            35
#define FORK_2019_SCAN_DISTANCE_RIGHT_MIN_THRESHOLD                             5
#define FORK_2019_SCAN_DISTANCE_RIGHT_MAX_THRESHOLD                            35
#define FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION                             30
#define FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS                               50
#define FORK_2019_SCAN_MEASURE_COUNT                                           3
#define FORK_2019_SCAN_MATCH_COUNT                                             2

// VERY IMPORTANT to have more than 30 ms between calls, if not, the i2c link
// seems to be quickly blocked
#define FORK_2019_SCAN_TIME_BETWEEN_MEASURE_MILLISECONDS                      30

// Scan Servo Value
#define FORK_2019_SCAN_SPEED_FACTOR                                         0xFF
// TODO : To change
#define FORK_2019_SCAN_MIDDLE_SERVO_VALUE                                   1400
#define FORK_2019_SCAN_LEFT_SERVO_VALUE                                     1800
#define FORK_2019_SCAN_RIGHT_SERVO_VALUE                                    1100


// FORK SCAN
void forkScan2019ConfigTofList(TofSensor* leftForkScanSensor,
                              TofSensor* rightForkScanSensor,
                              MultiplexerList* multiplexerList,
                              IOExpanderList* ioExpanderList);

bool forkScan(ServoList* servoList, TofSensorList* tofSensorList, unsigned int leftRight);

bool forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList);

bool forkScanFromRightToLeft(ServoList* servoList, TofSensorList* tofSensorList);

#endif
