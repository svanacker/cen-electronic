#include "robotConfigPc.h"

#include "../../../common/error/error.h"

#include "../../../common/pc/file/fileUtils.h"

#include "../robotConfig.h"

#include <stdio.h>
#include <stdbool.h>

/**
 * @private
 */
unsigned int robotConfigPcReadNextBitPart(FILE * filePointer, unsigned int bitIndex) {
    char c = fgetc(filePointer);
    if (c != '0' && c != '1') {
        writeError(ROBOT_CONFIG_MUST_BE_0_OR_1_CHAR_ERROR);
        return 0;
    }
    if (c == '1') {
        return 1 << bitIndex;
    }
    return 0;
}

/**
 * @private
 */
void robotConfigPcCheckSpace(FILE * filePointer) {
    char c = fgetc(filePointer);
    if (c != ' ') {
        writeError(ROBOT_CONFIG_MUST_BE_SPACE_CHAR_ERROR);
    }
}

/**
 * Implementation of the read Function of configuration switch.
 * @see robotConfig.h
 * @private
 */
unsigned int _robotConfigPcReadInt(RobotConfig* robotConfig) {
    FILE* filePointer;

    filePointer = fopen(ROBOT_CONFIG_PC_FILE_NAME, "r");
    unsigned long fileLength = readFileLength(filePointer);

    if (fileLength != ROBOT_CONFIG_PC_FILE_LENGTH) {
        writeError(ROBOT_CONFIG_FILE_LENGTH_ERROR);
        fclose(filePointer);
        return false;
    }
    
    unsigned int result = 0;
    // HIGH BITS
    result += robotConfigPcReadNextBitPart(filePointer, 13);
    result += robotConfigPcReadNextBitPart(filePointer, 12);
    // separator
    robotConfigPcCheckSpace(filePointer);
    result += robotConfigPcReadNextBitPart(filePointer, 11);
    result += robotConfigPcReadNextBitPart(filePointer, 10);
    result += robotConfigPcReadNextBitPart(filePointer, 9);
    result += robotConfigPcReadNextBitPart(filePointer, 8);

    // HIGH / LOW Bits separator
    robotConfigPcCheckSpace(filePointer);
    robotConfigPcCheckSpace(filePointer);

    // LOW BITS
    result += robotConfigPcReadNextBitPart(filePointer, 7);
    result += robotConfigPcReadNextBitPart(filePointer, 6);
    result += robotConfigPcReadNextBitPart(filePointer, 5);
    result += robotConfigPcReadNextBitPart(filePointer, 4);
    robotConfigPcCheckSpace(filePointer);
    result += robotConfigPcReadNextBitPart(filePointer, 3);
    result += robotConfigPcReadNextBitPart(filePointer, 2);
    result += robotConfigPcReadNextBitPart(filePointer, 1);
    result += robotConfigPcReadNextBitPart(filePointer, 0);

    fclose(filePointer);

    return result;
}

/**
* Implementation of the write Function of configuration switch.
* @see robotConfig.h
* @private
*/
void _robotConfigPcWriteInt(RobotConfig* robotConfig, unsigned int value) {
    // TODO
}

void initRobotConfigPc(RobotConfig* robotConfig, enum RobotType robotType) {
    initRobotConfig(robotConfig, robotType, _robotConfigPcReadInt, _robotConfigPcWriteInt);
}
