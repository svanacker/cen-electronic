#include "tomatoe2010.h"

#include "../../common/delay/delay30F.h"
#include "../../device/drivers/rly08.h"


// Device Interface

void initTomatoe2010(void) {
	setTomatoeEnabled(0);
}

void stopTomatoe2010(void) {
	setTomatoeEnabled(0);
}

void setTomatoeEnabled(int value) {
	// To be sure
	setRelayState(TOMATOE_RELAY_INDEX, value);
	delaymSec(1);
	setRelayState(TOMATOE_RELAY_INDEX, value);
	delaymSec(10);
	setRelayState(TOMATOE_RELAY_INDEX, value);
}

const char* getTomatoe2010DeviceName( void ) {
	return "Tomatoe2010";
}

unsigned int getTomatoe2010SoftwareRevision(void) {
	return 1; 
}

unsigned int isTomatoe2010DeviceOk() {
	return isRLY08DeviceOk();
}

DeviceDescriptor getTomatoe2010DeviceDescriptor() {
	DeviceDescriptor result;
	result.deviceInit = &initTomatoe2010;
	result.deviceShutDown = &stopTomatoe2010;
	result.deviceIsOk = &isTomatoe2010DeviceOk;
	result.deviceGetSoftwareRevision = &getTomatoe2010SoftwareRevision;
	result.deviceGetName = &getTomatoe2010DeviceName;
	result.enabled = 1;

	return result;
}
