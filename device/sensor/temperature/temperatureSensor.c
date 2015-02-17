#include "temperatureSensor.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

void printTemperatureSensor(OutputStream* outputStream, I2cBus* i2cBus){
    appendDec(outputStream, getTemperatureSensor(i2cBus));
}
