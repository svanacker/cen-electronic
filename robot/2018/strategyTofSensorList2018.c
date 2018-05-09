#include "strategyTofSensorList2018.h"

#include "../../common/math/cenMath.h"

#include "../../drivers/tof/tofList.h"

// TOF MANAGEMENT

void setTofListOrientationAngle2018(TofSensorList* tofSensorList, float distanceFactor) {
    unsigned int tofSensorListSize = getTofSensorListSize(tofSensorList);
    
    // Tof Sensor 0
    if (tofSensorListSize > BACK_RIGHT_SENSOR_INDEX) {
        TofSensor* backRightSensor0 = getTofSensorByIndex(tofSensorList, BACK_RIGHT_SENSOR_INDEX);
        backRightSensor0->orientationRadian = degToRad(BACK_RIGHT_SENSOR_ANGLE_DEGREE);
        backRightSensor0->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int ) (distanceFactor * BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD);
    }
    
    // Tof Sensor 1
    if (tofSensorListSize > BACK_MIDDLE_SENSOR_INDEX) {
        TofSensor* backMiddleSensor1 = getTofSensorByIndex(tofSensorList, BACK_MIDDLE_SENSOR_INDEX);
        backMiddleSensor1->orientationRadian = degToRad(BACK_MIDDLE_SENSOR_ANGLE_DEGREE);
        backMiddleSensor1->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
    }

    // Tof Sensor 2
    if (tofSensorListSize > BACK_LEFT_SENSOR_INDEX) {
        TofSensor* backLeftSensor2 = getTofSensorByIndex(tofSensorList, BACK_LEFT_SENSOR_INDEX);
        backLeftSensor2->orientationRadian = degToRad(BACK_LEFT_SENSOR_ANGLE_DEGREE);
        backLeftSensor2->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_LEFT_SENSOR_DISTANCE_THRESHOLD);
    }

    // Tof Sensor 3
    if (tofSensorListSize > FRONT_RIGHT_SENSOR_INDEX) {
        TofSensor* frontRightSensor3 = getTofSensorByIndex(tofSensorList, FRONT_RIGHT_SENSOR_INDEX); 
        frontRightSensor3->orientationRadian = degToRad(FRONT_RIGHT_SENSOR_ANGLE_DEGREE);
        frontRightSensor3->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD);
    }
    
    // Tof Sensor 4
    if (tofSensorListSize > FRONT_MIDDLE_SENSOR_INDEX) {
        TofSensor* frontMiddleSensor4 = getTofSensorByIndex(tofSensorList, FRONT_MIDDLE_SENSOR_INDEX);
        frontMiddleSensor4->orientationRadian = degToRad(FRONT_MIDDLE_SENSOR_ANGLE_DEGREE);
        frontMiddleSensor4->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
    }
    
    // Tof Sensor 5
    if (tofSensorListSize > FRONT_LEFT_SENSOR_INDEX) {
        TofSensor* frontLeftSensor5 = getTofSensorByIndex(tofSensorList, FRONT_LEFT_SENSOR_INDEX);
        frontLeftSensor5->orientationRadian = degToRad(FRONT_LEFT_SENSOR_ANGLE_DEGREE);
        frontLeftSensor5->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD);
    }
}