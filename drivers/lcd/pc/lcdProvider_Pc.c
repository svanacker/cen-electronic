/**
 * Provider of lcd interface for PC (write in Console)
 */
#include "../lcd.h"

#include <stdlib.h>
#include <stdio.h>

void setCursorAtHome(void) {
    // TODO
}

void setCursorRowAndColumn(char row, char column) {
    // TODO
}

void hideCursor(void) {
    // TODO
}

void showUnderlineCursor(void) {
    // TODO
}

void setBlinkCursor(void) {
    // TODO
}

void clearScreen(void) {
    // TODO : Provide a better implementation
    putchar('C');
    putchar('L');
    putchar('S');
    putchar('\n');
}


void carriageReturnCursor(void) {
    setCursorAtHome();
}

void writeLCDChar(char c) {
    putchar(c);
}

void initLCD(void) {

}