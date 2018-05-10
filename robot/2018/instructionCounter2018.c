#include "instructionCounter2018.h"

#include <stdbool.h>

#include "../../common/2d/2d.h"

#include "../../common/delay/cenDelay.h"

#include "../../client/robot/2018/launcherClient2018.h"

#include "../../common/log/logger.h"

#include "score2018.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameTargetList.h"

#include "../../main/mainBoard/mainBoard32.h"

char* appendInstructionCounterAsString(unsigned int instructionCounter) {
    switch (instructionCounter) {
        case INSTRUCTION_COUNTER_MATCH_WAIT_FOR_START : return "WAIT_FOR_START";
        case INSTRUCTION_COUNTER_MATCH_STARTED : return "MATCH STARTED";
        case INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_REQUESTED : return "START_TO_SWITCH_MOVE_REQUESTED";
        case INSTRUCTION_COUNTER_SWITCH_REACHED : return "SWITCH_REACHED";
        case INSTRUCTION_COUNTER_SWITCH_ON : return "SWICH_ON";
        case INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_TO_REQUEST : return "SWITCH_TO_DIST_1_TO_REQUEST";
        case INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED : return "INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED";
        case INSTRUCTION_COUNTER_DIST_1_REACHED : return "DIST_1_REACHED";
        case INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_TO_REQUEST : return "DIST_1_TO_BORDER_1_TO_REQUEST";
        case INSTRUCTION_COUNTER_BORDER_1_REACHED : return "BORDER_1_REACHED";
        case INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED : return "BORDER_1_TO_BEE_ASKED";
        case INSTRUCTION_COUNTER_BEE_REACHED : return "BEE_REACHED";
    }
    return "UNKNOWN INSTRUCTION COUNTER";
}

void setNewInstructionCounter(GameStrategyContext* gameStrategyContext, unsigned int newInstructionCounter) {
    OutputStream* logOutputStream = getInfoOutputStreamLogger();
    appendString(logOutputStream, "TRANSITION:");
    char* s = appendInstructionCounterAsString(gameStrategyContext->instructionCounter);
    appendString(logOutputStream, s);
    appendString(logOutputStream, "    =>    ");
    s = appendInstructionCounterAsString(newInstructionCounter);
    appendString(logOutputStream, s);
    println(logOutputStream);

    // DO THE REAL CHANGE
    gameStrategyContext->instructionCounter = newInstructionCounter;
}

void initInstructionCounter(GameStrategyContext* gameStrategyContext) {
    setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_MATCH_WAIT_FOR_START); 
}

void startInstructionCounter(GameStrategyContext* gameStrategyContext) {
     setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_MATCH_STARTED);
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
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_REQUESTED) {
        setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_SWITCH_REACHED);
    }
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED) {
        setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_1_REACHED);
    }
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED) {
        setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BORDER_1_REACHED);
    }
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED) {
        setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BEE_REACHED);
    }
}

void handleNextInstructionCounter(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;    
    // FOR Simple HOMOLOGATION
        
    if (gameStrategyContext->strategyIndex >= STRATEGY_1_SWITCH_INDEX && gameStrategyContext->strategyIndex <= STRATEGY_3_SWITCH_DIST_BEE_INDEX) {
        // STARTED -> SWITCH
        if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_MATCH_STARTED) { 
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_REQUESTED);
            PathList* pathList = getNavigationPathList(navigation);
            PathData* pathData = getPath(pathList, 0);
            moveAlongPath(pathData);
            return;
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
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_TO_REQUEST);
            return;
        }
        
        
        
        
        // ---------------------- STRAGEGY 2 ---------------------------
        if (gameStrategyContext->strategyIndex < STRATEGY_2_SWITCH_DIST_INDEX) {
            return;
        }
        // SWITCH -> DISTRIBUTOR_1
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED);
            PathList* pathList = getNavigationPathList(navigation);
            PathData* pathData = getPath(pathList, 1);
            moveAlongPath(pathData);
            return;
        }
        
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED) {
            // WAIT FOR THE NOTIFICATION
        }
        
        // DISTRIBUTOR_1 -> ACTIONS
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_REACHED) {
            if (gameStrategyContext->color == TEAM_COLOR_ORANGE) {
                clientDistributor2018LoadAndSendUnicolorBallList(0);
            }
            else {
                clientDistributor2018LoadAndSendUnicolorBallList(1);
            }
            delaymSec(2500);
            gameStrategyContext->score += SCORE_POINT_2018_DISTRIBUTOR_UNICOLOR_COMPLETE_POINT;
            /*
            GameTarget* gameTarget = getGameTarget(1);
            GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), 0);
            if (doGameTargetAction(gameTargetAction, (int*)gameStrategyContext)) {
                gameStrategyContext->score += SCORE_POINT_2018_DISTRIBUTOR_UNICOLOR_COMPLETE_POINT;
            }
            */
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_TO_REQUEST);    
            return;
        }


        
        
        // ---------------------- STRATEGY 3 ---------------------------
        if (gameStrategyContext->strategyIndex < STRATEGY_3_SWITCH_DIST_BEE_INDEX) {
            return;
        }
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED);
            PathList* pathList = getNavigationPathList(navigation);
            PathData* pathData = getPath(pathList, 2);
            moveAlongPath(pathData);
            return;
        }
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED) {
            // wait for notification
        }
        
        // GO ON BEE
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_REACHED) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BORDER_1_TO_BEE_TO_REQUEST);
        }
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_TO_BEE_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED);
            PathList* pathList = getNavigationPathList(navigation);
            PathData* pathData = getPath(pathList, 3);
            moveAlongPath(pathData);
            return;
        }
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED) {
            // Wait
        }
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BEE_REACHED) {
            gameStrategyContext->score += SCORE_POINT_2018_BEE_DESTROYED_POINT;
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_END_MATCH);
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