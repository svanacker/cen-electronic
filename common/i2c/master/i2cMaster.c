#include "../../../common/commons.h"

#ifdef PROG_32
	#include <legacy/i2c_legacy.h>
#else
	#include <i2c.h>
#endif

#include "i2cMaster.h"

#include "../../../common/delay/delay30F.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/buffer.h"


inline unsigned int portableMasterWriteI2C(unsigned char data) {
	#ifdef PROG_32
		return MasterWriteI2C1(data);
	#else
		return MasterWriteI2C(data);
	#endif
}

inline unsigned char portableMasterReadI2C() {
	#ifdef PROG_32
		return MasterReadI2C1();
	#else
		return MasterReadI2C();
	#endif
}

inline void portableCloseI2C() {
	#ifdef PROG_32
		CloseI2C1();
	#else
		CloseI2C();
	#endif
}

void i2cMasterWriteBuffer(char address, Buffer* buffer) {
    portableStartI2C();
	#ifndef PROG_32
    while (I2CCONbits.SEN);
	#endif
    // Wait till Start sequence is completed
    WaitI2C();

    // Adress
    portableMasterWriteI2C(address);
    WaitI2C();

    int count = getBufferElementsCount(buffer);
    int i;
    for (i = 0; i < count; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(c);
        WaitI2C();
    }

    portableStopI2C();
}

void i2cMasterWriteChar(char address, char c) {
	#ifndef PROG_32
    // We append to a buffer
    portableStartI2C();
    // Wait till Start sequence is completed
    WaitI2C();

    // Adress
    portableMasterWriteI2C(c);
    WaitI2C();

    // Data
    portableMasterWriteI2C(c);
    WaitI2C();

    StopI2C();
	#endif
}

unsigned char i2cMasterReadChar(char address) {
    //	i2cMasterWriteChar(address, I2C_SLAVE_FAKE_WRITE);
    //	delaymSec(50);
    WaitI2C();

    portableStartI2C();
    WaitI2C();

    // TEST
    /*
MasterWriteI2C(address);
    WaitI2C();
    StopI2C();
    WaitI2C();
    StartI2C();
    WaitI2C();
     */

    // send the address again with read bit
    portableMasterWriteI2C(address | 0x01);
    WaitI2C();

    unsigned char data = portableMasterReadI2C();

    portableStopI2C();
    return data;
}

unsigned char i2cMasterReadRegisterValue(char address, char commandRegister) {
    // Set the register command
    WaitI2C();
    portableStartI2C();
	#ifndef PROG_32
    while (I2CCONbits.SEN);
	#endif
    // send the address
    portableMasterWriteI2C(address);
    WaitI2C();
    // send the register
    portableMasterWriteI2C(commandRegister);
    WaitI2C();
    portableStopI2C();
    WaitI2C();

    // Read the register command
    portableStartI2C();
	#ifndef PROG_32
    while (I2CCONbits.SEN);
	#endif
    // send the address again with read bit
    portableMasterWriteI2C(address | 0x01);
    WaitI2C();
    // read the data
    unsigned char data = portableMasterReadI2C();
    portableStopI2C();
    return data;
}
