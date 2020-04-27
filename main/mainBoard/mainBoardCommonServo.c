#include "mainBoardCommonServo.h"

#include "mainBoardCommon.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../drivers/pwm/servo/servoPwmPca9685.h"

void mainBoardCommonAddPca9685Servos(void) {
        // ROBOT2020 : PCA9685 for SERVO
    ServoList* servoList = mainBoardCommonGetServoList();
    // I2cBus* i2cBus = mainBoardCommonGetMainI2cBus();
    I2cBus* i2cBus = getI2cBusByIndex(MAIN_BOARD_SERVO_I2C_BUS_INDEX);
    I2cBusConnection* servoI2cBusConnection = addI2cBusConnection(i2cBus, PCA9685_ADDRESS_0, true);
    addServoAllPca9685(servoList, servoI2cBusConnection);
}

