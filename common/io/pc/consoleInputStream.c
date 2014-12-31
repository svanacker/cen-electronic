#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "consoleInputStream.h"

#include "../../../common/io/inputStream.h"

// CONSOLE INPUT STREAM
// Useful when we want to get information from console on PC

void openConsoleInputStream(InputStream* inputStream, int param1) {

}

void closeConsoleInputStream(InputStream* inputStream) {

}

char readCharConsole(InputStream* inputStream) {
    char result = (char) _getch();
    
    return result;
}

bool availableDataConsole(InputStream* inputStream) {
    bool result = _kbhit();
    return result;
}

void initConsoleInputStream(InputStream* inputStream) {
    initInputStream(inputStream, openConsoleInputStream, closeConsoleInputStream, readCharConsole, availableDataConsole, NULL);
}
