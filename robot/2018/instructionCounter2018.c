#include "instructionCounter2018.h"

#include "../../client/robot/2018/launcherClient2018.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameTargetList.h"

void initInstructionCounter(GameStrategyContext* gameStrategyContext) {
    gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_MATCH_WAIT_FOR_START; 
}

void startInstructionCounter(GameStrategyContext* gameStrategyContext) {
     gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_MATCH_STARTED;
}

void handleNotificationInstructionCounter(GameStrategyContext* gameStrategyContext) {
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_ASKED) {
        gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_SWITCH_REACHED;
    }
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_ASKED) {
        gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_DIST_1_REACHED;
    }
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_ASKED) {
        gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_BORDER_1_REACHED;
    }
}

void handleNextInstructionCounter(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;    
    // FOR Simple HOMOLOGATION
        
    if (gameStrategyContext->strategyIndex >= STRATEGY_1_SWITCH_INDEX && gameStrategyContext->strategyIndex <= STRATEGY_3_SWITCH_DIST_BEE_INDEX) {
        // STARTED -> SWITCH
        if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_MATCH_STARTED) { 
            gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_ASKED;
            PathList* pathList = getNavigationPathList(navigation);
            PathData* pathData = getPath(pathList, 0);
            moveAlongPath(pathData);
        }
        // SWITCH -> ACTION
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_REACHED) {
            GameTarget* gameTarget = getGameTarget(0);
            GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), 0);
            doGameTargetAction(gameTargetAction, (int*)gameStrategyContext);
            gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_ASKED;
        }
        // SWITCH -> DISTRIBUTOR_1
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_ASKED) {
            PathList* pathList = getNavigationPathList(navigation);
            PathData* pathData = getPath(pathList, 1);
            moveAlongPath(pathData);
        }
        // DISTRIBUTOR_1 -> ACTOINS
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_REACHED) {
            GameTarget* gameTarget = getGameTarget(1);
            GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), 0);
            doGameTargetAction(gameTargetAction, (int*)gameStrategyContext);
            gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_ASKED;            
        }
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_ASKED) {
            // gameStrategyContext->instructionCounter++;
            // TODO : Add A game Target !!
            /*
            GameTarget* gameTarget = getGameTarget(2);
            GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), 0);
            doGameTargetAction(gameTargetAction, (int*)gameStrategyContext);
            */
        }
    }
    // For Simple CHECK
    if (gameStrategyContext->strategyIndex == STRATEGY_7_CHECK_IF_ROBOT_OK) {
        if (gameStrategyContext->instructionCounter == 1) {
            // To avoid that we repeat the test
            gameStrategyContext->instructionCounter++;
            clientGlobalTest();
        }
    }
}