#include "currentSensor.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

void printCurrentSensor(OutputStream* outputStream, Current* current){
    appendHex2(outputStream, current->readSensorValue(current));
}
