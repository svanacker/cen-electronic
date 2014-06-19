#include <p30fxxxx.h>

#include <i2c.h>

#include "../../common/delay/delay30F.h"
#include "../../common/i2c/i2cSlaveSetup.h"
#include "../../common/pwm/pwmPic.h"
#include "../../common/serial/serial.h"
#include "../../common/serial/serialUtils.h"


_FOSC(CSW_FSCM_OFF & XT_PLL16);  //7Mhz3728 * 16  = 117,9648 MHz /4 = 29,4912 MIPS maxi pour ce pic
_FWDT(WDT_OFF);                    //Watchdog OFF
//_FBORPOR(PBOR_OFF & BORV_27 & PWRT_16 & MCLR_EN);
_FGS(CODE_PROT_OFF);            //Codeprotect OFF

volatile unsigned int interruptCount = 0;
volatile unsigned int servoValue = 1000;

#define I2C_RECEIVED_VALUES_COUNT 4

#define I2C_REGISTER_COUNT 100

/** Store the values which are received. */
unsigned char i2cCurrentReceivedValues[I2C_RECEIVED_VALUES_COUNT];
unsigned char i2cCurrentReceivedValueIndex = 0;
unsigned char i2cRegisterValues[I2C_REGISTER_COUNT];

void initI2cCurrentReceivedValues() {
    int i;
    for (i = 0; i < I2C_RECEIVED_VALUES_COUNT; i++) {
        i2cCurrentReceivedValues[i] = 0;
    }
}

void initI2cRegisterValues() {
    int i;
    for (i = 0; i < I2C_REGISTER_COUNT; i++) {
        i2cRegisterValues[i] = 0;
    }
}

int main (void) {
    initI2cCurrentReceivedValues();
    initI2cRegisterValues();
    openSerial(DEFAULT_SERIAL_SPEED);
    delaymSec(100);
    putString("Slave OK");
    println();

    i2cSlaveInit(0x40);
    while (1) {

          delaymSec(2000);
        // sendDec(servoValue);
        putString("counter=");
        sendDec(interruptCount);
        putc(';');
        int i;

        for (i = 0; i < I2C_REGISTER_COUNT; i++) {
            sendDec(i2cRegisterValues[i]);
            putc('-');
        }
        println();
    }

    return (0);
}



/*
Function Name: SI2C1Interrupt
Description : This is the ISR for I2C1 Slave interrupt.
Arguments     : None
*/
void __attribute__((__interrupt__)) __attribute__((no_auto_psv)) _SI2CInterrupt(void) {
    interruptCount++;
    

    int data = SlaveReadI2C();

    i2cRegisterValues[interruptCount] = data;

    if (data == 0x41) {
        SlaveWriteI2C(0x08);
        IFS0bits.SI2CIF = 0;
        return;
    }

    if (i2cCurrentReceivedValueIndex == 0) {
        initI2cCurrentReceivedValues();
    }
    
    i2cCurrentReceivedValues[i2cCurrentReceivedValueIndex] = data;

    i2cCurrentReceivedValueIndex++;
    if (i2cCurrentReceivedValueIndex > 2) {
        i2cCurrentReceivedValueIndex = 0;

    }

    //I2CCONbits.SCLREL = 1;

    //clear I2C1 Slave interrupt flag
    IFS0bits.SI2CIF = 0;
}    
