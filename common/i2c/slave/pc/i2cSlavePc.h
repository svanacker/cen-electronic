#ifndef I2C_SLAVE_PC_H
#define I2C_SLAVE_PC_H

#include "../../../../common/io/buffer.h"

Buffer* getI2CSlaveToMasterPcBuffer(void);

/**
 * Function to call to handle the I2C (use Pipe) data from the master.
 */
void handleI2CDataFromMaster(void);

/**
* Function to call to send through the I2C (use Pipe) data from the slave to the master.
*/
void sendI2CDataToMaster(void);

#endif
