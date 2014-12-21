#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include "test/main/mainBoard/mainBoardPc.h"
#include "test/main/motorBoard/motorBoardPc.h"
#include "test/allTests.h"
#include "test/main/processHelper.h"

#define PIPE_NAME	L"\\\\.\\pipe\\mainBoardPipe"

unsigned __stdcall test(void* pArguments) {
	/*
	printf("test");

	_endthreadex(0);
	*/
	return 0;
}

void printUsage(void) {
	printf("Run emulators for cen-electronic projects : \r\n");
	printf("cen-electronic-console.exe [BOARD_NAME]\r\n");

	// MainBoard
	printf("\t[BOARD_NAME]\t Select the board that you want to launch by providing name in the following list\r\n");
	printf("\t\t\t");
	printf(MAIN_BOARD_PC_NAME);
	printf(" \t : run the main Board Emulator\r\n");

	// MotorBoard
	printf("\t\t\t");
	printf(MOTOR_BOARD_PC_NAME);
	printf("\t : run the motor Board Emulator\r\n");

}

int main(int argumentCount, char* arguments[])
{
	// runAllTests();
	if (argumentCount <= 1) {
		char* applicationNameAsChar = arguments[0];

		// Run the Motor Board
		runProcess(applicationNameAsChar, MOTOR_BOARD_PC_NAME);

		// And After the main Board
		runMainBoardPC();
	}
	else {
		char* boardName = arguments[1];
		if (strcmp(boardName, MAIN_BOARD_PC_NAME) == 0) {
			runMainBoardPC();
		}
		else if (strcmp(boardName, MOTOR_BOARD_PC_NAME) == 0) {

			/*
			wchar_t buffer[128];
			DWORD numBytesRead = 0;
			BOOL result = ReadFile(
				motorBoardPipe,
				buffer, // the data from the pipe will be put here
				127 * sizeof(wchar_t), // number of bytes allocated
				&numBytesRead, // this will store number of bytes actually read
				NULL // not using overlapped IO
				);

			if (result) {
				printf("Number of bytes read: %d", numBytesRead);
			}
			else {
				printf("Failed to read data from the pipe.");
			}
			*/

			// Close our pipe handle
			// CloseHandle(motorBoardPipe);

			runMotorBoardPC();
		}
		else {
			printUsage();
			return EXIT_FAILURE;
		}
	}

	/*
	HANDLE hThread;
	unsigned threadID;
	hThread = (HANDLE)_beginthreadex(NULL, 0, &test, NULL, 0, &threadID);
	printf("main");
	*/
	
	getchar();
	return EXIT_SUCCESS;
}


