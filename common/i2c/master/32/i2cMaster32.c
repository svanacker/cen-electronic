#include "../../../../common/commons.h"

#include <peripheral/legacy/i2c_legacy.h>

#include "../i2cMaster.h"

#include "../../../../common/delay/cenDelay.h"
#include "../../../../common/i2c/i2cCommon.h"


unsigned int portableMasterWriteI2C(unsigned char data) {
	return MasterWriteI2C1(data);
}

unsigned char portableMasterReadI2C(void) {
	return MasterReadI2C1();
}

void portableCloseI2C(void) {
	CloseI2C1();
}

inline void portableMasterWaitSendI2C( void ) {
	while (I2C1CONbits.SEN) {
	
	}
}

