#include "motionEndInfo.h"

void resetMotionEndInfo(MotionEndInfo* endMotion) {
    endMotion->integralTime = 0;
    endMotion->index = 0;
    int i;
    for (i = 0; i < MAX_HISTORY_COUNT; i++) {
        endMotion->absDeltaPositionIntegralHistory[i] = 0;
        endMotion->absUIntegralHistory[i] = 0;
    }
    endMotion->absDeltaPositionIntegral = 0;
    endMotion->absUIntegral = 0;
}