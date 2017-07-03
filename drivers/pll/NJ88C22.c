#include <peripheral/legacy/i2c_legacy.h>

#include "NJ88C22.h"

#include "../../common/pll/pll.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

static Pll* pll;

I2cBusConnection* _NJ88C22GetI2cBusConnection(Pll* pll) {
    I2cBusConnection* result = (I2cBusConnection*) pll->object;
    return result;
}
/** @private
 * Setup the NJ88C22 
 */
void _setupNJ88C22 (Pll* pll){
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _NJ88C22GetI2cBusConnection(pll);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    
  
}

/**
 * @see PLL.h
 * @private
 * Write the register of NJ88C22 truth a PCF8574.
 * @param pll the pll
 * @param data data of 28 MSB bits to transfert
 */
void _writeNJ88C22Pll(Pll* pll) {
    //int FVCO_HF = 144010;
    
    int data = 0; //ENABLE->D2=0   CLK->D1=0   DATA->D0=0
    int bitToTransfert = 0;
    INT32 data32Bits = 0;
    //UINT32 data32Bits = 0b01110000100001111001010000000000 ; //174.0000MHZ
    
    //UINT32 data32Bits = 0b01000110011011101001010000000000; //144.0000Mhz
    PllData* pllData = &(pll->pllData);
    int FVCO_HF = pllData->pllFrequency;        
            
    pllData->REGA = (FVCO_HF / FCOMP_OL1_PLL) % DIV_P;
    pllData->REGM = (FVCO_HF / FCOMP_OL1_PLL) / DIV_P ;
    pllData->REGR = FOSC_OL1_PLL / (2 * FCOMP_OL1_PLL);

    //pllData->REGA = 56;
    data32Bits = pllData->REGA;
    data32Bits = data32Bits << 10;
    data32Bits = data32Bits + pllData->REGM;
    data32Bits = data32Bits << 11;
    data32Bits = data32Bits + pllData->REGR;
    data32Bits = data32Bits << 4;
    
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _NJ88C22GetI2cBusConnection(pll);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterWaitSendI2C(i2cBusConnection);
    // address the register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, NJ88C22_WRITE_ADDRESS);
    WaitI2C(i2cBus); 

//1rst bit to  transfert
    bitToTransfert = data32Bits >>31;
    data32Bits = data32Bits << 1;
    if (bitToTransfert == 0){ 
        data = data & 0xFE;  //bit=0
    }
    else {
        data = data | 0x01;  //bit=1
    }
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

void initPllNJ88C22(Pll* pll, I2cBusConnection* i2cBusConnection) {
    initPll(pll, 
            _setupNJ88C22,
            _writeNJ88C22Pll,            
            (int*) i2cBusConnection);
}