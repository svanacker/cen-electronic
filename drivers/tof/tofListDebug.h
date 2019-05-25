#ifndef TOF_LIST_DEBUG_H
#define TOF_LIST_DEBUG_H

#include "tofList.h"
#include "tofListDebug.h"

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"


// COMMON PART
#define TOF_SENSOR_INDEX_COLUMN_LENGTH		                            3
#define TOF_SENSOR_NAME_COLUMN_LENGTH		                           13
#define TOF_SENSOR_TYPE_COLUMN_LENGTH		                            7
#define TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH		                        5
#define TOF_SENSOR_START_RESULT_COLUMN_LENGTH		                    6
#define TOF_SENSOR_ENABLE_COLUMN_LENGTH                                 6

// CONFIG PART

#define TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH                    5 
#define TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH                    5
#define TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH        7
#define TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH                   7
#define TOF_SENSOR_VALUE_BEAM_ANGLE_DEGREE_LENGTH                       5
#define TOF_SENSOR_VALUE_ORIENTATION_ANGLE_DEGREE_LENGTH                7
#define TOF_SENSOR_VALUE_DISTANCE_FROM_ROBOT_CENTER_MM_COLUMN_LENGTH    6 
#define TOF_SENSOR_VALUE_ANGLE_FROM_ROBOT_CENTER_DEGREE_COLUMN_LENGTH   7

// NETWORK PART

#define TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH                                 8
#define TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH                                 5
#define TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH                                 5
#define TOF_SENSOR_I2C_BUS_NEW_ADDRESS_COLUMN_LENGTH                           8
#define TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH                              10
#define TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH                           7
#define TOF_SENSOR_HAS_HARDWARE_RESTART_COLUMN_LENGTH                          8
#define TOF_SENSOR_HARDWARE_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH         8

#define TOF_SENSOR_LAST_COLUMN		                                           0

// DETECTION PART

#define TOF_SENSOR_VALUE_DISTANCE_IN_RANGE_COLUMN_LENGTH                8

#define TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH                     8
#define TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH                     8
#define TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH                         9
#define TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH                         9



/**
 * Print a list of tof Sensor.
 */
void printTofSensorDetectionTable(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian);

/**
* Default Print function of the Config Table List.
* Could be override / configure for specific Tof
*/
void printTofSensorConfigTable(OutputStream* outputStream, TofSensorList* tofSensorList);

/**
* Default Print function of the Network Table List.
* Could be override / configure for specific Tof
*/
void printTofSensorNetworkTable(OutputStream* outputStream, TofSensorList* tofSensorList);

#endif
