#ifndef BEACON_BOARD_H
#define BEACON_BOARD_H

#include "../../common/io/buffer.h"

// LOGS
#define BEACON_LOG_HANDLER_LIST_LENGTH					2

// BEACON SYSTEM

// Bounds of detection
#define SERVO_LASER_1_MAX_LEFT_POSITION_DEFAULT_VALUE 500
#define SERVO_LASER_1_MAX_RIGHT_POSITION_DEFAULT_VALUE 1500

#define SERVO_LASER_2_MAX_LEFT_POSITION_DEFAULT_VALUE 700
#define SERVO_LASER_2_MAX_RIGHT_POSITION_DEFAULT_VALUE 1700

// Factors to determine line (between beacon and receiver) equation, with cartesian coordinates corresponding to the first laser beacon. */
#define BEACON_SERVO_1_ANGLE_DEGREE 90
#define BEACON_SERVO_1_INIT_COMPUTE_VALUE 1720
#define BEACON_SERVO_1_FACTOR 10.2

#define BEACON_SERVO_2_ANGLE_DEGREE 90
#define BEACON_SERVO_2_INIT_COMPUTE_VALUE 1480
#define BEACON_SERVO_2_FACTOR 10.2

// Width of the board game table
#define DISTANCE_BETWEEN_BEACON 2100.0f

/** 
* Time in milliseconds we consider that we do not send the position (because the last
* detection is too old (it's a risk to send obsolete Information).
*/
#define OBSOLETE_DETECTION_TIME_THRESHOLD    3000.0f

// Calibration Point
#define BEACON_CALIBRATION_POINT_X         DISTANCE_BETWEEN_BEACON / 2.0f
#define BEACON_CALIBRATION_POINT_Y         3100.0f

/** Defines the interval (in pulse for servo) to search, when we are in tracking mode. */
#define SHORT_TRACKING_INTERVAL 50


// ZIGBEE

/** 
* Time in milliseconds for each notification for the robot opponent position.
*/
#define NOTIFY_DELAY                    1000.0f

/**
* Define the MAC_ADRESS_ROUTER (64 bits) used by the coordinateur (Beacon Main).
* This constant is DEPENDANT of you MATERIAL. Adapt it to your HARDWARE.
*/
#define JENNIC_COORDINATER_MAC_ADDRESS  "0006066005651610050"
    
/**
* Define the MAC_ADRESS_ROUTER (64 bits) used by the router (Beacon Receiver).
* This constant is DEPENDANT of you MATERIAL. Adapt it to your HARDWARE.
*/
#define JENNIC_ROUTER_MAC_ADDRESS        "0006066005651610057"

Buffer* getZigbeeInputBuffer();

// BUFFER SIZE

// DEBUG UART

#define    JENNIC_DEBUG_INPUT_BUFFER_LENGTH    12
#define    JENNIC_DEBUG_OUTPUT_BUFFER_LENGTH    12

// ZIGBEE UART

#define    JENNIC_ZIGBEE_INPUT_BUFFER_LENGTH    50
#define    JENNIC_ZIGBEE_OUTPUT_BUFFER_LENGTH    50

// DRIVER

#define    JENNIC_ZIGBEE_REQUEST_DRIVER_BUFFER_LENGTH        14
#define    JENNIC_ZIGBEE_RESPONSE_DRIVER_BUFFER_LENGTH        14

// DEVICE
#define    BEACON_BOARD_DEVICE_LENGTH            7

// TIMERS
#define BEACON_BOARD_TIMER_LENGTH            2

// TIMERS
#define BEACON_RECEIVER_BOARD_TIMER_LENGTH  2

#endif
