#include "strategyTofSensorList2018.h"

#include "../../common/math/cenMath.h"

#include "../../drivers/tof/tofList.h"

// TOF MANAGEMENT

void setTofListOrientationAngle2018(TofSensorList* tofSensorList) {
    TofSensor* backRightSensor0 = getTofSensorByIndex(tofSensorList, BACK_RIGHT_SENSOR_INDEX);
    TofSensor* backMiddleSensor1 = getTofSensorByIndex(tofSensorList, BACK_MIDDLE_SENSOR_INDEX);
    TofSensor* backLeftSensor2 = getTofSensorByIndex(tofSensorList, BACK_LEFT_SENSOR_INDEX);

    TofSensor* frontRightSensor3 = getTofSensorByIndex(tofSensorList, FRONT_RIGHT_SENSOR_INDEX);
    TofSensor* frontMiddleSensor4 = getTofSensorByIndex(tofSensorList, FRONT_MIDDLE_SENSOR_INDEX);
    TofSensor* frontLeftSensor5 = getTofSensorByIndex(tofSensorList, FRONT_LEFT_SENSOR_INDEX);

    // Orientation
    backRightSensor0->orientationRadian = degToRad(BACK_RIGHT_SENSOR_ANGLE_DEGREE);
    backMiddleSensor1->orientationRadian = degToRad(BACK_MIDDLE_SENSOR_ANGLE_DEGREE);
    backLeftSensor2->orientationRadian = degToRad(BACK_LEFT_SENSOR_ANGLE_DEGREE);

    frontRightSensor3->orientationRadian = degToRad(FRONT_RIGHT_SENSOR_ANGLE_DEGREE);
    frontMiddleSensor4->orientationRadian = degToRad(FRONT_MIDDLE_SENSOR_ANGLE_DEGREE);
    frontLeftSensor5->orientationRadian = degToRad(FRONT_LEFT_SENSOR_ANGLE_DEGREE);

    // Threshold
    backRightSensor0->thresholdDistanceMM = BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD;
    backMiddleSensor1->thresholdDistanceMM = BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD;
    backLeftSensor2->thresholdDistanceMM = BACK_LEFT_SENSOR_DISTANCE_THRESHOLD;

    frontRightSensor3->thresholdDistanceMM = FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD;
    frontMiddleSensor4->thresholdDistanceMM = FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD;
    frontLeftSensor5->thresholdDistanceMM = FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD;

}