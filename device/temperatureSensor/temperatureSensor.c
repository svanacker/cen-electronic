#include "temperatureSensor.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printTemperatureSensor(OutputStream* outputStream){
    appendDec(outputStream, getTemperatureSensor());
}
