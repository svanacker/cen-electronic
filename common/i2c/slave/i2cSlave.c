#include "i2cSlave.h"
#include "i2cSlaveLink.h"

/** The I2C link used by the interrupt routine. */
static StreamLink* i2cStreamLink;

void setI2cStreamLink(StreamLink* streamLink) {
    i2cStreamLink = streamLink;
}

StreamLink* getI2cStreamLink() {
    return i2cStreamLink;
}
