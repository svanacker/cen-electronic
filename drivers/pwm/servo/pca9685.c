#include "pca9685.h"
#include "pca9685Debug.h"
#include "i2cMaster.h"
#include "cenMath.h"
#include "cenDelay.h"

#include "../../common/log/logger.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include <math.h>


// SOURCE CODE INSPIRED FROM 
// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/Adafruit_PWMServoDriver.cpp
// https://forum.mikroe.com/viewtopic.php?f=88&t=69437



void pca9685_init(I2cBusConnection* i2cBusConnection) {
    pca9685_reset(i2cBusConnection);
    
    OutputStream* debugOutputStream = getInfoOutputStreamLogger();

    // set a default frequency
    pca9685_setPWMFreq(i2cBusConnection, 50);

    pca9685_debugMainRegisterList(debugOutputStream, i2cBusConnection);

    /*
    int i;
    for (i = 100; i < 500; i += 20) {
        pca9685_setPWM(i2cBusConnection, 1, 0, i);
        delaymSec(100);
    }
    pca9685_debugMainRegisterList(debugOutputStream, i2cBusConnection);
*/
    /*
    int i;
    for (i = 1000; i < 2000; i++) {
        pca9685_setPWM(i2cBusConnection, 0, 500, i);
        delaymSec(10);
    }
    delaymSec(1000);
    */
    
    //pca9685_setPWM(i2cBusConnection, 1, 1000, 2200);
    
    // pca9685_debugMainRegisterList(debugOutputStream, i2cBusConnection);
}

void pca9685_reset(I2cBusConnection* i2cBusConnection) {
    // BUGGED : pca9685_write8(i2cBusConnection, I2C_GENERAL_ADDRESS, PCA9685_SOFTWARE_RESET);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Start / Address
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, I2C_GENERAL_ADDRESS);
    WaitI2C(i2cBus);
    // Register
    portableMasterWriteI2C(i2cBusConnection, PCA9685_SOFTWARE_RESET);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    delaymSec(10);
}

// TODO : BUGGED !!
void pca9685_setPWMFreq(I2cBusConnection* i2cBusConnection, float frequency) {
    frequency *= 0.9; // Correct for overshoot in the frequency setting (see issue #11).
    float prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= frequency;
    prescaleval -= 1;

    // unsigned char prescale = floor(prescaleval + 0.5);
    unsigned char prescale = 121;
 
    // Frequency could only be change if sleep
    pca9685_write8(i2cBusConnection, PCA9685_MODE1, PCA9685_MODE1_MASK_ALLCALL | PCA9685_MODE1_MASK_SLEEP);
    delaymSec(5);
    pca9685_write8(i2cBusConnection, PCA9685_PRESCALE, prescale);            // set the prescaler
    delaymSec(5);
    // Stop sleeping
    pca9685_write8(i2cBusConnection, PCA9685_MODE1, PCA9685_MODE1_MASK_ALLCALL | PCA9685_MODE1_MASK_AUTO_INC);
}

void pca9685_setPWM(I2cBusConnection* i2cBusConnection, unsigned char pwmIndex, unsigned int on, unsigned int off) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterWaitSendI2C(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, LED0_ON_L + 4 * pwmIndex);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, on);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, on >> 8);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, off);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, off >> 8);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    /*
    pca9685_write8(i2cBusConnection, LED0_ON_L + 4 * pwmIndex, on);
    delaymSec(10);
    pca9685_write8(i2cBusConnection, LED0_ON_H + 4 * pwmIndex, on >> 8);
    delaymSec(10);
    pca9685_write8(i2cBusConnection, LED0_OFF_L + 4 * pwmIndex, off);
    delaymSec(10);
    pca9685_write8(i2cBusConnection, LED0_OFF_H + 4 * pwmIndex, off >> 8);    
    delaymSec(10);
     * */
}

void pca9685_setPin(I2cBusConnection* i2cBusConnection, unsigned char pwmIndex, unsigned int value, bool invert) {
    /*
    OutputStream* debugOutputStream = getInfoOutputStreamLogger();
    appendStringLN(debugOutputStream, "pca9685_setPin !");
    appendStringAndDecLN(debugOutputStream, "pwmIndex=", pwmIndex);
    appendStringAndDecLN(debugOutputStream, "value=", value);
    */
    // Clamp value between 0 and 4095 inclusive.
    value = minInt(value, 4095);
    if (invert) {
        if (value == 0) {
            // Special value for signal fully on.
            pca9685_setPWM(i2cBusConnection, pwmIndex, 4096, 0);
        } else if (value == 4095) {
            // Special value for signal fully off.
            pca9685_setPWM(i2cBusConnection, pwmIndex, 0, 4096);
        } else {
            pca9685_setPWM(i2cBusConnection, pwmIndex, 0, 4095 - value);
        }
    } else {
        if (value == 4095) {
            // Special value for signal fully on.
            pca9685_setPWM(i2cBusConnection, pwmIndex, 4096, 0);
        } else if (value == 0) {
            // Special value for signal fully off.
            pca9685_setPWM(i2cBusConnection, pwmIndex, 0, 4096);
        } else {
            pca9685_setPWM(i2cBusConnection, pwmIndex, 0, value);
        }
    }
}

void pca9685_write8(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned char data) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Start
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);

    // Register
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);

    // Data
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

unsigned char pca9685_read8(I2cBusConnection* i2cBusConnection, unsigned char reg) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    unsigned char result;
    portableMasterWaitSendI2C(i2cBusConnection);
    
    // Start
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);

    // Register
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);
    
    // Restart in read mode
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // send read address (bit zero is set)
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 1);
    WaitI2C(i2cBus);
    
    result = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // portableMasterAckI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);

    return result;
}

void pca9685_test(I2cBusConnection* i2cBusConnection) {

}
