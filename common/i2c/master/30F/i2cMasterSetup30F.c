#include <i2c.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../i2cMasterSetup.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/master/i2cMaster.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"

static bool initialized = false;

void i2cMasterInitialize(I2cBus* i2cBus) {
    // Avoid more than one initialization
    if (initialized) {
        appendString(getDebugOutputStreamLogger(), "I2C Master already initialized\n");
        return;
    }
    int I2C_BRG = 0x10B;    // 100kHz for PIC30
    // Configure I2C for 7 bit address mode
    int I2C_CON =
//                    I2C_ON & // Warning solved : #FFFF with & ==> NO EFFECT
//                    I2C_IDLE_CON &
//                    I2C_CLK_HLD &
//                    I2C_IPMI_DIS &
                        I2C_7BIT_ADD
                & I2C_SLW_DIS
                & I2C_SM_DIS
                & I2C_GCALL_DIS
                & I2C_STR_DIS
                & I2C_NACK
                & I2C_ACK_EN
                & I2C_RCV_EN
                & I2C_STOP_DIS
                & I2C_RESTART_DIS
                & I2C_START_DIS;
    OpenI2C(I2C_CON, I2C_BRG);

    WaitI2C(i2cBus);

    appendString(getDebugOutputStreamLogger(), "I2C Master CONF=");
    appendBinary16(getDebugOutputStreamLogger(), I2C_CON, 4);
    appendCRLF(getDebugOutputStreamLogger());

    initialized = true;
}

void i2cMasterFinalize(I2cBus* i2cBus) {
    if (initialized) {
        initialized = false;
        portableMasterCloseI2C(i2cBus);
    }
}
