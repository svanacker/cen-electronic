#ifndef GAMEBOARD_ELEMENT_LIST_H
#define GAMEBOARD_ELEMENT_LIST_H

// Forward declaration
struct GameBoardElementList;
struct GameBoardElement;
typedef struct GameBoardElementList GameBoardElementList;
typedef struct GameBoardElement GameBoardElement;

/**
* Type of function which must be called to draw an element of the gameboard.
*/
typedef char GameboardPrintFunction(int* element, int column, int line);

/**
 * Structure to store the gameboard element;
 */
struct GameBoardElement {
    /** The function which will be used to be print. */
    GameboardPrintFunction* printFunction;
};

/**
* Structure to store the list of Game Board elements which are not "targets"
*/
struct GameBoardElementList {
    /* An array of pointer on element pointer. */
    GameBoardElement (*elements)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;
};


/**
* Initializes the GameboardElement List with an array and the size of the array to avoid big and uniform
* array length.
* @param gameBoardElementListArray the array of element pointer to add.
* @param gameBoardElementListSize the size of the array of pointer to add.
*/
void initGameBoardElementList(GameBoardElementList* gameBoardElementList,
                              GameBoardElement(*gameBoardElementListArray)[],
                              unsigned char gameBoardElementListSize);

GameBoardElement* getGameBoardElement(GameBoardElementList* gameBoardElementList, unsigned int index);

/**
* Add a game board element to draw.
*/
GameBoardElement* addGameBoardElement(GameBoardElementList* gameBoardElementList, GameboardPrintFunction* gameBoardPrintFunction);

#endif

