#ifndef END_MATCH_DETECTOR_DEVICE_H
#define END_MATCH_DETECTOR_DEVICE_H

#include "../../device/device.h"

/**
 * Unit which is responsable of detecting the end of the match.
 * @author svanacker
 * @version 17/04/2010
*/
#define MATCH_DURATION 85

/**
* Defines the index for the timer which detects end of the match.
*/
#define END_MATCH_DETECTOR_TIMER_CODE 20

/**
* Returns the deviceDescriptor of the end Match Detector.
*/
DeviceDescriptor* getEndMatchDetectorDeviceDescriptor();

/**
* Indicates that the match begins.
*/
void markStartMatch( void );

/**
* Get the current time for the match.
*/
int getCurrentTimeInSecond ( void );

/**
* Ask to know if the match is ending.
* @return true if the match is ending
*/
bool isEnd( void );

void showEnd(OutputStream* outputStream);

#endif


