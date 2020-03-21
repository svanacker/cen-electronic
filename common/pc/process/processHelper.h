#ifndef PROCESS_HELPER_H
#define PROCESS_HELPER_H

#include <stdbool.h>

// Console Width / Height in Chars
#define CONSOLE_CHARS_WIDTH 120
#define CONSOLE_CHARS_HEIGHT 100

// Console buffer width / height
#define CONSOLE_BUFFER_WIDTH CONSOLE_CHARS_WIDTH
// 20 Pages of Historic
#define CONSOLE_BUFFER_HEIGHT CONSOLE_CHARS_HEIGHT * 20

// We consider resolution is 1920x1080

// 1920 / 2
#define HALF_SCREEN_WIDTH    960

// We don't reach 1080 to have the Windows taskbar visible
#define CONSOLE_HEIGHT        1000

/***
 * Size and move the Window Console. 
 */
void moveConsole(int left, int top, int width, int height);

/**
 * Run the process.
 */
bool runProcess(char* applicationName, char* option);

/**
 * Set the size of the console in chars (width and height), and the buffer (for historic).
 */
void setConsoleSizeAndBuffer(int width, int height, int bufferWidth, int bufferHeight);

#endif
