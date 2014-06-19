#include "pcf8574Test.h"

#include "../common/delay/delay30F.h"
#include "../common/serial/serial.h"
#include "../common/serial/serialUtils.h"

#include "../device/drivers/pcf8574.h"

void pcf8574Test (void){
    char data;
    putString("PCFADD0 : ");
    data = readPCF8574 (0x40,0,0xFF);
    sendHex2(data);
    delaymSec(150);
    putString("PCFADD1 : ");
    data = readPCF8574 (0x40,1,0xFF);
    sendHex2(data);
    delaymSec(500);
}
