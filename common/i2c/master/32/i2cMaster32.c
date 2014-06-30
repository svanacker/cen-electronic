#include "../../../../common/commons.h"

#include <legacy/i2c_legacy.h>

#include "../i2cMaster.h"

#include "../../../../common/delay/cenDelay.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/io/buffer.h"


inline int portableMasterWriteI2C(char data) {
	return MasterWriteI2C1(data);
}

inline char portableMasterReadI2C() {
	return MasterReadI2C1();
}

inline void portableCloseI2C() {
	CloseI2C1();
}

inline void portableMasterWaitSendI2C( void ) {
	// TODO !!!
}
