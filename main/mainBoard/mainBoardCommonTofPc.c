#include "mainBoardCommonTofPc.h"

#include "mainBoardCommonTof.h"

#include "../../drivers/tof/pc/tofListPc.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

#include "../../device/deviceList.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// -> IO EXPANDER
#include "../../drivers/ioExpander/ioExpanderList.h"

#include "../../drivers/i2c/multiplexer/multiplexerList.h"

#include "../../robot/strategy/gameStrategyContext.h"

TofSensorList* mainBoardCommonTofInitDriversPc(RobotConfig* robotConfig, 
                                               MultiplexerList* multiplexerList,
                                               IOExpanderList* ioExpanderList,
                                               GameStrategyContext* gameStrategyContext) {
    TofSensorList* tofSensorList = mainBoardCommonTofInitDrivers(robotConfig, multiplexerList, ioExpanderList);
    initTofSensorListPc(tofSensorList, tofSensorList->tofSensorArray, MAIN_BOARD_TOF_SENSOR_LIST_LENGTH, (int*) gameStrategyContext);

    return tofSensorList;
}