#include "robotConfig.h"
#include "robotConfigDevice.h"
#include "robotConfigDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/driver.h"
#include "../../drivers/io/pcf8574.h"

/** Config is a 16 bit value */
static unsigned int config = 0;

/**
 * @private
 */
unsigned char readPCFByte(int pcfConfigAddress) {
    unsigned char read = readPCF8574(PCF8574_BASE_ADDRESS, pcfConfigAddress, 0xFF);

    // The high 4 bits of each byte is inversed => 1100 0001 is in reality : 0011 0001
    unsigned char result = read & 0x0F;
    if (read & 0x10) {
        result += 0x80;
    }
    if (read & 0x20) {
        result += 0x40;
    }
    if (read & 0x40) {
        result += 0x20;
    }
    if (read & 0x80) {
        result += 0x10;
    }
    return result;
}

void refreshConfig(void) {
    // load the value
#ifdef MPLAB_SIMULATION
    config = 0;
    return;
#endif

    unsigned char lowByte = readPCFByte(PCF8574_LOW_BYTE_CONFIG_ADDRESS);
    unsigned char highByte = readPCFByte(PCF8574_HIGH_BYTE_CONFIG_ADDRESS);


    // The both highest bit is not available => be careful to the inversion made by readPCFByte
    config = ((highByte & 0x3F) << 8) | lowByte;
}

unsigned int getConfigValue(void) {
    refreshConfig();
    return config;
}

int isConfigSet(unsigned int configMask) {
	refreshConfig();
	int intersection = (config & configMask);
    return intersection != 0;
}

char* getConfigBitString(unsigned char configIndex) {
    switch (configIndex) {
        case CONFIG_DEBUG_MASK: return "Debug";
        case CONFIG_USE_SONAR_MASK: return "UseSonar";
        case CONFIG_ROLLING_TEST_MASK: return "RollingTest";
        case CONFIG_COLOR_BLUE_MASK: return "Blue";
        default: return "?";
    }
}

/**
 * Returns a String corresponding to the configuration
 * '1' when the bit is set, '0' when not set
 */
void appendStringConfig(OutputStream* outputStream) {
    refreshConfig();
    signed int i;
    for (i = CONFIG_BIT_COUNT - 1; i >= 0; i--) {
        char c;
		if ((config & (1 << i)) > 0) {
			c = '1';
		}
        else {
            c = '0';
		}
	    append(outputStream, c);
    }
}

unsigned char isConfigDebug() {
    refreshConfig();
    return isConfigSet(CONFIG_DEBUG_MASK);
}

unsigned char getStrategy() {
    refreshConfig();
    return config & CONFIG_STRATEGY_MASK;
}

// Device interface

void initConfig(void) {
    refreshConfig();
}

void stopConfig(void) {

}

BOOL isConfigDeviceOk(void) {
    refreshConfig();
    return getConfigValue() < MAX_UNSIGNEDINT;
}

void deviceConfigHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_CONFIG) {
        // Send ack first
        appendAck(outputStream);

        // can take a little time
        refreshConfig();
        append(outputStream, COMMAND_CONFIG);
        appendHex4(outputStream, config);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initConfig,
    .deviceShutDown = &stopConfig,
    .deviceIsOk = &isConfigDeviceOk,
    .deviceHandleRawData = &deviceConfigHandleRawData
};

DeviceDescriptor* getRobotConfigDeviceDescriptor() {
    return &descriptor;
}
