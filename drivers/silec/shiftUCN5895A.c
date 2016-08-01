#include <peripheral/legacy/i2c_legacy.h>

#include "shiftUCN5895A.h"

#include "../../common/silec/silec.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

int CGRAM [96][7];

short CGROM [128][7]  = 
   {{0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //" "
    {0x0E,0x11,0x13,0x15,0x19,0x11,0x0E}, //"0"
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x1F}, //"1"
    {0x0E,0x11,0x01,0x02,0x04,0x08,0x1F}, //"2"
    {0x1F,0x02,0x04,0x02,0x01,0x11,0x0E}, //"3"
    {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02}, //"4"
    {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E}, //"5"
    {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E}, //"6"
    {0x1F,0x01,0x02,0x04,0x08,0x08,0x08}, //"7"
    {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E}, //"8"
    {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C} //"9"
    
    
    
};

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
void _writeUCN5895(Silec* silec,int row,UINT32 charLine2,UINT32 charLine1,UINT32 charLine0) {
    SilecData* silecData = &(silec->silecData);
    int data = 0 ; //   ENABLE->D2=0   CLK->D1=0   DATA->D0=0
    int bitToTransfert = 0;
    UINT32 dataLine;
    data = data + row;
           
    //CLK = 0 STROBE = 0  DATA = 0
    STROBE_UCN5895 = 0;
    SER_IN_UCN5895 = 0;
    CLOCK_UCN5895 = 0;
    
      
    
    dataLine = charLine0;
     
    //1rst bit to  transfert
    bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;
    if (bitToTransfert == 0){ 
        SER_IN_UCN5895 = 0;      
    }
    else {
        SER_IN_UCN5895 = 1;     
    }

//Clock up
    CLOCK_UCN5895 = 1;  

 
    int i;
    for (i = 0; i<32; i++){

    //Clock up
        CLOCK_UCN5895 = 1;  

        bitToTransfert = (dataLine & 0x01) ;    
        dataLine = dataLine >> 1;

    //bit to  transfert
        if (bitToTransfert == 0){ 
            SER_IN_UCN5895 = 0;   //bit=0
        }
        else {
            SER_IN_UCN5895 = 1;   //bit=1
        }
        
    //Clock down
        CLOCK_UCN5895 = 0;     
    } 

    dataLine = charLine1;
     
    //1rst bit to  transfert
    bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;
    if (bitToTransfert == 0){ 
        SER_IN_UCN5895 = 0;      
    }
    else {
        SER_IN_UCN5895 = 1;     
    }

//Clock up
    CLOCK_UCN5895 = 1;  

    for (i = 0; i<32; i++){

    //Clock up
        CLOCK_UCN5895 = 1;  

        bitToTransfert = (dataLine & 0x01) ;    
        dataLine = dataLine >> 1;

    //bit to  transfert
        if (bitToTransfert == 0){ 
            SER_IN_UCN5895 = 0;   //bit=0
        }
        else {
            SER_IN_UCN5895 = 1;   //bit=1
        }
        
    //Clock down
        CLOCK_UCN5895 = 0;     
    } 
    
    dataLine = charLine2;
     
    //1rst bit to  transfert
    bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;
    if (bitToTransfert == 0){ 
        SER_IN_UCN5895 = 0;      
    }
    else {
        SER_IN_UCN5895 = 1;     
    }

//Clock up
    CLOCK_UCN5895 = 1;  

    for (i = 0; i<32; i++){

    //Clock up
        CLOCK_UCN5895 = 1;  

        bitToTransfert = (dataLine & 0x01) ;    
        dataLine = dataLine >> 1;

    //bit to  transfert
        if (bitToTransfert == 0){ 
            SER_IN_UCN5895 = 0;   //bit=0
        }
        else {
            SER_IN_UCN5895 = 1;   //bit=1
        }
        
    //Clock down
        CLOCK_UCN5895 = 0;     
    } 
    
    
    E1_HC237 = 0;     
    delay100us(4);
 
    E1_HC237 = 1;
    //strobe up
    STROBE_UCN5895 = 1;
        //strobe down
    //STROBE_UCN5895 = 0;
    //E1_HC237 = 1;
    A0_HC237 = row & 0x01;
    A1_HC237 = (row & 0x02)>>1;
    A2_HC237 = (row & 0x04)>>2;
    
    E1_HC237 = 0;
}

void writeCharSilec(Silec* silec,int data){
    while (1){
        _writeUCN5895(silec, 0,0x0EFFFFFF,0x0EFFFFFF,0x0EFFFFFF);              
        _writeUCN5895(silec, 1,0x1135670F,0x1135670F,0x1135670F);              
        _writeUCN5895(silec, 2,0x1335670F,0x1335670F,0x1335670F);              
        _writeUCN5895(silec, 3,0x1535670F,0x1535670F,0x1535670F);              
        _writeUCN5895(silec, 4,0x1935670F,0x1935670F,0x1935670F);              
        _writeUCN5895(silec, 5,0x1135670F,0x1135670F,0x1135670F);              
        _writeUCN5895(silec, 6,0x0E35670F,0x0E35670F,0x0E35670F);
    }    
}

void initSHIFTUCN5895(Silec* silec, I2cBusConnection* i2cBusConnection) {
    initSilec(silec, 
            _setupUCN5895,
            _writeUCN5895,            
            (int*) i2cBusConnection);  
    int data = 0;
    writeCharSilec(silec,data);
}