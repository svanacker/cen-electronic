#include <stdlib.h>

#include "gameboardElement2018.h"

#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"

// START AREA

char startAreaGreenPrint(int* element, int column, int line) {
    int xColumn = convertXToColumn(500);
    int yLine = convertYToLine(500);
    if (column == xColumn && yLine <= line) {
        return '|';
    }
    if (line == yLine && xColumn >= column) {
        return '-';
    }
    return CHAR_NO_DRAW;
}

char startAreaOrangePrint(int* element, int column, int line) {
    int xColumn = convertXToColumn(500);
    int yLine = convertYToLine(2500);
    if (column == xColumn && yLine >= line) {
        return '|';
    }
    if (line == yLine && xColumn >= column) {
        return '-';
    }
    return CHAR_NO_DRAW;
}

void addGameBoardElements2018(GameBoardElementList* gameBoardElementList) {
    addGameBoardElement(gameBoardElementList, &startAreaGreenPrint);
    addGameBoardElement(gameBoardElementList, &startAreaOrangePrint);
}
