#ifndef TIME_GAIN_FACTOR_H
#define TIME_GAIN_FACTOR_H

/**
 * Returns the gain which is dependant of time.
 * 
 * @param currentMatchingTime
 *            the time between 0 and MatchData.DEFAULT_DURATION
 * @param timeToAchieveTargetAction
 * @return
 */
typedef	float getTimeGainFactorFunction(float currentMatchingTime, float remainingTime, float timeToAchieveTargetAction);

// default implementation

/**
 * Strategy which do not depends on time to achieve it except when there are not
 * time any more.
 */
float getConstantTimeGainFactor(float currentMatchingTime, float remainingTime, float timeToAchieveTargetAction);

#endif
