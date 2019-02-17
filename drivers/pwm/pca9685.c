#include "pca9685.h"
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


// DEBUG

#define PCA9685_DEBUG_REG_COLUMN_LENGTH	             10
#define PCA9685_DEBUG_REG_HEX_COLUMN_LENGTH	         10
#define PCA9685_DEBUG_REG_NAME_COLUMN_LENGTH	     15
#define PCA9685_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH	 10
#define PCA9685_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH	 10
#define PCA9685_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH	 15

/**
* Private.
*/
void pca9685_printListHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "#Reg", PCA9685_DEBUG_REG_COLUMN_LENGTH);
	appendStringHeader(outputStream, "#Reg Hex", PCA9685_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Reg Name", PCA9685_DEBUG_REG_NAME_COLUMN_LENGTH);   
    appendStringHeader(outputStream, "Dec Value", PCA9685_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hex Value", PCA9685_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Bin Value", PCA9685_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Private
 * @param i2cBusConnection
 */
void pca9685_debugMainRegister(OutputStream* outputStream, I2cBusConnection* i2cBusConnection, unsigned char reg, const char* regName) {
    unsigned value = pca9685_read8(i2cBusConnection, reg);
	appendDecTableData(outputStream, reg, PCA9685_DEBUG_REG_COLUMN_LENGTH);
	appendHex4TableData(outputStream, reg, PCA9685_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringTableData(outputStream, regName, PCA9685_DEBUG_REG_NAME_COLUMN_LENGTH);
    appendDecTableData(outputStream, value, PCA9685_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, value, PCA9685_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendBinary8TableData(outputStream, value, 4, PCA9685_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}

void pca9685_debugMainRegisterList(OutputStream* outputStream, I2cBusConnection* i2cBusConnection) {
    pca9685_printListHeader(outputStream);
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_MODE1, "MODE1");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_PRESCALE, "PRESCALER");
    // BUG WITH MODE 2 READ : pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_MODE2, "MODE2");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_SUBADR1, "SUBADR1");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_SUBADR2, "SUBADR2");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_SUBADR3, "SUBADR3");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9885_ALLCALLADR, "ALLCALLADR");

    // LED 0
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_L, "LED0_ON_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_H, "LED0_ON_H");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_L, "LED0_OFF_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_H, "LED0_OFF_H");    

    // LED 1
    /*
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_L + 4, "LED1_ON_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_H + 4, "LED1_ON_H");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_L + 4, "LED1_OFF_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_H + 4, "LED1_OFF_H");    
    */
    appendTableHeaderSeparatorLine(outputStream);
}


void pca9685_init(I2cBusConnection* i2cBusConnection) {
    pca9685_reset(i2cBusConnection);
    
    OutputStream* debugOutputStream = getInfoOutputStreamLogger();
    pca9685_debugMainRegisterList(debugOutputStream, i2cBusConnection);

    // set a default frequency
    pca9685_setPWMFreq(i2cBusConnection, 50);
    
    // No Sleep anymore
    pca9685_write8(i2cBusConnection, PCA9685_MODE1, PCA9685_MODE1_MASK_ALLCALL);
    
    pca9685_setPWM(i2cBusConnection, 0, 0, 1500);
    delaymSec(1000);
    pca9685_setPWM(i2cBusConnection, 1, 1200, 0);
    
    pca9685_debugMainRegisterList(debugOutputStream, i2cBusConnection);
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
    unsigned char prescale = 135;
    
    unsigned char oldmode = pca9685_read8(i2cBusConnection, PCA9685_MODE1);
    unsigned char newmode = (oldmode & 0b11111111) | PCA9685_MODE1_MASK_SLEEP; // sleep !
 
    pca9685_write8(i2cBusConnection, PCA9685_MODE1, newmode);                  // go to sleep

    newmode = pca9685_read8(i2cBusConnection, PCA9685_MODE1);

    pca9685_write8(i2cBusConnection, PCA9685_PRESCALE, prescale);            // set the prescaler
    // pca9685_write8(i2cBusConnection, PCA9685_MODE1, oldmode);                // back to old mode
    delaymSec(5);
    // pca9685_write8(i2cBusConnection, PCA9685_MODE1, oldmode | PCA9685_MODE1_MASK_AUTO_INC); //  This sets the MODE1 register to turn on auto increment.

    // pca9685_write8(i2cBusConnection, PCA9685_MODE1, (oldmode & (~PCA9685_MODE1_MASK_SLEEP)));// Stop sleep
}

void pca9685_setPWM(I2cBusConnection* i2cBusConnection, unsigned char pwmIndex, unsigned int on, unsigned int off) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterWaitSendI2C(i2cBusConnection);
    // Wait till Start sequence is completed
    WaitI2C(i2cBus);

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
}

void pca9685_setPin(I2cBusConnection* i2cBusConnection, unsigned char pwmIndex, unsigned int value, bool invert) {
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
    
    // portableMasterNackI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);

    return result;
}

void pca9685_test(I2cBusConnection* i2cBusConnection) {

}
