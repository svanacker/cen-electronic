#include "mainBoardCommonLcd.h"

#include <stdbool.h>

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/logHandlerList.h"

#include "../../device/deviceConstants.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"

#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

// LCD
#include "../../drivers/lcd/lcd.h"

#include "../../robot/config/robotConfig.h"

// lcd DEBUG 
static OutputStream lcdOutputStream;

void mainBoardCommonLcdAddDevices(void) {
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
}

void mainBoardCommonLcdInit(RobotConfig* robotConfig) {
        // LCD (LCD via Parallel interface)
    initLCDOutputStream(&lcdOutputStream);
    addLogHandler("LCD", &lcdOutputStream, LOG_LEVEL_ERROR, LOG_HANDLER_CATEGORY_ALL_MASK);

    // Backlight the LCD is needed
    bool backlight = isConfigSet(robotConfig, CONFIG_LCD_MASK);
    setBacklight(backlight);
}
