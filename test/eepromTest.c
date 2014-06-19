#include <stdio.h>

#include "eeprom.h"
#include "i2cSetup.h"
#include "lcd02.h"
#include "delay.h"

int main(void) {
    char s[80];
    
    delaymSec(1000);

    initializeI2C();
    clrScreen();

    int i=my_eeprom_read_int(4) + 1;
    my_eeprom_write_int(4, i);

    sprintf(s, "%d", i);
    affTexte(s);
    
    while (1);

    return 0;
}
