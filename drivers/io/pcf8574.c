#include "../../common/commons32.h"

#ifdef PROG_32
	#include <p32xxxx.h>
#else
	#include <i2c.h>
#endif

#include "../../common/i2c/i2cCommon.h"

#include "pcf8574.h"

#include "../../common/delay/delay30F.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/printWriter.h"

unsigned char internalGetAddress(unsigned char addr, unsigned char devAddr) {
    unsigned char result;
    result = addr | ((devAddr & 0x07) << 1);
    return result;
}

char isPCF8574Present(unsigned char addr, unsigned char devAddr) {
    char result;
    unsigned char realAddress = internalGetAddress(addr, devAddr);
    WaitI2C();
    StartI2C();
    WaitI2C();
	#ifndef PROG_32
    while (I2CCONbits.SEN);
	#endif
    result = MasterWriteI2C(realAddress);
    WaitI2C();
    StopI2C();

    return result;
}

void writePCF8574(unsigned char addr, unsigned char devAddr, unsigned char outData, unsigned char dirs) {
    unsigned char realAddress = internalGetAddress(addr, devAddr);
    WaitI2C();
    StartI2C();
    WaitI2C();
	#ifndef PROG_32
    while (I2CCONbits.SEN);
	#endif
    MasterWriteI2C(realAddress); // send write addres
    WaitI2C();
    MasterWriteI2C(outData | dirs); // write new outputs to buffer
    WaitI2C();
    ;
    MasterWriteI2C(outData | dirs); // force data to output pins
    WaitI2C();
    StopI2C();
}

unsigned char readPCF8574(unsigned char addr, unsigned char devAddr, unsigned char dirs) {
    unsigned char result;
    unsigned char realAddress = internalGetAddress(addr, devAddr);
    IdleI2C();
    StartI2C();
	#ifndef PROG_32
    while (I2CCONbits.SEN);
	#endif
    // send read address (bit zero is set)
    MasterWriteI2C(realAddress | 1);
    IdleI2C();
    result = MasterReadI2C();
    //AckI2C();
    StopI2C();

    return (result & dirs);
}

void testPCF8574(OutputStream* outputStream) {
    char data;
    // PCF 0
    appendString(outputStream, "PCFADD0=");
    data = readPCF8574(0x40, 0, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(150);
    // PCF 1
    appendString(outputStream, " PCFADD1 : ");
    data = readPCF8574(0x40, 1, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(500);
}
