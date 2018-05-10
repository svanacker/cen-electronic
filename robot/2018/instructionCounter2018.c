#include "instructionCounter2018.h"

#include <stdbool.h>

#include "../../common/2d/2d.h"

#include "../../client/robot/2018/launcherClient2018.h"

#include "score2018.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameTargetList.h"

void initInstructionCounter(GameStrategyContext* gameStrategyContext) {
    gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_MATCH_WAIT_FOR_START; 
}

void startInstructionCounter(GameStrategyContext* gameStrategyContext) {
     gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_MATCH_STARTED;
}

void handleObstacle(GameStrategyContext* gameStrategyContext) {
    // TODO :()
}

bool isTrajectoryReached(GameStrategyContext* gameStrategyContext, unsigned commandHeader, Point* destinationPoint) {
    
    if (commandHeader == NOTIFY_MOTION_STATUS_REACHED) {
        return true;
    }
    if (commandHeader == NOTIFY_MOTION_STATUS_FAILED
                || commandHeader == NOTIFY_MOTION_STATUS_MOVING
                || commandHeader == NOTIFY_MOTION_STATUS_OBSTACLE
                || commandHeader == NOTIFY_MOTION_STATUS_BLOCKED
                || commandHeader == NOTIFY_MOTION_STATUS_SHOCKED) {    
     
        Point* robotPosition = gameStrategyContext->robotPosition;
        float error = distanceBetweenPoints(destinationPoint, robotPosition);
        if (error < TRAJECTORY_REACHED_TRESHOLD) {
            return true;
        }
    }
    return false;
}

void handleNotificationInstructionCounter(GameStrategyContext* gameStrategyContext, unsigned commandHeader) {
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
            gameStrategyContext->score += SCORE_POINT_2018_OUTSIDE_START_AREA;
            gameStrategyContext->score += SCORE_POINT_2018_BEE_INSTALLED_POINT;
            gameStrategyContext->score += SCORE_POINT_2018_PANEL_INSTALLED_POINT;
            GameTarget* gameTarget = getGameTarget(0);
            GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), 0);
            if (doGameTargetAction(gameTargetAction, (int*)gameStrategyContext)) {
                gameStrategyContext->score += SCORE_POINT_2018_PANEL_ON_POINT;
            }
            gameStrategyContext->instructionCounter = INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_ASKED;
        }
        // SWITCH -> DISTRIBUTOR_1
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_ASKED) {
            PathList* pathList = getNavigationPathList(navigation);
            PathData* pathData = getPath(pathList, 1);
            moveAlongPath(pathData);
        }
        // DISTRIBUTOR_1 -> ACTIONS
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_REACHED) {
            GameTarget* gameTarget = getGameTarget(1);
            GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), 0);
            if (doGameTargetAction(gameTargetAction, (int*)gameStrategyContext)) {
                gameStrategyContext->score += SCORE_POINT_2018_DISTRIBUTOR_UNICOLOR_COMPLETE_POINT;
            }
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