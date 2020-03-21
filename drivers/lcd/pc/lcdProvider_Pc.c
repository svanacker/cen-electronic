/**
 * Provider of lcd interface for PC (write in Console)
 */
#include "../lcd.h"

#include <stdlib.h>
#include <stdio.h>

void setCursorAtHome(void) {
    // TODO
}

void setCursorRowAndColumn(unsigned char row, unsigned char column) {
    // TODO
}

void hideCursor(void) {
    // TODO
}

void showUnderlineCursor(void) {
    // TODO
}

void setBacklight(bool enabled) {
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

void writeLCDChar(unsigned char c) {
    putchar(c);
}

void initLCD(void) {

}