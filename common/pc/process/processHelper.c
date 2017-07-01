#include "processHelper.h"

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <Wincon.h>

/**
 * Convert char array to wide char array
 * PLEASE NOTE that it's the responsibility of the caller to free the memory
 */
wchar_t* convertCharArrayToWideCharArray(char* source) {
    size_t   charCopiedCount;
    size_t originalSize = strlen(source) + 1;
    wchar_t* result = (wchar_t*)malloc(originalSize * sizeof(wchar_t));
    mbstowcs_s(&charCopiedCount, result, originalSize, source, originalSize);

    return result;
}

bool runProcess(char* applicationName, char* option) {
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    // applicationName
    char* applicationNameAsChar = applicationName;
    wchar_t* applicationNameAsWideChar = convertCharArrayToWideCharArray(applicationNameAsChar);

    // commandLine
    char commandLineAsChar[100] = " ";
    // strcat_s(commandLineAsChar, sizeof(commandLineAsChar), " ");
    strcat_s(commandLineAsChar, sizeof(commandLineAsChar), option);
    wchar_t* commandLineAsWideChar = convertCharArrayToWideCharArray(commandLineAsChar);

    if (!CreateProcess(applicationNameAsWideChar, commandLineAsWideChar, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo)) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        free(applicationNameAsWideChar);
        free(commandLineAsWideChar);
        return FALSE;
    }
    free(applicationNameAsWideChar);
    free(commandLineAsWideChar);

    return TRUE;
}
void moveConsole(int left, int top, int width, int height)
{
    HWND console = GetConsoleWindow();
    // RECT r;
    // GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, left, top, width, height, TRUE); // 800 width, 100 height
}

void setConsoleSizeAndBuffer(int width, int height, int bufferWidth, int bufferHeight) {
	COORD coord;
	HWND console = GetConsoleWindow();
	coord.X = bufferWidth;
	coord.Y = bufferHeight;

	SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}