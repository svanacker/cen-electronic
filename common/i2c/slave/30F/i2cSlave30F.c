#include "../i2cSlave.h"

#include <i2c.h>

unsigned char portableSlaveReadI2C(void) {
	unsigned char result = SlaveReadI2C();
	return result;
}

void portableSlaveWriteI2C(unsigned char c) {
	SlaveWriteI2C(c);
}
