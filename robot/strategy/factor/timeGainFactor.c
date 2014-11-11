#include "gainFactor.h"
#include "timeGainFactor.h"

float getConstantTimeGainFactor(float currentMatchingTime, float remainingTime, float timeToAchieveTargetAction) {
    if (remainingTime == 0.0f) {
        return 0.0f;
    }
    if (timeToAchieveTargetAction < remainingTime) {
        if (timeToAchieveTargetAction < 0.1f) {
            return DEFAULT_GAIN;
        }
        return 1.0 / timeToAchieveTargetAction;
    }
    // we can try it, but we discourage it
    // return Math.pow(remainingTime / timeToAchieveTargetAction, 3.0f);
    // TODO
    return 0.0f;
}
