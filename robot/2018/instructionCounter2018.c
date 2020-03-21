#include "instructionCounter2018.h"
#include "score2018.h"
#include "distributor2018.h"

#include <stdbool.h>

#include "../../client/robot/2018/launcherClient2018.h"

#include "../../common/2d/2d.h"
#include "../../common/delay/cenDelay.h"
#include "../../common/log/logger.h"

#include "../../navigation/pathList.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameTargetList.h"

#include "../../main/mainBoard/mainBoard32.h"

char* appendInstructionCounterAsString(unsigned int instructionCounter) {
    switch (instructionCounter) {
            // MATCH
        case INSTRUCTION_COUNTER_MATCH_WAIT_FOR_START: return "WAIT_FOR_START";
            // -> SWITCH
        case INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_TO_REQUEST: return "START_TO_SWITCH_MOVE_TO_REQUEST";
        case INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_REQUESTED: return "START_TO_SWITCH_MOVE_REQUESTED";
        case INSTRUCTION_COUNTER_SWITCH_REACHED: return "SWITCH_REACHED";
            // -> DIST_1
        case INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_TO_REQUEST: return "SWITCH_TO_DIST_1_TO_REQUEST";
        case INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED: return "SWITCH_TO_DIST_1_REQUESTED";
        case INSTRUCTION_COUNTER_DIST_1_REACHED: return "DIST_1_REACHED";
            // -> BORDER_1
        case INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_TO_REQUEST: return "DIST_1_TO_BORDER_1_TO_REQUEST";
        case INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED: return "DIST_1_TO_BORDER_1_REQUESTED";
        case INSTRUCTION_COUNTER_BORDER_1_REACHED: return "BORDER_1_REACHED";
            // -> BEE
        case INSTRUCTION_COUNTER_BORDER_1_TO_BEE_TO_REQUEST: return "BORDER_1_TO_BEE_TO_REQUEST";
        case INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED: return "BORDER_1_TO_BEE_REQUESTED";
        case INSTRUCTION_COUNTER_BEE_REACHED: return "BEE_REACHED";
            // -> DIST_2_FRONT
        case INSTRUCTION_COUNTER_BEE_TO_DIST_2_FRONT_TO_REQUEST: return "BEE_TO_DIST_2_FRONT_TO_REQUEST";
        case INSTRUCTION_COUNTER_BEE_TO_DIST_2_FRONT_REQUESTED: return "BEE_TO_DIST_2_FRONT_REQUESTED";
        case INSTRUCTION_COUNTER_DIST_2_FRONT_REACHED: return "BEE_TO_DIST_2_FRONT_REACHED";
            // -> DIST_2
        case INSTRUCTION_COUNTER_DIST_2_FRONT_TO_DIST_2_TO_REQUEST: return "DIST_2_FRONT_TO_DIST_2_TO_REQUEST";
        case INSTRUCTION_COUNTER_DIST_2_FRONT_TO_DIST_2_REQUESTED: return "DIST_2_FRONT_TO_DIST_2_REQUESTED";
        case INSTRUCTION_COUNTER_DIST_2_REACHED: return "DIST_2_REACHED";
            // -> GARBAGE FRONT RELEASE
        case INSTRUCTION_COUNTER_DIST_2_TO_GARBAGE_RELEASE_FRONT_TO_REQUEST: return "DIST_2_TO_GARBAGE_RELEASE_FRONT_TO_REQUEST";
        case INSTRUCTION_COUNTER_DIST_2_TO_GARBAGE_RELEASE_FRONT_REQUESTED: return "DIST_2_TO_GARBAGE_RELEASE_FRONT_REQUESTED";
        case INSTRUCTION_COUNTER_GARBAGE_FRONT_RELEASE_REACHED: return "GARBAGE_FRONT RELEASE_REACHED";
            // -> GARBAGE RELEASE
        case INSTRUCTION_COUNTER_GARBAGE_FRONT_TO_GARBAGE_RELEASE_TO_REQUEST: return "GARBAGE_FRONT_TO_GARBAGE_RELEASE_TO_REQUEST";
        case INSTRUCTION_COUNTER_GARBAGE_FRONT_TO_GARBAGE_RELEASE_REQUESTED: return "GARBAGE_FRONT_TO_GARBAGE_RELEASE_REQUESTED";
        case INSTRUCTION_COUNTER_GARBAGE_RELEASE_REACHED: return "GARBAGE_RELEASE_REACHED";
            // GARBAGE RELEASE

        case INSTRUCTION_COUNTER_END_MATCH: return "END_MATCH";
    }
    return "UNKNOWN INSTRUCTION COUNTER";
}

/**
 * @private
 * @param gameStrategyContext
 * @param pathIndex
 * @return 
 */
PathData* getPathData(GameStrategyContext* gameStrategyContext, unsigned int pathIndex) {
    Navigation* navigation = gameStrategyContext->navigation;
    PathList* pathList = getNavigationPathList(navigation);
    PathData* pathData = getPath(pathList, pathIndex);

    return pathData;
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
    setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_TO_REQUEST);
}

void handleObstacle(GameStrategyContext* gameStrategyContext) {
    // TODO :(
}

/**
 * @private
 * @param gameStrategyContext
 * @param commandHeader
 * @param pathIndex
 * @return 
 */
bool isTrajectoryReached(GameStrategyContext* gameStrategyContext, unsigned commandHeader, unsigned int pathIndex) {

    if (commandHeader == NOTIFY_MOTION_STATUS_REACHED) {
        return true;
    }
    if (commandHeader == NOTIFY_MOTION_STATUS_FAILED
            || commandHeader == NOTIFY_MOTION_STATUS_MOVING
            || commandHeader == NOTIFY_MOTION_STATUS_OBSTACLE
            || commandHeader == NOTIFY_MOTION_STATUS_BLOCKED
            || commandHeader == NOTIFY_MOTION_STATUS_SHOCKED) {
        return false;
    }
    return false;
}

void gotoNextInstructionOrTryToFinishCurrentInstruction(GameStrategyContext* gameStrategyContext,
        unsigned char commandHeader,
        unsigned int pathIndex,
        unsigned int nextInstructionCounter) {
    if (!isTrajectoryReached(gameStrategyContext, commandHeader, pathIndex)) {
        PathData* pathData = getPathData(gameStrategyContext, pathIndex);
        if (!pathData->retried) {
            pathData->retried = true;
            delaymSec(500);
            Point* robotPosition = gameStrategyContext->robotPosition;

            restartFromPositionToGoToPath(pathData, robotPosition);
        }
    } else {
        setNewInstructionCounter(gameStrategyContext, nextInstructionCounter);
    }
}

void handleNotificationInstructionCounter(GameStrategyContext* gameStrategyContext, unsigned commandHeader) {
    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 0, INSTRUCTION_COUNTER_SWITCH_REACHED);
    }

    if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 1, INSTRUCTION_COUNTER_DIST_1_REACHED);
    } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 2, INSTRUCTION_COUNTER_BORDER_1_REACHED);
    } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 3, INSTRUCTION_COUNTER_BEE_REACHED);
    } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BEE_TO_DIST_2_FRONT_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 4, INSTRUCTION_COUNTER_DIST_2_FRONT_REACHED);
    } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_FRONT_TO_DIST_2_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 5, INSTRUCTION_COUNTER_DIST_2_REACHED);
    } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_TO_GARBAGE_RELEASE_FRONT_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 6, INSTRUCTION_COUNTER_GARBAGE_FRONT_RELEASE_REACHED);
    } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_GARBAGE_FRONT_TO_GARBAGE_RELEASE_REQUESTED) {
        gotoNextInstructionOrTryToFinishCurrentInstruction(gameStrategyContext, commandHeader, 7, INSTRUCTION_COUNTER_GARBAGE_RELEASE_REACHED);
    }
}

void handleNextInstructionCounter(GameStrategyContext* gameStrategyContext) {
    // FOR Simple HOMOLOGATION

    if (gameStrategyContext->strategyIndex >= STRATEGY_1_SWITCH_INDEX && gameStrategyContext->strategyIndex <= STRATEGY_4_SWITCH_DIST_BEE_DIST_INDEX) {
        // STARTED -> SWITCH
        if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 0);
            moveAlongPath(pathData);
            return;
        }// SWITCH -> ACTION
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_REACHED) {
            gameStrategyContext->score += SCORE_POINT_2018_OUTSIDE_START_AREA;
            gameStrategyContext->score += SCORE_POINT_2018_BEE_INSTALLED_POINT;
            gameStrategyContext->score += SCORE_POINT_2018_PANEL_INSTALLED_POINT;
            GameTarget* gameTarget = getGameTarget(0);
            GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), 0);
            if (doGameTargetAction(gameTargetAction, (int*) gameStrategyContext)) {
                gameStrategyContext->score += SCORE_POINT_2018_PANEL_ON_POINT;
            }
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_TO_REQUEST);
            return;
        }




        // ---------------------- STRAGEGY 2 ---------------------------
        if (gameStrategyContext->strategyIndex < STRATEGY_2_SWITCH_DIST_INDEX) {
            return;
        }// SWITCH -> DISTRIBUTOR_1
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 1);
            moveAlongPath(pathData);
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED) {
            // WAIT FOR THE NOTIFICATION
        }// DISTRIBUTOR_1 -> ACTIONS
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_REACHED) {
            loadUnicolorDistributorSimple(gameStrategyContext->color);
            gameStrategyContext->score += SCORE_POINT_2018_DISTRIBUTOR_UNICOLOR_6_BALLS;
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_TO_REQUEST);
            return;
        }




        // ---------------------- STRATEGY 3 ---------------------------
        if (gameStrategyContext->strategyIndex < STRATEGY_3_SWITCH_DIST_BEE_INDEX) {
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 2);
            moveAlongPath(pathData);
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED) {
            // wait for notification
        }// GO ON BEE
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_REACHED) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BORDER_1_TO_BEE_TO_REQUEST);
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_TO_BEE_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 3);
            moveAlongPath(pathData);
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED) {
            // Wait For notification
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BEE_REACHED) {
            gameStrategyContext->score += SCORE_POINT_2018_BEE_DESTROYED_POINT;
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BEE_TO_DIST_2_FRONT_TO_REQUEST);
        }

        // ---------------------- STRATEGY 4 ---------------------------
        if (gameStrategyContext->strategyIndex < STRATEGY_4_SWITCH_DIST_BEE_DIST_INDEX) {
            return;
        }// BEE -> DIST_FRONT_2
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BEE_TO_DIST_2_FRONT_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_BEE_TO_DIST_2_FRONT_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 4);
            moveAlongPath(pathData);
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_BEE_TO_DIST_2_FRONT_REQUESTED) {
            // wait for notification
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_FRONT_REACHED) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_2_FRONT_TO_DIST_2_TO_REQUEST);
        }// DIST_FRONT_2 -> DIST_2
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_FRONT_TO_DIST_2_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_2_FRONT_TO_DIST_2_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 5);
            moveAlongPath(pathData);
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_FRONT_TO_DIST_2_REQUESTED) {
            // wait for notification
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_REACHED) {
            loadMixedDistributor(gameStrategyContext->color);
            gameStrategyContext->score += SCORE_POINT_2018_DISTRIBUTOR_UNLOADED_POINT;
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_2_TO_GARBAGE_RELEASE_FRONT_TO_REQUEST);
        }// DIST_2 -> GARBAGE RELEASE FRONT
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_TO_GARBAGE_RELEASE_FRONT_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_DIST_2_TO_GARBAGE_RELEASE_FRONT_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 6);
            moveAlongPath(pathData);
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_DIST_2_TO_GARBAGE_RELEASE_FRONT_REQUESTED) {
            // wait for notification
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_GARBAGE_FRONT_RELEASE_REACHED) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_GARBAGE_FRONT_TO_GARBAGE_RELEASE_TO_REQUEST);
        }// GARBAGE RELEASE FRONT -> GARBAGE RELEASE
        else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_GARBAGE_FRONT_TO_GARBAGE_RELEASE_TO_REQUEST) {
            setNewInstructionCounter(gameStrategyContext, INSTRUCTION_COUNTER_GARBAGE_FRONT_TO_GARBAGE_RELEASE_REQUESTED);
            PathData* pathData = getPathData(gameStrategyContext, 7);
            moveAlongPath(pathData);
            return;
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_GARBAGE_FRONT_TO_GARBAGE_RELEASE_REQUESTED) {
            // wait for notification
        } else if (gameStrategyContext->instructionCounter == INSTRUCTION_COUNTER_GARBAGE_RELEASE_REACHED) {
            ejectMixedDistributor(gameStrategyContext->color);
            gameStrategyContext->score += SCORE_POINT_2018_DISTRIBUTOR_MIXEDCOLOR_BALL_COUNT * 2;
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