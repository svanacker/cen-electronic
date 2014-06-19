/**
* Provider of lcf interface for lcd02
*/
#include "../../device/drivers/lcd.h"
#include "../../device/drivers/lcd02.h"

DeviceDescriptor getLCDDeviceDescriptor() {
    return getLCD02DeviceDescriptor();
}

void setCursorAtHome(void) {
    lcd02_setCursorAtHome();
}

void setCursorPosition (char position) {
    lcd02_setCursorPosition (position);
}

void setCursorRowAndColumn(char row, char column) {
    lcd02_setCursorRowAndColumn(row, column);
}

void hideCursor (void) {
    lcd02_hideCursor();
}

void showUnderlineCursor (void) {
    lcd02_showUnderlineCursor();
}

void setBlinkCursor(void) {
    lcd02_setBlinkCursor();
}

void backSpaceCursor (void) {
    lcd02_backSpaceCursor();
}

void tabCursor (void) {
    lcd02_tabCursor();
}

void smartLineCursor (void) {
    lcd02_smartLineCursor();
}

void verticalTabCursor (void) {
    lcd02_verticalTabCursor();
}

void clearScreen (void) {
    lcd02_clearScreen();
}

void setBacklight(unsigned char enabled) {
    lcd02_setBacklight(enabled);
}

void carriageReturnCursor (void) {
    lcd02_carriageReturnCursor();
}

void clearColumnCursor (void) {
    lcd02_clearColumnCursor();
}

void setTabulationSize (char tabulationSize) {
    lcd02_setTabulationSize(tabulationSize);
}

void writeChar (char c) {
    lcd02_writeChar(c);
}

void sendCommand (char command) {
    lcd02_sendCommand(command);
}

void initLCD ( void ) {
    initLCD02();
}

unsigned int getLCDSoftwareRevision (void) {
    return getLCD02SoftwareRevision();
}
