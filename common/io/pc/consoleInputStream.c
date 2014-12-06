#include <stdlib.h>
#include <stdio.h>

#include "consoleInputStream.h"
#include "../../../common/io/inputStream.h"

// CONSOLE INPUT STREAM
// Useful when we want to get information from console on PC

void openConsoleInputStream(InputStream* inputStream, int param1) {

}

void closeConsoleInputStream(InputStream* inputStream) {

}

char readCharConsole(InputStream* inputStream) {
    char result = (char) getchar();
    
    return result;
}

bool availableDataConsole(InputStream* inputStream) {
    bool result = (getchar() != EOF);
    return result;
}

void initConsoleInputStream(InputStream* inputStream) {
	initInputStream(inputStream, openConsoleInputStream, closeConsoleInputStream, readCharConsole, availableDataConsole, NULL);
}
