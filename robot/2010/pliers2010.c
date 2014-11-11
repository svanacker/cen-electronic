#include "pliers2010.h"

#include "../../common/delay/delay30F.h"
#include "../../device/device.h"
#include "../../device/drivers/sd21.h"
#include "../../device/drivers/pcf8574.h"

// ALL VALUES ARE FOR LEFT / RIGHT
int plierUpDownIndex[2] = {PLIER_SERVO_UP_DOWN_LEFT_INDEX, PLIER_SERVO_UP_DOWN_RIGHT_INDEX};
int plierOpenCloseIndex[2] = {PLIER_SERVO_OPEN_CLOSE_LEFT_INDEX, PLIER_SERVO_OPEN_CLOSE_RIGHT_INDEX};
int sensorIndex[2] = {PLIER_SERVO_SENSOR_LEFT_INDEX, PLIER_SERVO_SENSOR_RIGHT_INDEX};
// int contactorMasks[2] = {PIN_CONTACTOR_LEFT_MASK, PIN_CONTACTOR_RIGHT_MASK};
int metallicSensorMasks[2] = {PIN_METALLIC_SENSOR_LEFT_MASK, PIN_METALLIC_SENSOR_RIGHT_MASK};

// Up / Down operations
/* OLD VALUE : 12/05/2010
int upValues[2] = { 0x0320, 0x07D0 };
int downPosition1Values[2] = { 0x03E8, 0x0780 };
int downPosition2Values[2] = { 0x05DC, 0x0580 };
int downValues[2] = { 0x07D0, 0x0320 };
*/
int upValues[2] = { 0x0430, 0x600  };
int downPosition1Values[2] = { 0x0480, 0x05F0 };
int downPosition2Values[2] = { 0x05DC, 0x0480 };
int downValues[2] = { 0x00830, 0x0200 };

// Open / Close operations
int openPliers[2] = { 0x0400, 0x0400 };
//int openMiddlePliers[2] = { 0x05DC, 0x05DC };
int openMiddleSmallPliers[2] = { 0x0500, 0x0500 };
int openMiddlePliers[2] = { 0x0620, 0x05A0 };
int closePliers[2] = { 0x0820, 0x07D0 };

// Sensor operations
// begin value to not be too large for the robot
int beginUpSensorValues[2] = { 0x03A8, 0x0860 };
int upSensorValues[2] = { 0x03C8, 0x0830};
int downSensorValues[2] = { 0x0740, 0x0480};

// Temporisation
#define LONG_TEMP 500
#define MIDDLE_TEMP 300
#define SHORT_TEMP 100
/*
#define LONG_TEMP 2000
#define MIDDLE_TEMP 2000
#define SHORT_TEMP 2000
*/


// Private functions

void commandServo(int servoIndex, int position) {
    // void commandSD21(char servo, char speed, int position);
    commandSD21(servoIndex, 255, position);
}

int getUpDownServoIndex(int plierIndex) {
    return plierUpDownIndex[plierIndex];
}

int getOpenCloseServoIndex(int plierIndex) {
    return plierOpenCloseIndex[plierIndex];
}

int getSensorServoIndex(int plierIndex) {
    return sensorIndex[plierIndex];
}

/*
int getContactorMask(int plierIndex) {
    return contactorMasks[plierIndex];
}
*/

int getMetallicSensorMask(int plierIndex) {
    return metallicSensorMasks[plierIndex];
}

unsigned char readInput(unsigned char inputMask) {
    unsigned char result = readPCF8574(PCF8574_BASE_ADDRESS, PCF8574_CONTACTOR_ADDRESS, inputMask);
    return result;
}

// SENSOR

void beginUpSensor(int plierIndex) {
    commandServo(getSensorServoIndex(plierIndex), beginUpSensorValues[plierIndex]);    
}

void upSensor(int plierIndex) {
    commandServo(getSensorServoIndex(plierIndex), upSensorValues[plierIndex]);    
}

void downSensor(int plierIndex) {
    commandServo(getSensorServoIndex(plierIndex), downSensorValues[plierIndex]);    
}

unsigned char isMetalDetected(int plierIndex) {
    return readInput(getMetallicSensorMask(plierIndex));
}

// Operations

void preparePlier(int plierIndex) {
    downPlier(plierIndex);
    openPlier(plierIndex);
}

void takeAndLoadCorn(int plierIndex) {
    // take the corn
    closePlier(plierIndex);
    longTemp();
    upPlier(plierIndex);
    longTemp();
    middleTemp();

    int i=0;

    for (i=0; i<TRIES_COUNT_TO_LOAD_CORN; i++) {
        openPlierMiddleSmallPosition(plierIndex);
        middleTemp();
        openPlierMiddlePosition(plierIndex);
        middleTemp();
        downPlierPosition1(plierIndex);
        longTemp();
        openPlier(plierIndex);
        shortTemp();
        downPlierPosition2(plierIndex);
        closePlier(plierIndex);
        middleTemp();
        upPlier(plierIndex);
        longTemp();
    }

    // end of sequence : relaxing position
    downPlierPosition1(plierIndex);

    // New from 13/05/2010
    openPlier(plierIndex);
}

// Public functions

void waitPlier( int delay ) {
    delaymSec(delay);
}

void longTemp( void ) {
    waitPlier(LONG_TEMP);
}

void middleTemp( void ) {
    waitPlier(MIDDLE_TEMP);
}

void shortTemp( void ) {
    waitPlier(SHORT_TEMP);
}

void pliersInTheRobot( void ) {
    int index;
    for (index = 0; index < PLIERS_COUNT; index++) {
        // Plier
        closePlier(index);
        downPlierPosition1(index);
        // Sensors
        beginUpSensor(index);
    }
}

void pliersAfterStart( void ) {
    int index;
    for (index = 0; index < PLIERS_COUNT; index++) {
        upSensor(index);
    }    
}

// UP / DOWN

void upPlier(int plierIndex) {
    commandServo(getUpDownServoIndex(plierIndex), upValues[plierIndex]);    
}

void downPlier(int plierIndex) {
    commandServo(getUpDownServoIndex(plierIndex), downValues[plierIndex]);    
}

void downPlierPosition1(int plierIndex) {
    commandServo(getUpDownServoIndex(plierIndex), downPosition1Values[plierIndex]);    
}

void downPlierPosition2(int plierIndex) {
    commandServo(getUpDownServoIndex(plierIndex), downPosition2Values[plierIndex]);    
}

// OPEN / CLOSE

void openPlier(int plierIndex) {
    commandServo(getOpenCloseServoIndex(plierIndex), openPliers[plierIndex]);
}

void openPlierMiddlePosition(int plierIndex) {
    commandServo(getOpenCloseServoIndex(plierIndex), openMiddlePliers[plierIndex]);
}

void openPlierMiddleSmallPosition(int plierIndex) {
    commandServo(getOpenCloseServoIndex(plierIndex), openMiddleSmallPliers[plierIndex]);
}

void closePlier(int plierIndex) {
    commandServo(getOpenCloseServoIndex(plierIndex), closePliers[plierIndex]);
}

// DEVICE INTERFACE

void initPliers2010(void) {
    getSD21SoftwareRevision();
    getSD21BatteryLevel();
    pliersInTheRobot();
    
}

void stopPliers2010(void) {
    pliersInTheRobot();
}

const char* getPliers2010DeviceName( void ) {
    return "Pliers2010";
}

unsigned int getPliers2010SoftwareRevision(void) {
    return 1; 
}

unsigned int isPliers2010DeviceOk() {
    return isSD21DeviceOk();
}

DeviceDescriptor getPliers2010DeviceDescriptor() {
    DeviceDescriptor result;
    result.deviceInit = &initPliers2010;
    result.deviceShutDown = &stopPliers2010;
    result.deviceIsOk = &isPliers2010DeviceOk;
    result.deviceGetSoftwareRevision = &getPliers2010SoftwareRevision;
    result.deviceGetName = &getPliers2010DeviceName;
    result.enabled = 1;

    return result;
}
