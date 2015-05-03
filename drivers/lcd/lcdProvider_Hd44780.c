/**
 * Provider of lcd interface for lcd02
 */
#include "lcd.h"
#include "lcdHd44780.h"

/*
DeviceDescriptor getLCDDeviceDescriptor() {
        return getLCD02DeviceDescriptor();
}
 */

void setCursorAtHome(void) {
    hd44780_setCursorAtHome();
}

/*
void setCursorPosition (char position) {
        hd44780_setCursorPosition (position);
}
 */

void setCursorRowAndColumn(char row, char column) {
    hd44780_setCursorRowAndColumn(row, column);
}

void hideCursor(void) {
    hd44780_hideCursor();
}

void showUnderlineCursor(void) {
    hd44780_showUnderlineCursor();
}

void setBlinkCursor(void) {
    hd44780_setBlinkCursor();
}

/*
void backSpaceCursor (void) {
        hd44780_backSpaceCursor();
}
 */

/*
void tabCursor (void) {
        hd44780_tabCursor();
}

void smartLineCursor (void) {
        hd44780_smartLineCursor();
}

void verticalTabCursor (void) {
        hd44780_verticalTabCursor();
}
 */


void clearScreen(void) {
    hd44780_clearScreen();
}

/*
void setBacklight(unsigned char enabled) {
        hd44780_setBacklight(enabled);
}
 */

void carriageReturnCursor(void) {
    setCursorAtHome();
}

/*
void clearColumnCursor (void) {
        hd44780_clearColumnCursor();
}

void setTabulationSize (char tabulationSize) {
        hd44780_setTabulationSize(tabulationSize);
}
 */

void writeLCDChar(char c) {
    hd44780_writeChar(c);
}

/*
void sendCommand (char command) {
        hd44780_sendCommand(command);
}
 */

void initLCD(void) {
    hd44780_initLcd();
}

/*
unsigned int getLCDSoftwareRevision (void) {
        return getLCD02SoftwareRevision();
}
 */
