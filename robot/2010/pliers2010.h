/**
* Pliers for 2010 Edition of the robot cup.
* PREPARATION OF PLIER
* - Down the plier
* - Open plier
* - Wait for taken mais
* TAKE_LOAD CORN
* - Close plier
* - Wait for 500 ms
* - Up the plier
* - Wait for 500 ms
* - Open the plier middle position
* - Wait for 100 ms
* - Down the plier lightly (position 1)
* - Wait for 100 ms
* - Open plier completely
* - Wait for 100 ms
* - Down the plier to the middle
* - Close plier
* - Wait for 300 ms
* - Up the plier
* - Wait for 500 ms
* - Down the plier position 1
*/
#ifndef PLIERS_2010_H
#define PLIERS_2010_H

#include "../../device/device.h"

#define PLIER_LEFT_INDEX 0
#define PLIER_RIGHT_INDEX 1

#define PLIERS_COUNT 2


// Left
#define PLIER_SERVO_UP_DOWN_LEFT_INDEX 0x14
#define PLIER_SERVO_OPEN_CLOSE_LEFT_INDEX 0x13

#define PLIER_SERVO_SENSOR_LEFT_INDEX 0x15
// #define PIN_CONTACTOR_LEFT_MASK 0b00000001
#define PIN_METALLIC_SENSOR_LEFT_MASK 0b10000000

// Right
#define PLIER_SERVO_UP_DOWN_RIGHT_INDEX 0x11
#define PLIER_SERVO_OPEN_CLOSE_RIGHT_INDEX 0x12

#define PLIER_SERVO_SENSOR_RIGHT_INDEX 0x10
// #define PIN_CONTACTOR_RIGHT_MASK 0b00000100
#define PIN_METALLIC_SENSOR_RIGHT_MASK 0b00010000

/** Address of the PCF8574 to read the information. */
#define PCF8574_CONTACTOR_ADDRESS 5

// the number of times we try to load the corn
#define TRIES_COUNT_TO_LOAD_CORN 2

// How many corn we take
#define CORN_TO_TAKE_COUNT 4

/**
* Init the pliers.
*/
void initPliers2010();

/**
* Take the corn for the plier Index.
*/
void takeAndLoadCorn(int plierIndex);

/**
* Load the corn for the plier Index into the bot.
*/
void preparePlier(int plierIndex);

void pliersInTheRobot(void);

void pliersAfterStart( void );

// TEMPORISATION

void longTemp( void );

void middleTemp( void );

void shortTemp( void );

// UP / DOWN

/**
* Up the plier.
*/
void upPlier(int plierIndex);

/**
* Down the plier.
*/
void downPlier(int plierIndex);

/**
* Down the plier to the position 1
*/
void downPlierPosition1(int plierIndex);

/**
* Down the plier to the position 2
*/
void downPlierPosition2(int plierIndex);

// OPEN / CLOSE

/**
* Open the plier.
*/
void openPlier(int plierIndex);

/**
* Open the plier to a middle position.
*/
void openPlierMiddlePosition(int plierIndex);

void openPlierMiddleSmallPosition(int plierIndex);

/**
* Close and wait.
*/
void closePlier(int plierIndex);

// SENSOR OPEN / CLOSE

/**
* Begin up the sensor to not be to large.
*/
void beginUpSensor(int plierIndex);


/**
* Up the sensor
*/
void upSensor(int plierIndex);

/**
* Down the sensor.
*/
void downSensor(int plierIndex);

/**
* Returns if we detect metal (black corn)
*/
unsigned char isMetalDetected(int plierIndex);

// DEVICE INTERFACE

/**
* Returns a device descriptor on the pliers.
*/
DeviceDescriptor getPliers2010DeviceDescriptor();

#endif
