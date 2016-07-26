#include <peripheral/legacy/i2c_legacy.h>

#include "shiftUCN5895A.h"

#include "../../common/silec/silec.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

static Silec* silec;

I2cBusConnection* _UCN5895GetI2cBusConnection(Silec* silec) {
    I2cBusConnection* result = (I2cBusConnection*) silec->object;
    return result;
}
/** @private
 * Setup the UCN5895 
 */
void _setupUCN5895 (Silec* silec){
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _UCN5895GetI2cBusConnection(silec);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    
  
}

/**
 * @see SILEC.h
 * @private
 * Write the register of UCN5895 truth a PCF8574.
 * @param silec the silec
 * @param data data of 28 MSB bits to transfert
 */
void _writeUCN5895(Silec* silec) {
    //int FVCO_HF = 144010;
    
    int data = 0; //ENABLE->D2=0   CLK->D1=0   DATA->D0=0
    int bitToTransfert = 0;
    INT32 data32Bits = 0;

    SilecData* silecData = &(silec->silecData);
    int FVCO_HF = silecData->silecFrequency;         
       
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _UCN5895GetI2cBusConnection(silec);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterWaitSendI2C(i2cBusConnection);
    // address the register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, SHIFTUCN5895_WRITE_ADDRESS);
    WaitI2C(i2cBus); 


    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);

//Clock up
    data = data | 0x02;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);     

//Enable = 1    
    data = data | 0b00000100;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);           

    int i;
    for (i = 0; i<28; i++){

    //Clock up
        data = data | 0x02;
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);      

         bitToTransfert = data32Bits >>31;
        data32Bits = data32Bits << 1;

    //bit to  transfert
        if (bitToTransfert == 0){ 
            data = data & 0xFE;  //bit=0
        }
        else {
            data = data | 0x01;  //bit=1
        }
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);

    //Clock down
        data = data & 0xFD;
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);        
    } 

    //Enable down
    data = data & 0b11111011;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);   

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void initSHIFTUCN5895(Silec* silec, I2cBusConnection* i2cBusConnection) {
    initSilec(silec, 
            _setupUCN5895,
            _writeUCN5895,            
            (int*) i2cBusConnection);
}