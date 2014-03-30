#include <stdlib.h>

#include "laserBeacon.h"
#include "beaconSystem.h"
#include "laserBeaconDevice.h"
#include "laserBeaconDeviceInterface.h"
#include "commonBeaconDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/serial/serial.h"

#include "../../device/device.h"

#include "../../robot/robotDetector.h"

#include "../../drivers/jennic/jennic5139Driver.h"
#include "../../drivers/beacon/beaconLaserDriver.h"

#include "../../main/beaconBoard/beaconBoard.h"

void deviceBeaconInit() {
    initLaserBeacon();
}

void deviceBeaconShutDown() {
	stopLaserBeacon();
}

bool deviceBeaconIsOk() {
    return TRUE;
}

void deviceBeaconHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
	// Init Coordinater
	if (header == COMMAND_INIT_JENNIC_AS_COORDINATER) {
        appendAck(outputStream);
        append(outputStream, COMMAND_INIT_JENNIC_AS_COORDINATER);
    	initJennic5139Coordinater();
	}
	// Send immediately position to router (even if beacon system is disabled)
	else if (header == COMMAND_SEND_ROBOT_POSITION_FROM_COORDINATER_TO_ROUTER) {
        appendAck(outputStream);
        append(outputStream, COMMAND_SEND_ROBOT_POSITION_FROM_COORDINATER_TO_ROUTER);
		Point* point = getOpponentRobotPosition();
		notifyRobotPosition(point);
	}
	// Get the last detected position of the robot
    else if (header == COMMAND_BEACON_POSITION) {
        // Computes position
        Point* point = getOpponentRobotPosition();
		appendAck(outputStream);

		appendRobotPosition(outputStream, COMMAND_BEACON_POSITION, point);
	// Get the configuration of the both laser
    } else if (header == COMMAND_BEACON_CONFIGURATION) {
        appendAck(outputStream);
        append(outputStream, COMMAND_BEACON_CONFIGURATION);

		OutputStream* logOutputStream = getOutputStreamLogger(INFO);
		printBeaconSystemConfiguration(logOutputStream);
	// Set the configuration of the system
    } else if (header == COMMAND_BEACON_SET_CONFIGURATION) {
        appendAck(outputStream);

		float distanceBetweenBeacon = readHex4(inputStream);
		checkIsChar(inputStream, '-');
		float calibrationX = readHex4(inputStream);
		checkIsChar(inputStream, '-');
		float calibrationY = readHex4(inputStream);

		setDistanceBetweenBeacon(distanceBetweenBeacon);
		setCalibrationPoint(calibrationX, calibrationY);
	
        append(outputStream, COMMAND_BEACON_SET_CONFIGURATION);
	// Calibration
	} else if (header == COMMAND_BEACON_CALIBRATION) {
        appendAck(outputStream);
		doBeaconCalibration();
		append(outputStream, COMMAND_BEACON_CALIBRATION);
	// Jennic Remote (router) Light on / off
	} else if (header == COMMAND_ROUTER_LIGHT) {
        appendAck(outputStream);
		unsigned char status = readHex2(inputStream);
		jennic5139RemoteLight(JENNIC_ROUTER_MAC_ADDRESS, JENNIC_LED_ALL, status != 0);
        append(outputStream, COMMAND_ROUTER_LIGHT);
	}
	// Run the servo of the beacon system
	else if (header == COMMAND_BEACON_SERVO_RUN) {
        appendAck(outputStream);
		setBeaconSystemEnabled(TRUE);
        append(outputStream, COMMAND_BEACON_SERVO_RUN);
	}
	// Stop the servo of the beacon system
	else if (header == COMMAND_BEACON_SERVO_STOP) {
        appendAck(outputStream);
		setBeaconSystemEnabled(FALSE);
        append(outputStream, COMMAND_BEACON_SERVO_STOP);
	}
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceBeaconInit,
    .deviceShutDown = &deviceBeaconShutDown,
    .deviceIsOk = &deviceBeaconIsOk,
    .deviceHandleRawData = &deviceBeaconHandleRawData,
};

DeviceDescriptor* getBeaconDeviceDescriptor() {
    return &descriptor;
}
