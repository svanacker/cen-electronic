#include <p32xxxx.h>
#include <string.h>
#include <plib.h>



// definition des bits de configuration.
// Quartz externe, PLL x 10
// Watchdog OFF

#pragma config FNOSC = PRIPLL, POSCMOD = XT, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPBDIV = DIV_2, FPLLODIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN=OFF

// calcul de la fréquence du bus
#define    GetSystemClock()             (80000000ul)
#define    GetPeripheralClock()        (GetSystemClock()/(1 << OSCCONbits.PBDIV))
#define    GetInstructionClock()        (GetSystemClock())
#define I2C_CLOCK_FREQ                 (100000)

//Définition I2C

#define BRG_VAL 0xc6    //100khz

void delaymSec(unsigned int mSecond) {
    unsigned int i;
    while (mSecond != 0) {
        i = 1590;
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --mSecond;
    }
}

int main(void) {

    OpenI2C1(I2C_ON, BRG_VAL); //Enable I2C channel


    while (1) {
        StartI2C1(); //Send the Start Bit
        IdleI2C1(); //Wait to complete
        MasterWriteI2C1(0x50);
        MasterWriteI2C1('m');
        IdleI2C1();
        MasterWriteI2C1('6');
        IdleI2C1();
        MasterWriteI2C1('0');
        IdleI2C1();
        MasterWriteI2C1('6');
        IdleI2C1();
        MasterWriteI2C1('0');
        IdleI2C1();
        StopI2C1(); //Send the Stop condition
        IdleI2C1(); //Wait to complete


        delaymSec(1000);

        StartI2C1(); //Send the Start Bit
        IdleI2C1(); //Wait to complete
        MasterWriteI2C1(0x50);
        MasterWriteI2C1('n');
        IdleI2C1();
        StopI2C1(); //Send the Stop cond
        delaymSec(1000);

        StartI2C1(); //Send the Start Bit
        IdleI2C1(); //Wait to complete
        MasterWriteI2C1(0x50);
        MasterWriteI2C1('m');
        IdleI2C1();
        MasterWriteI2C1('E');
        IdleI2C1();
        MasterWriteI2C1('0');
        IdleI2C1();
        MasterWriteI2C1('E');
        IdleI2C1();
        MasterWriteI2C1('0');
        IdleI2C1();
        StopI2C1(); //Send the Stop cond
        delaymSec(1000);
    }
}