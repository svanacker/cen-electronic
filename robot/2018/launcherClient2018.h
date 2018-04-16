#ifndef LAUNCHER_CLIENT_2018_H
#define LAUNCHER_CLIENT_2018_H

#include <stdbool.h>

#include "../../common/commons.h"

/**
 * Ask the right launcher to send one ball and returns true if succeed.
 */
bool launchRight(int index);

/**
 * Ask the left launcher to send one ball and returns true if succeed.
 */
bool launchLeft(int index);

#endif
