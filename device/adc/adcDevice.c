#include "adcDevice.h"
#include "adcDeviceInterface.h"

#include "../../common/adc/adcutils.h"
#include "../../common/cmd/commonCommand.h"

#include "../../common/pwm/motorPwm.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#define ADC_SAMPLE_COUNT 5

// DEVICE INTERFACE

void initADC( void ) {

}

void stopADC( void ) {

}

unsigned int isADCDeviceOk ( void ) {
	return TRUE;
}

void deviceADCHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
	if (header == COMMAND_GET_ADC_VALUE) {
		signed int adcIndex = readSignedHex2(inputStream);
		appendAck(outputStream);

		int value = 0;
		int i;
		for (i = 0; i < ADC_SAMPLE_COUNT; i++) {
			value += getANX(adcIndex);
		}
		// to get the average
		value /= ADC_SAMPLE_COUNT;

		append(outputStream, COMMAND_GET_ADC_VALUE);
		appendHex4(outputStream, value);
	}
}

static DeviceDescriptor descriptor = {
	.deviceInit = &initADC,
	.deviceShutDown = &stopADC,
	.deviceIsOk = &isADCDeviceOk,
	.deviceHandleRawData = &deviceADCHandleRawData,
};

DeviceDescriptor* getADCDeviceDescriptor() {
	return &descriptor;
}
