#include <peripheral/legacy/i2c_legacy.h>

#include "shiftUCN5895A.h"

#include "../../common/silec/silec.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

short tableCaracteree[3][7]  = 
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00},//" "
    {0x0E,0x11,0x13,0x15,0x19,0x11,0x0E},  //"0"
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x1F}  //"1"
    
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


void write74HC233(Silec* silec, int datas, int row){
    
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _UCN5895GetI2cBusConnection(silec);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    
    int data = 0 ;
    data = row << 4;
    
    portableMasterWaitSendI2C(i2cBusConnection);
    // address the register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, SHIFTUCN5895_WRITE_ADDRESS);
    WaitI2C(i2cBus); 

    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);
    
    data = data | 0x08;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);
    
    //data = data & 0xF7;
    //portableMasterWriteI2C(i2cBusConnection, data);
    //WaitI2C(i2cBus);
    
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
        
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
    row = row << 4;
    row = row + 0x08;
    data = data + row;
           
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _UCN5895GetI2cBusConnection(silec);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    
    portableMasterWaitSendI2C(i2cBusConnection);
    // address the register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, SHIFTUCN5895_WRITE_ADDRESS);
    WaitI2C(i2cBus); 

    //portableMasterWriteI2C(i2cBusConnection, data);
    //WaitI2C(i2cBus);
    
    //CLK = 0 STROBE = 0  DATA = 0
    data = data & 0xF8;
    
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus); 
    
    dataLine = charLine0;
     
    //1rst bit to  transfert
    bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;
    if (bitToTransfert == 0){ 
        data = data & 0xFB;  //bit=0        
    }
    else {
        data = data | 0x04;  //bit=1       
    }
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);

//Clock up
    data = data | 0x02;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);   

         

    int i;
    for (i = 0; i<32; i++){

    //Clock up
        data = data | 0x02;        
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);      

        bitToTransfert = (dataLine & 0x01) ;    
        dataLine = dataLine >> 1;

    //bit to  transfert
        if (bitToTransfert == 0){ 
            data = data & 0xFB;  //bit=0
        }
        else {
            data = data | 0x04;  //bit=1
        }
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);

    //Clock down
        data = data & 0xFD;
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);        
    } 
    
    
    
    dataLine = charLine1;
     
    //1rst bit to  transfert
    bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;
    if (bitToTransfert == 0){ 
        data = data & 0xFB;  //bit=0
    }
    else {
        data = data | 0x04;  //bit=1
    }
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);

//Clock up
    data = data | 0x02;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);     


    for (i = 0; i<32; i++){

    //Clock up
        data = data | 0x02;
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);      

        bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;

    //bit to  transfert
        if (bitToTransfert == 0){ 
            data = data & 0xFB;  //bit=0
        }
        else {
            data = data | 0x04;  //bit=1
        }
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);

    //Clock down
        data = data & 0xFD;
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);        
    } 
    
    dataLine = charLine2;
     
    //1rst bit to  transfert
    bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;
    if (bitToTransfert == 0){ 
        data = data & 0xFB;  //bit=0
    }
    else {
        data = data | 0x04;  //bit=1
    }
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);

//Clock up
    data = data | 0x02;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);     


    for (i = 0; i<32; i++){

    //Clock up
        data = data | 0x02;
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);      

        bitToTransfert = (dataLine & 0x01) ;    
    dataLine = dataLine >> 1;

    //bit to  transfert
        if (bitToTransfert == 0){ 
            data = data & 0xFB;  //bit=0
        }
        else {
            data = data | 0x04;  //bit=1
        }
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);

    //Clock down
        data = data & 0xFD;
        portableMasterWriteI2C(i2cBusConnection, data);
        WaitI2C(i2cBus);        
    } 

    //strobe up
    data = data | 0x01;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);   
    
    //strobe down
    data = data & 0xFE;
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
}

void writeCharSilec(Silec* silec,int data){
    while (1){
        _writeUCN5895(silec, 0,0x0EFFFFFF,0xFFFFFFFF,0xFFFFFFFF);              
        write74HC233(silec , data ,0);
        _writeUCN5895(silec, 0,0x1135670F,0x89ABCDEF,0x34567F0F);              
        write74HC233(silec , data ,1);
        _writeUCN5895(silec, 0,0x1335670F,0x89ABCDEF,0x34567F0F);              
        write74HC233(silec , data ,2);
        _writeUCN5895(silec, 0,0x1535670F,0x89ABCDEF,0x34567F0F);              
        write74HC233(silec , data ,3);
        _writeUCN5895(silec, 0,0x1935670F,0x89ABCDEF,0x34567F0F);              
        write74HC233(silec , data ,4);
        _writeUCN5895(silec, 0,0x1135670F,0x89ABCDEF,0x34567F0F);              
        write74HC233(silec , data ,5);
        _writeUCN5895(silec, 0,0x0E35670F,0x89ABCDEF,0x34567F0F);              
        write74HC233(silec , data ,6);
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