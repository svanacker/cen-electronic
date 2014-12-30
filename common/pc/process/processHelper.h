#ifndef PROCESS_HELPER_H
#define PROCESS_HELPER_H

#include <stdbool.h>

#define HALF_SCREEN_WIDTH    684
#define CONSOLE_HEIGHT        700

/***
 * Size and move the Window Console. 
 */
void moveConsole(int left, int top, int width, int height);

/**
 * Run the process.
*/
bool runProcess(char* applicationName, char* option);

#endif
