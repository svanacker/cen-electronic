#include <stdio.h>
#include <conio.h>

#include "../serial.h"

void openSerial(unsigned char serialPortIndex, unsigned long baudRate) {
}

void openSerialAtDefaultSpeed(unsigned char serialPortIndex) {

}

void closeSerial(unsigned char serialPortIndex) {
}

int serialKbhit(unsigned char serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        return _kbhit();
    }
    return 0;
}

char serialGetc(unsigned char serialPortIndex) {
    char result = (char) _getch();
    return result;
}

void serialPutc(unsigned char serialPortIndex, char c) {
    putchar(c);
}
