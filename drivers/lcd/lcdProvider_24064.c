#include "lcd24064.h"

#include "lcdProvider_24064.h"

void clearScreen(void) {
    clearScreen_24064();
}

void setCursorAtHome(void) {
    setCursorAtHome_24064();
}

void hideCursor(void) {
    hideCursor_24064();
}

void showUnderlineCursor(void) {
    showUnderlineCursor_24064();
}

void setCursorPosition (int row, int col){
    setCursorPosition_24064 (row, col);
}

void setPixel(int x,int y){
    setPixel_24064(x,y);
}

void line(int x1,int y1,int x2,int y2){
    line_24064(x1, y1, x2, y2);
}

void initLcd (void){
    InitLCD_24064;
}