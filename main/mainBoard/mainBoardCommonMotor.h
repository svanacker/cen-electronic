#ifndef MAIN_BOARD_COMMON_MOTOR_H
#define MAIN_BOARD_COMMON_MOTOR_H

#include "mainBoardCommon.h"

#include "../../io/inputStream.h"

#include "../../device/device.h"

// DEVICES

/**
 * Add the motor devices used by main Board.
 * @param serialIndex
 */
void mainBoardCommonMotorAddDevices(unsigned char serialIndex);

/**
 * TODO
 */
void mainBoardDeviceHandleMotionDeviceNotification(const Device* device, const char commandHeader, InputStream* inputStream);

// DISPATCHER

/**
 * Add the dispatcher for Motor Dispatcher.
 */
void mainBoardCommonMotorAddDispatcher(void);

// SERIAL

/**
 * Add the Open Serial Link to the Motor Board.
 */
void mainBoardCommonMotorOpenSerialLink(void);

/**
 * Add the Open Serial Link to the Motor Board to notify to the PC.
 */
void mainBoardCommonMotorNotifyOpenSerialLink(void);

// MAIN - INIT 

/**
 * Initialisation part in the Main Program of MAIN BOARD for the Motor Part.
 */
void mainBoardCommonMotorMainEndInit(void);

// HANDLE STREAM INSTRUCTION

void mainBoardCommonMotorHandleStreamInstruction(void);


#endif

