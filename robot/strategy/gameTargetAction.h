#ifndef GAME_TARGET_ACTION_H
#define GAME_TARGET_ACTION_H

#include "gameTargetActionItemList.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../navigation/location.h"

/**
* Type of Action (Inheritance management to have 2 types of Actions
*/
enum ActionType {
    // The action status is UNDEFINED,
    ACTION_TYPE_UNDEFINED = 0,
    // The action is a MOVE, in this case, we must specify a start and an end Location
    ACTION_TYPE_MOVE = 1,
    // The action is an action of preparation of an action of Handling (to earn time)
    ACTION_TYPE_PREPARE = 2,
    // The action is an action of handling an object (but it does not provide some points)
    ACTION_TYPE_TAKE = 3,
    // The action is often an action of release or dropping and object, which becomes the real target
    ACTION_TYPE_DROP = 4
};

/**
 * Define if the action was done or not.
 */
enum ActionStatus {
    // The action status is UNKNOWN,
    ACTION_STATUS_UNDEFINED = 0,
    // The action is TODO
    ACTION_STATUS_TODO = 1,
    // The action is on goind
    ACTION_STATUS_DOING = 2,
    // The action was done (go on the location && actionItems done)
    ACTION_STATUS_DONE = 3,
    // The action is on error
    ACTION_STATUS_ERROR = 4
};

/**
* Define the priority of the actions !
*/
#define ACTION_PRIORITY_HIGHEST             100
#define ACTION_PRIORITY_NORMAL              50
#define ACTION_PRIORITY_LOWEST               0

#define ACTION_PRIORITY_DROP_STANDARD        ACTION_PRIORITY_LOWEST
#define ACTION_PRIORITY_TAKE_STANDARD        ACTION_PRIORITY_NORMAL
#define ACTION_PRIORITY_PREPARE_STANDARD     ACTION_PRIORITY_HIGHEST

/**
 * Encapsulates the target action.
 */
typedef struct GameTargetAction {
    // Returns the first point which is needed to do the target Action
    Location* startLocation;
    // Returns the location of the target Action.
    Location* endLocation;
    // Time to achieve (in second) all Actions (excluding time to move)
    float timeToAchieve;
    // type
    enum ActionType type;
    // Status
    enum ActionStatus status;
    // Reference to GameTargetActionListItem, can be NULL
    GameTargetActionItemList* actionItemList;
    // Priority (from 0 = lowPriority, n = high Priority)
    unsigned int priority;
} GameTargetAction;

/**
 * Initializes the structure.
 */
void initGameTargetAction(GameTargetAction* targetAction, 
                          Location* startLocation,
                          Location* endLocation,
                          enum ActionType actionType,
                          float timeToAchieve,
                          unsigned int priority,
                          GameTargetActionItemList* actionItemList);

/**
* Clear the targetAction and the items if any.
*/
void clearTargetAction(GameTargetAction* targetAction);

/**
 * Determines if the targetAction needs that the robot moves.
 */
bool targetActionNeedsMove(GameTargetAction* targetAction);

/**
 * Used for test but not in real situation, just to debug if action could be done easily
 * @return true if all items were done successfully, false if there at least one problem
 */
bool doGameTargetAction(GameTargetAction* targetAction, int* context);

#endif
