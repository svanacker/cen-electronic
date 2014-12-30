#include "../i2cSlave.h"

#include <plib.h>
#include <i2c.h>

unsigned char portableSlaveReadI2C(void) {
    unsigned char result = SlaveReadI2C1();
    return result;
}

void portableSlaveWriteI2C(unsigned char c) {
    SlaveWriteI2C1(c);
}
