#include <plib.h>

#include "pcf8573p.h"
#include "../../common/I2C/I2Ccommon.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void getPcf8573Clock(Pcf8573Clock* clock) {
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8573P_WRITE_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(0x00);
    WaitI2C();
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8573P_READ_ADDRESS);
    WaitI2C();
    clock->hour = portableMasterReadI2C();
    AckI2C1();
    WaitI2C();
    clock->min = portableMasterReadI2C();
    AckI2C1();
    WaitI2C();
    clock->day = portableMasterReadI2C();
    AckI2C1();
    WaitI2C();
    clock->month = portableMasterReadI2C();
    NotAckI2C1();
    WaitI2C();
    portableCloseI2C();
    WaitI2C();
}

void setPcf8573Clock(Pcf8573Clock* clock) {
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8573P_WRITE_ADDRESS);
    portableMasterWriteI2C(0x00);
    portableMasterWriteI2C(clock->hour);
    portableMasterWriteI2C(clock->min);
    portableMasterWriteI2C(clock->day);
    portableMasterWriteI2C(clock->month);
    portableCloseI2C();
    WaitI2C();
}

void writePcf8573ClockToOutputStream(OutputStream* outputStream, Pcf8573Clock* clock) {    
    appendDec(outputStream, clock->hour);
    appendString(outputStream, ":");
    appendDec(outputStream, clock->min);

    appendString(outputStream, " ");
    appendDec(outputStream, clock->day);

    append(outputStream, '/');
    appendDec(outputStream, clock->month);
}
