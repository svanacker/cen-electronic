#include "gameStrategyDebug.h"
#include "gameStrategy.h"
#include "gameStrategyItem.h"
#include "gameTarget.h"
#include "gameTargetListDebug.h"
#include "gameTargetAction.h"
#include "gameTargetActionItem.h"
#include "gameTargetActionItemList.h"
#include "gameTargetActionList.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// TARGET COLUMNS
#define GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH                       16
#define GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH                        8
#define GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH              8
#define GAME_STRATEGY_ITEM_LIST_TARGET_OPPORTUNITY_FACTOR_COLUMN_LENGTH          8

#define GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH                     10
// ACTION COLUMNS
#define GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_START_LOCATION_NAME_COLUMN_LENGTH  8
#define GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH    8
#define GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_TIME_TO_ACHIEVE_COLUMN_LENGTH      8
// ACTION LIST ITEMS : TODO
#define GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_NAME_COLUMN_LENGTH            17
#define GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_PHASIS_COLUMN_LENGTH          8

// END
#define GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH                     0

/**
* Private.
*/
void printGameStrategyItemListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
    // Line 1
    appendStringHeader(outputStream, "name", GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "gain", GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "potent.", GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Opport.", GAME_STRATEGY_ITEM_LIST_TARGET_OPPORTUNITY_FACTOR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "status", GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Action", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_START_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Action", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Action", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_TIME_TO_ACHIEVE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Action", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Action", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_PHASIS_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);

    // Line 2
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "gain", GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Factor", GAME_STRATEGY_ITEM_LIST_TARGET_OPPORTUNITY_FACTOR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Start", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_START_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "End", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Time to", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_TIME_TO_ACHIEVE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Item", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Item", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_PHASIS_COLUMN_LENGTH);
    
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);

    // Line 3
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_OPPORTUNITY_FACTOR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_START_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Achieve", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_TIME_TO_ACHIEVE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Phasis", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_PHASIS_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

/**
* @private
*/
void printGameStrategyItemTable(OutputStream* outputStream, GameStrategyItem* strategyItem) {
	GameTarget* target = strategyItem->target;
    // TARGET
	appendStringTableData(outputStream, target->name, GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->gain, GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->potentialGain, GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->currentComputedOpportunityFactor, GAME_STRATEGY_ITEM_LIST_TARGET_OPPORTUNITY_FACTOR_COLUMN_LENGTH);
    addGameTargetStatusTableData(outputStream, target->status, GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH);
    // ACTIONS
    appendStringTableData(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_START_LOCATION_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_TIME_TO_ACHIEVE_COLUMN_LENGTH);
    // ITEMS
    appendStringTableData(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_PHASIS_COLUMN_LENGTH);

    // END
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);
}

/**
* @private
*/
void printGameTargetActionTable(OutputStream* outputStream, GameTargetAction* gameTargetAction) {
    // TARGET
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_OPPORTUNITY_FACTOR_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH);

    // ACTIONS
    appendStringTableData(outputStream, gameTargetAction->startLocation->name, GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_START_LOCATION_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, gameTargetAction->endLocation->name, GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, gameTargetAction->timeToAchieve, GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH);

    // ITEMS
    appendStringTableData(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_PHASIS_COLUMN_LENGTH);

    // END
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);
}


/**
 * @private
 * @param gameTargetList
 * @param outputStream
 */

unsigned int printActionItemPhasis(OutputStream* outputStream, enum ActionItemPhasis actionItemPhasis) {
	if (actionItemPhasis == ACTION_ITEM_PHASIS_START_LOCATION) {
		return appendString(outputStream, "START");
	}
	else if (actionItemPhasis == ACTION_ITEM_PHASIS_END_LOCATION) {
		return appendString(outputStream, "END");
	}
    else {
        return appendString(outputStream, "???");
	}
}

/**
 * @private
 * @param outputStream
 * @param actionItemPhasis
 * @param columnSize
 * @return 
 */
unsigned int addActionItemPhasis(OutputStream* outputStream, enum ActionItemPhasis actionItemPhasis, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = printActionItemPhasis(outputStream, actionItemPhasis);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

/**
* @private
*/
void printGameTargetActionItemTable(OutputStream* outputStream, GameTargetActionItem* gameTargetActionItem) {
    // TARGET
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_OPPORTUNITY_FACTOR_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH);

    // ACTIONS
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_START_LOCATION_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_END_LOCATION_NAME_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_TIME_TO_ACHIEVE_COLUMN_LENGTH);

    // ITEMS
    appendStringTableData(outputStream, gameTargetActionItem->name, GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_NAME_COLUMN_LENGTH);
    addActionItemPhasis(outputStream, gameTargetActionItem->phasis, GAME_STRATEGY_ITEM_LIST_TARGET_ACTION_ITEM_PHASIS_COLUMN_LENGTH);
            
    // END
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);
}


void printGameStrategyTable(OutputStream* outputStream, GameStrategy* gameStrategy) {
	unsigned int itemSize = gameStrategy->size;
    unsigned int i;
    unsigned int j;
    unsigned int k;
    printGameStrategyItemListHeader(outputStream);
    // Each Item
	for (i = 0; i < itemSize; i++) {
		GameStrategyItem* strategyItem = gameStrategy->items[i];
		printGameStrategyItemTable(outputStream, strategyItem);
        GameTarget* gameTarget = strategyItem->target;
        GameTargetActionList* actionList = &(gameTarget->actionList);
        unsigned int actionSize = actionList->size;
        // Each Action of Each GameStrategyItem
        for (j = 0; j < actionSize; j++) {
            GameTargetAction* targetAction = getGameTargetAction(actionList, j);
            printGameTargetActionTable(outputStream, targetAction);
            // For Each Action Item
            GameTargetActionItemList* itemList = targetAction->actionItemList;
            unsigned int actionItemSize = itemList->size;
            for (k = 0; k < actionItemSize; k++) {
                GameTargetActionItem* actionItem = getGameTargetActionItem(itemList, k);
                printGameTargetActionItemTable(outputStream, actionItem);
            }
        }
	}
    appendTableHeaderSeparatorLine(outputStream);
}
