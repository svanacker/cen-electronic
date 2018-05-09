#ifndef LAUNCHER_CLIENT_2018_H
#define LAUNCHER_CLIENT_2018_H

#include <stdbool.h>

#include "../../../common/commons.h"

bool clientGlobalTest(void);

/**
* @Client
* Set the light on for a specified direction (LEFT / RIGHT)
*/
bool clientLightOn2018(int launcherIndex);

/**
* @Client
* Launch a ball
* @param launcherIndex (LEFT / RIGHT)
*/
bool clientLaunch2018(int launcherIndex, bool prepare);

/**
* @Client
* Rotate the distributor on 1/8 until the distributor rotation is ok.
*/
bool clientDistributor2018CleanNext(int launcherIndex);

/**
* Eject the ball which is not on the right color if any
*/
bool clientDistributor2018EjectDirty(void);


#endif
