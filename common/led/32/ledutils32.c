#include <p32xxxx.h>
#include <peripheral/ports.h>
#include <stdbool.h>

#include "../ledutils.h"
#include "../../io/pin.h"

int ledstate;

void _initLed(){
    led1_dir = 0;
    led2_dir = 0;    
    ledstate = 0;
}

void setLedValue (char index,char state){
    _initLed();

    switch(index) {
        case 1 : {led1 = state;break;}
        case 2 : {led2 = state;break;}
    }
}

void testLedMainBoard (void){
    _initLed();
    char i;
    for (i=0;i<10;i++){
        led1 = !led1;
        led2 = !led2;
        delaymSec(300);
    }
    led1 = 1;
}
