#include <stdbool.h>

#include "adcDevice.h"
#include "adcDeviceInterface.h"

#include "../../common/adc/adcutils.h"
#include "../../common/delay/cenDelay.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../../common/timer/delayTimer.h"

#include "../device.h"

#include "../../drivers/sharp/gp2d12.h"
#include "../../drivers/sharp/gp2y0a02yk.h"
#include "../../drivers/sharp/gp2y0a21yk.h"

#define ADC_SAMPLE_COUNT 1

// DEVICE INTERFACE

void initADC(void) {

}

void stopADC(void) {

}

bool isADCDeviceOk(void) {
    return true;
}

unsigned int readAdc(unsigned char adcIndex) {
    int value = 0;
    int i;
    for (i = 0; i < ADC_SAMPLE_COUNT; i++) {
        value += getANX(adcIndex);
    }
    // to get the average
    value /= ADC_SAMPLE_COUNT;

    // value = gp2d12GetCentimerDistanceForTension(value);
    // value = gp2y0a02ykGetCentimerDistanceForTension(value);
    // value = gp2y0a21ykGetCentimerDistanceForTension(value);

    return value;
}

void deviceADCHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_GET_ADC_VALUE) {
        ackCommand(outputStream, ADC_DEVICE_HEADER, COMMAND_GET_ADC_VALUE);

        unsigned char adcIndex = readHex2(inputStream);
        unsigned int value = readAdc(adcIndex);

        appendHex4(outputStream, value);
    } else if (commandHeader == COMMANG_GET_ADC_VALUE_DEBUG_PERIOD) {
        ackCommand(outputStream, ADC_DEVICE_HEADER, COMMAND_GET_ADC_VALUE);

        unsigned char adcIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned char sampleCount = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned char delayPeriodBetweenSample = readHex2(inputStream);

        int i;
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        for (i = 1; i <= sampleCount; i++) {
            if (i > 0) {
                timerDelayMilliSeconds(100 * delayPeriodBetweenSample);
            }
            unsigned int value = readAdc(adcIndex);
            appendStringAndDec(debugOutputStream, "value=", value);
            appendStringLN(debugOutputStream, " mV");
        }
    } else if (commandHeader == COMMAND_GET_ADC_ALL_VALUES) {
        ackCommand(outputStream, ADC_DEVICE_HEADER, COMMAND_GET_ADC_ALL_VALUES);
        int i;
        for (i = 1; i <= getANXCount(); i++) {
            if (i != 1) {
                appendSeparator(outputStream);
            }
            appendHex4(outputStream, readAdc(i));
        }
    } else if (commandHeader == COMMAND_GET_ADC_LIST) {
        ackCommand(outputStream, ADC_DEVICE_HEADER, COMMAND_GET_ADC_LIST);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        printAdcList(debugOutputStream);
    }
}

static DeviceDescriptor descriptor;

DeviceDescriptor* getADCDeviceDescriptor(void) {
    initDeviceDescriptor(&descriptor,
            &initADC,
            &stopADC,
            &isADCDeviceOk,
            &deviceADCHandleRawData,
            NULL);

    return &descriptor;
}
