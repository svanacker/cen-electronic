#include <stdio.h>

#include "i2cSetup.h"
#include "lcd02.h"
#include "delay.h"
#include "coders.h"

int main(void) {
    initializeI2C();
    affTexte("Test LCD\n");

    initCoders();
    setupInterrupt();

    unsigned int count = 0;
    char s[20];
    while (1) {
        count++;
        if ((count % 60000) == 0) {
            clrScreen();
            int i;
            for (i=0; i<2; i++) {
                long coder = getCoderValue(i);
                sprintf(s, "%x_", (int)(coder >> 16));
                affTexte(s);
                sprintf(s, "%x", (int)(coder & 0xFFFF));
                affTexte(s);
                carRetCur();
            }
            count = 0;
        }
    }

    return 0;
}
