#include <stdlib.h>

#include "strategy2012.h"

#include "../../robot/strategy/GameTarget.h"

#define COLOR_COUNT		 2

static GameTarget bullion1Target;
// static GameTargetAction[COLOR_COUNT]

/**
 * Get the way to have bullion1.
 */
GameTarget* getBullion1Target() {
	/*
	if (bullion1Target == NULL) {
			
	}
	*/
	return &bullion1Target;
}

/*
private ITargetAction[] addSymmetricTargetAction(ITarget[] targets, String start, String end, int time) {
	// red
	ITargetAction a1 = addTargetAction(targets[0], NavigationMap2012.getRedName(start), NavigationMap2012.getRedName(end),
			time);
	// violet
	ITargetAction a2 = addTargetAction(targets[1], NavigationMap2012.getVioletName(start),
			NavigationMap2012.getVioletName(end), time);
	return new ITargetAction[] { a1, a2 };
}
*/
