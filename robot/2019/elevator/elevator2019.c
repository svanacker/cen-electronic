#include "elevator2019.h"

#include <stdbool.h>

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/error/error.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/pwm/servo/servoList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/tof/tofList.h"

#include "../../../robot/2019/fork/fork2019.h"

unsigned int getElevatorBottomServoValue(void) {
    if (getRobotType() == ROBOT_TYPE_BIG) {
        return FORK_2019_BIG_ROBOT_ELEVATOR_BOTTOM_SERVO_VALUE;
    }
    else if (getRobotType() == ROBOT_TYPE_SMALL) {
        return FORK_2019_SMALL_ROBOT_ELEVATOR_BOTTOM_SERVO_VALUE;        
    }
    return 1500;
}

unsigned int getElevatorUpServoValue(void) {
    if (getRobotType() == ROBOT_TYPE_BIG) {
        return FORK_2019_BIG_ROBOT_ELEVATOR_UP_SERVO_VALUE;
    }
    else if (getRobotType() == ROBOT_TYPE_SMALL) {
        return FORK_2019_SMALL_ROBOT_ELEVATOR_UP_SERVO_VALUE;        
    }
    return 1500;
}

unsigned int getElevatorSecondDropServoValue(void) {
    if (getRobotType() == ROBOT_TYPE_BIG) {
        return FORK_2019_BIG_ROBOT_ELEVATOR_SECOND_DROP_SERVO_VALUE;
    }
    else if (getRobotType() == ROBOT_TYPE_SMALL) {
        return FORK_2019_SMALL_ROBOT_ELEVATOR_SECOND_DROP_SERVO_VALUE;        
    }
    return 1500;
}


unsigned int getElevatorGoldeniumServoValue(void) {
    if (getRobotType() == ROBOT_TYPE_BIG) {
        return FORK_2019_BIG_ROBOT_ELEVATOR_GOLDENIUM_SERVO_VALUE;
    }
    else if (getRobotType() == ROBOT_TYPE_SMALL) {
        return FORK_2019_SMALL_ROBOT_ELEVATOR_GOLDENIUM_SERVO_VALUE;        
    }
    return 1500;
}

unsigned int getElevatorGoldeniumScanServoValue(void) {
    if (getRobotType() == ROBOT_TYPE_BIG) {
        return FORK_2019_BIG_ROBOT_ELEVATOR_GOLDENIUM_SCAN_SERVO_VALUE;
    }
    else if (getRobotType() == ROBOT_TYPE_SMALL) {
        return FORK_2019_SMALL_ROBOT_ELEVATOR_GOLDENIUM_SCAN_SERVO_VALUE;        
    }
    return 1500;
}

void moveElevatorAtValue(ServoList* servoList, unsigned int value, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, value, true);
}

void moveElevatorBottom(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, getElevatorBottomServoValue(), wait);
}
void moveElevatorInitPosition(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_INIT_POSITION_SERVO_VALUE, wait);
}

void moveElevatorUp(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, getElevatorUpServoValue(), wait);
}

void moveElevatorAcceleratorSecondDrop(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, getElevatorSecondDropServoValue(), wait);
}

void moveElevatorToTakeGoldenium(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, getElevatorGoldeniumServoValue(), wait);
}

void moveElevatorToScanGoldenium(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, getElevatorGoldeniumScanServoValue(), wait);
}
