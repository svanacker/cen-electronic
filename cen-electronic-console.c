#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include "main/mainBoard/mainBoardPc.h"
#include "main/motorBoard/motorBoardPc.h"
#include "test/allTests.h"
#include "common/pc/process/processHelper.h"

void printUsage(void) {
    printf("ROBOT EMULATOR for cen-electronic projects : \r\n");
    printf("cen-electronic-console.exe [BOARD_NAME] [OPTION]\r\n");

    // MainBoard
    printf("\t[BOARD_NAME]\t Select the board that you want to launch by providing name in the following list\r\n");
    printf("\t\t\t");
    printf(MAIN_BOARD_PC_NAME);
    printf(" \t : run the main Board Emulator\r\n");
    printf("\t\t\t\t [OPTION] robotManager : launch the mainBoard with a connection to RobotManager\r\n");

    // MotorBoard
    printf("\t\t\t");
    printf(MOTOR_BOARD_PC_NAME);
    printf("\t : run the motor Board Emulator\r\n");
    printf("\t\t\t\t [OPTION] single : just launch motorBoard without initializing I2C to connect it to a master\r\n");

    // All Tests
    printf("\t\t\t");
    printf(ALL_TESTS_NAME);
    printf("\t : run All Tests\r\n");

}

int main(int argumentCount, char* arguments[])
{
    char* applicationNameAsChar = arguments[0];

    if (argumentCount <= 1) {

        // Run the Motor Board
        char motorBoardOptionCommand[255];
        strcpy_s(motorBoardOptionCommand, _countof(motorBoardOptionCommand), MOTOR_BOARD_PC_NAME);
        strcat_s(motorBoardOptionCommand, _countof(motorBoardOptionCommand), " ");
        strcat_s(motorBoardOptionCommand, _countof(motorBoardOptionCommand), MOTOR_BOARD_PC_RUN_STANDARD);
        runProcess(applicationNameAsChar, motorBoardOptionCommand);

        // And After the main Board
        runMainBoardPC(false);
    }
    else {
        char* boardName = arguments[1];
        if (strcmp(boardName, MAIN_BOARD_PC_NAME) == 0) {
            bool robotManager = false;
            if (argumentCount > 2) {
                char* mainBoardRunMode = arguments[2];
                robotManager = (strcmp(mainBoardRunMode, MAIN_BOARD_PC_ROBOT_MANAGER) == 0);

                char motorBoardOptionCommand[255];
                strcpy_s(motorBoardOptionCommand, _countof(motorBoardOptionCommand), MOTOR_BOARD_PC_NAME);
                strcat_s(motorBoardOptionCommand, _countof(motorBoardOptionCommand), " ");
                strcat_s(motorBoardOptionCommand, _countof(motorBoardOptionCommand), MOTOR_BOARD_PC_RUN_STANDARD);
                runProcess(applicationNameAsChar, motorBoardOptionCommand);
            }
            // In all cases
            runMainBoardPC(robotManager);
        }
        else if (strcmp(boardName, MOTOR_BOARD_PC_NAME) == 0) {
            bool singleMode = true;
            if (argumentCount > 2) {
                char* motorBoardRunMode = arguments[2];
                singleMode = (strcmp(boardName, MOTOR_BOARD_PC_RUN_SINGLE) == 0);
            }
            runMotorBoardPC(singleMode);
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


