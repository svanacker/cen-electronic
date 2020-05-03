#include "mainBoardCommonColor.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../drivers/colorSensor/colorSensor.h"

#include "../../device/deviceList.h"

#include "../../device/color/colorDeviceInterface.h"
#include "../../device/color/colorDevice.h"

#include "../../drivers/colorSensor/colorSensorTcs34725.h"

static ColorSensor colorSensor;
static Color color;
static Tcs34725 tcs34725;

void mainBoardCommonColorSensorAddDevices(void) {
    addLocalDevice(getColorSensorDeviceInterface(), getColorSensorDeviceDescriptor(&colorSensor));
}

/**
 * Private Function
 * @return 
 */
enum ColorType colorSensorFindColorType(ColorSensor* colorSensor) {
    return COLOR_TYPE_UNKNOWN;
}

/**
 * Main Part of MAIN_BOARD for Color Sensor.
 */
ColorSensor* mainBoardCommonColorSensorInitDrivers() {
    I2cBus* ioColorSensorBus = getI2cBusByIndex(MAIN_BOARD_COLOR_BUS_INDEX);

    I2cBusConnection* colorSensorI2cBusConnection = addI2cBusConnection(ioColorSensorBus, TCS34725_ADDRESS, true);
    initTcs34725Struct(&tcs34725, colorSensorI2cBusConnection);
    initColorSensorTcs34725(&colorSensor, &color, &colorSensorFindColorType, &tcs34725);
    
    return &colorSensor;
}

/**
 * To get a reference on the initialized Sensor.
 */
ColorSensor* mainBoardCommonGetColorSensor(void) {
    return &colorSensor;
}
