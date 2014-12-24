#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include "test/main/mainBoard/mainBoardPc.h"
#include "test/main/motorBoard/motorBoardPc.h"
#include "test/allTests.h"
#include "common/pc/process/processHelper.h"

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

	// All Tests
	printf("\t\t\t");
	printf(ALL_TESTS_NAME);
	printf("\t : run All Tests\r\n");

}

int main(int argumentCount, char* arguments[])
{
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
			runMotorBoardPC();
		}
		else if (strcmp(boardName, ALL_TESTS_NAME) == 0) {
			runAllTests();
		}
		else {
			printUsage();
			return EXIT_FAILURE;
		}
	}
	
	getchar();
	return EXIT_SUCCESS;
}


