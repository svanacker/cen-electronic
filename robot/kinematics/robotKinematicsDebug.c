#include "robotKinematicsDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/math/cenMath.h"

#define ROBOT_KINEMATICS_KEY_COLUMN_LENGTH        65
#define ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH  10
#define ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH      10
#define ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH       18
#define ROBOT_KINEMATICS_LAST_COLUMN               0

void printRobotKinematicsStoredValuesTableHeader(OutputStream* outputStream) {
	println(outputStream);

	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Key", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Hex Value", ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Dec Value", ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Unit ", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
	appendTableHeaderSeparatorLine(outputStream);
}
void printRobotKinematicsComputedValuesTableHeader(OutputStream* outputStream) {
    println(outputStream);

    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Key", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dec Value", ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Unit ", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}

void printRobotKinematicsTable(OutputStream* outputStream, RobotKinematics* robotKinematics) {
    printRobotKinematicsStoredValuesTableHeader(outputStream);
    // ROBOT TYPE
	appendStringTableData(outputStream, "Robot Type", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHex2TableData(outputStream, getKinematicsRobotType(robotKinematics), ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	addRobotTypeTableData(outputStream, getKinematicsRobotType(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "N/A", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
 
    appendTableHeaderSeparatorLine(outputStream);
    
    // CODER VALUE
	appendStringTableData(outputStream, "Coder Wheel Average Diameter", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHexFloat6TableData(outputStream, getCoderWheelAverageDiameterMM(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderWheelAverageDiameterMM(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

	appendStringTableData(outputStream, "Coder Wheel Average Delta Diameter", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHexFloat6TableData(outputStream, getCoderWheelAverageDeltaDiameterMM(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderWheelAverageDeltaDiameterMM(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

	appendStringTableData(outputStream, "Coder Wheel Distance Between Wheels", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendHexFloat6TableData(outputStream, getCoderWheelDistanceBetweenWheelsMM(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderWheelDistanceBetweenWheelsMM(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendStringTableData(outputStream, "Coder Wheel Pulse By Rotation", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, getCoderWheelPulseByRotation(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderWheelPulseByRotation(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "pulse / rotation", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    // MOTOR VALUE
    appendStringTableData(outputStream, "Motor Wheel Average Diameter", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, getMotorWheelAverageDiameterMM(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, robotKinematics->motorWheelAverageDiameterMM, ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendStringTableData(outputStream, "Motor Wheel Distance Between Wheels", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, getMotorWheelDistanceBetweenWheelsMM(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getMotorWheelDistanceBetweenWheelsMM(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendStringTableData(outputStream, "Motor Wheel Rotation By Second At Full Speed/PWM", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, getMotorWheelRotationBySecondAtFullSpeed(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getMotorWheelRotationBySecondAtFullSpeed(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "rotation / second", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendStringTableData(outputStream, "Motor Max Torque", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, getMotorMaxTorqueMilliNewton(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getMotorMaxTorqueMilliNewton(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "milliNewton", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendStringTableData(outputStream, "Motor Reductor Ratio", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, getMotorReductorRatio(robotKinematics), ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getMotorReductorRatio(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
    
    // ROBOT VALUE
    appendStringTableData(outputStream, "Robot Weight", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendHexFloat6TableData(outputStream, getRobotWeightGrams(robotKinematics), ROBOT_KINEMATICS_WEIGHT_DIGIT_PRECISION, ROBOT_KINEMATICS_HEX_VALUE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getRobotWeightGrams(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "grams", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    // COMPUTE VALUE
    printRobotKinematicsComputedValuesTableHeader(outputStream);
    // -> Speed / Acceleration
    appendStringTableData(outputStream, "Computed : Robot Speed Max", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getRobotSpeedMaxMillimeterBySecond(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm / second", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendStringTableData(outputStream, "Computed : Robot Acceleration Max", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getRobotAccelerationMaxMillimeterBySecondSquare(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm / Second^2", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);


    appendStringTableData(outputStream, "Computed : Coder Wheels Distance from Center", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderWheelsDistanceFromCenter(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
    appendStringTableData(outputStream, "Computed : Coder Left Wheel Length for One Pulse", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderLeftWheelLengthForOnePulse(robotKinematics) * MILLI_TO_NANO_FACTOR, ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "nanometer", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
    appendStringTableData(outputStream, "Computed : Coder Right Wheel Length for One Pulse", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderRightWheelLengthForOnePulse(robotKinematics) * MILLI_TO_NANO_FACTOR, ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "nanometer", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
    appendStringTableData(outputStream, "Computed : Coder Average Wheel Length for One Pulse", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderAverageWheelLengthForOnePulse(robotKinematics) * MILLI_TO_NANO_FACTOR, ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "nanometer", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
    appendStringTableData(outputStream, "Computed : Coder Wheel / Motor Wheel Average Diameter Factor", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendDecfTableData(outputStream, getCoderWheelAndMotorWheelAverageDiameterFactor(robotKinematics), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "-", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);

    appendStringTableData(outputStream, "Computed : Coder Wheel Pulse By Seconds At FullSpeed (Forward)", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getCoderWheelPulseBySecondsAtFullSpeed(robotKinematics, false), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "pulse / second", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
    appendStringTableData(outputStream, "Computed : Coder Wheel Pulse By Seconds At FullSpeed (Rotation)", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, getCoderWheelPulseBySecondsAtFullSpeed(robotKinematics, true), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "pulse / second", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
    appendStringTableData(outputStream, "Computed : Left Wheel mm for 90 deg", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendDecfTableData(outputStream, rotationInDegreeToRealDistanceForLeftWheel(robotKinematics, DEG_90), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
    appendStringTableData(outputStream, "Computed : Right Wheel mm for 90 deg", ROBOT_KINEMATICS_KEY_COLUMN_LENGTH);
	appendDecfTableData(outputStream, rotationInDegreeToRealDistanceForRightWheel(robotKinematics, DEG_90), ROBOT_KINEMATICS_VALUE_COLUMN_LENGTH);
	appendStringTableData(outputStream, "mm", ROBOT_KINEMATICS_UNIT_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_KINEMATICS_LAST_COLUMN);
    
	appendTableHeaderSeparatorLine(outputStream);
}
