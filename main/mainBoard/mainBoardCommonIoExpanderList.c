
#include "mainBoardCommonTof32.h"
#include "mainBoardCommonTof.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

#include "../../device/deviceList.h"

// IO Expander
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"
#include "../../device/ioExpander/ioExpanderDevice.h"

// -> IO EXPANDER
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/ioExpanderPcf8574.h"
#include "../../drivers/ioExpander/pcf8574.h"

// IO Expander
static IOExpanderList ioExpanderList;
static IOExpander ioExpanderArray[MAIN_BOARD_IO_EXPANDER_LIST_LENGTH];

IOExpanderList* mainBoardCommonGetIOExpanderList(void) {
    return &ioExpanderList;
}

void mainBoardCommonIOExpanderListAddDevices32(void) {
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));
}

IOExpanderList* mainBoardCommonIOExpanderListInitDrivers32(void) {
    // IO Expander List
    appendString(getDebugOutputStreamLogger(), "IO Expander List ...");
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) &ioExpanderArray, MAIN_BOARD_IO_EXPANDER_LIST_LENGTH);

    I2cBus* ioExpanderBus = getI2cBusByIndex(MAIN_BOARD_IO_EXPANDER_BUS_INDEX);

    // -> Strategy    
    I2cBusConnection* ioExpanderStrategyI2cBusConnection = addI2cBusConnection(ioExpanderBus, PCF8574_ADDRESS_2, true);
    IOExpander* ioExpanderStrategy = getIOExpanderByIndex(&ioExpanderList, MAIN_BOARD_IO_EXPANDER_STRATEGY_INDEX);
    initIOExpanderPCF8574(ioExpanderStrategy, ioExpanderStrategyI2cBusConnection);
    
    // -> IO Expander (either classical or IOButtonBoard)
    I2cBusConnection* ioExpanderButtonBoardBusConnection = addI2cBusConnection(ioExpanderBus, PCF8574_ADDRESS_0, true);
    IOExpander* ioExpanderButtonBoard = getIOExpanderByIndex(&ioExpanderList, MAIN_BOARD_IO_EXPANDER_IOBOARD_INDEX);
    initIOExpanderPCF8574(ioExpanderButtonBoard, ioExpanderButtonBoardBusConnection);
    
    // BEEP Expander
    I2cBusConnection* beepIOExpanderBusConnection = addI2cBusConnection(ioExpanderBus, PCF8574_ADDRESS_1, true);
    IOExpander* beepIOExpander = getIOExpanderByIndex(&ioExpanderList, MAIN_BOARD_IO_EXPANDER_BEEP_INDEX);
    initIOExpanderPCF8574(beepIOExpander, beepIOExpanderBusConnection);


    // End of IOExpanderList
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    
    return &ioExpanderList;
}

