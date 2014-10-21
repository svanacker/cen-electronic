#include "../../common/commons.h"

#ifdef PROG_32
    #include <plib.h>
    #include "../../common/setup/32/picSetup32.h"
#else
    #include <i2c.h>
    #include "../../common/setup/30F/picSetup30F.h"
#endif

#include "MainJK330.h"

//include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/i2c/master/i2cMaster.h"
#include "../../common/i2c/master/i2cMasterSetup.h"

#include "../../common/i2c/master/i2cMasterOutputStream.h"
#include "../../common/i2c/master/i2cMasterInputStream.h"

#include "../../common/io/buffer.h"
#include "../../common/io/compositeOutputStream.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/streamLink.h"
#include "../../common/io/stream.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../common/pwm/pwmPic.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"
#include "../../device/deviceList.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"


#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"
#include "../../drivers/dispatcher/i2cDriverDataDispatcher.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// SYSTEM DEBUG
#include "../../device/system/systemDebugDevice.h"
#include "../../device/system/systemDebugDeviceInterface.h"

// I2C MASTER DEBUG
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

//CLOCK
#include "../../drivers/clock/PCF8563.h"

#include "../../device/clock/clock.h"
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

//TEMPERATURE SENSOR
#include "../../device/temperatureSensor/temperatureSensor.h"
#include "../../device/temperatureSensor/temperatureSensorDevice.h"
#include "../../device/temperatureSensor/temperatureSensorDeviceInterface.h"


//KEYBOARD
#include "../../drivers/keyboard/74c922.h"

// LCD
#include "../../drivers/lcd/lcd.h"
#include "../../drivers/lcd/lcd24064.h"
#include "../../drivers/lcd/lcdProvider_24064.h"

//SENSOR
#include "../../drivers/sensor/MCP9804.h"
#include "../../drivers/sensor/LM75A.h"

#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

//#include "../device/led/led.h"

//#include "../drivers/io/EEPROM_I2C.h"
#include "../../menu/menu.h"

//#ifndef MPLAB_SIMULATION
//    #ifdef PROG_32
        #define SERIAL_PORT_DEBUG         SERIAL_PORT_3
        #define SERIAL_PORT_PC             SERIAL_PORT_2
        #define SERIAL_PORT_LCD            SERIAL_PORT_5
//    #else
//        #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
//        #define SERIAL_PORT_PC             SERIAL_PORT_2
//    #endif
//#else
    // We use the same port for both
 //   #define SERIAL_PORT_PC             SERIAL_PORT_1
 //   #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
//#endif

// serial link DEBUG
static char debugInputBufferArray[MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// serial link PC
static char pcInputBufferArray[MAIN_BOARD_PC_INPUT_BUFFER_LENGTH];
static Buffer pcInputBuffer;
static char pcOutputBufferArray[MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH];
static Buffer pcOutputBuffer;
static OutputStream pcOutputStream;
static StreamLink pcSerialStreamLink;

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// DEBUG I2C
static char i2cMasterDebugOutputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// DISPATCHER I2C

// i2c->Motor
static DriverDataDispatcher motorI2cDispatcher;
static char motorBoardInputBufferArray[MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// i2c->Air Conditioning
static DriverDataDispatcher airConditioningI2cDispatcher;
static char airConditioningBoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer airConditioningBoardInputBuffer;
static InputStream airConditioningBoardInputStream;
static OutputStream airConditioningBoardOutputStream;

// i2c->Mechanical 2
static DriverDataDispatcher mechanical2I2cDispatcher;
static char mechanical2BoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer mechanical2BoardInputBuffer;
static InputStream mechanical2BoardInputStream;
static OutputStream mechanical2BoardOutputStream;

// lcd DEBUG
static OutputStream lcdOutputStream;

// logs
static LogHandler debugSerialLogHandler;
static LogHandler lcdLogHandler;


// Devices
static Device deviceListArray[MAIN_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[MAIN_BOARD_TIMER_LENGTH];


// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************

static const char* HELLO_UART_PC = "JK330 with PIC32...on UART PC\r\n";
static const char* HELLO_UART_DEBUG = "JK330 with PIC32...on UART DEBUG\r\n";
static const char* HELLO_UART_TEST = "JK330 with PIC32...on UART TEZST\r\n";

// Variable Capteur de temperature MCP9804
int BCD1, BCD2, BCD3, BCD4;
int BCD10;

//#define ACK 1
//#define NACK 0

int Temperature;

/**
 * @private
 */
void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);
}

/**
 * @private
 */
void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MAIN_BOARD_DEVICE_LENGTH);

    // Test & System
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getSystemDebugDeviceInterface(), getSystemDebugDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());

    // Local
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor());
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor());

    // Init the devices
    initDevices();  
}

void waitForInstruction(void) {
    
    // Listen instruction from pcStream->Devices
    handleStreamInstruction(
            &pcInputBuffer,
            &pcOutputBuffer,
            &pcOutputStream,
            &filterRemoveCRLF,
            NULL);
    
    // Listen instruction from debugStream->Devices
    handleStreamInstruction(
            &debugInputBuffer,
            &debugOutputBuffer,
            &debugOutputStream,
            &filterRemoveCRLF,
            NULL);
}

int main(void) {  
   
    setPicName("MAIN BOARD JK330");

    // Open the serial Link for debug
    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);

    // Open the serial Link for the PC
    openSerialLink(&pcSerialStreamLink,
            &pcInputBuffer,
            &pcInputBufferArray,
            MAIN_BOARD_PC_INPUT_BUFFER_LENGTH,
            &pcOutputBuffer,
            &pcOutputBufferArray,
            MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH,
            &pcOutputStream,
            SERIAL_PORT_PC,
            DEFAULT_SERIAL_SPEED);



   appendString(&pcOutputStream, "JK330 with PIC32...on UART PC\r");
   appendString(&debugOutputStream, "JK330 with PIC32...on UART DEBUG\r");

    //Configure les PIN de control de l'afficheur MGSLS24064
    SetupLCD_24064();

        //creer le flux lcd
   //Initialise l'afficheur LCD et affiche l'image d'accueil

    initLCDOutputStream(&lcdOutputStream);


    
    
    i2cMasterInitialize();
    initRegMCP9804 (0x00,0x18,0x01,0xE0,0x01,0x40,0x02,0x40); // 30C,20C,34C


    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&debugSerialLogHandler, "UART", &debugOutputStream, DEBUG);
    addLogHandler(&lcdLogHandler, "LCD", &lcdOutputStream, ERROR);

    init74c922();

    appendString(getOutputStreamLogger(DEBUG), getPicName());
    println(getOutputStreamLogger(DEBUG));
   

    clearScreen();
    drawPicture();

    initDevicesDescriptor();
    initDriversDescriptor();

    //Affiche la liste des loggger sur DEBUG
    printLogger(getOutputStreamLogger(DEBUG));

   appendString(getOutputStreamLogger(DEBUG), "Lecture Horloge : \r");

   //CLOCK Read
   Clock* globalClock = getGlobalClock();
   updateClockFromHardware(globalClock);

   // Print on the OutputStream
   printClock(getOutputStreamLogger(DEBUG), globalClock);
   appendCR(getOutputStreamLogger(DEBUG));

   setTemperatureAlertLimit(0x35);//35°C

   clearScreen();
   setCursorAtHome();
   menu_P(&lcdOutputStream);
   while (1){
        setCursorPosition_24064(0,23);  //raw,col

        //CLOCK Read
        Clock* globalClock = getGlobalClock();
        updateClockFromHardware(globalClock);
        // Print on the OutputStream
        printClock(&lcdOutputStream, globalClock);
        waitForInstruction();

        printTemperatureSensor(&lcdOutputStream);

        unsigned int c = readKey();
        appendHex2(&lcdOutputStream, c);

        setCursorPosition_24064(0,19);

        appendDec(&lcdOutputStream, ReadTempAmbMCP9804());
   }
}