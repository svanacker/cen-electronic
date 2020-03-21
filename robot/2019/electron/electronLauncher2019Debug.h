#ifndef ELECTRON_LAUNCHER_DEBUG_2019_H
#define ELECTRON_LAUNCHER_DEBUG_2019_H

#include "electronLauncher2019.h"

#include "../../../common/io/outputStream.h"


unsigned int printElectronLauncherState(OutputStream* outputStream, enum ElectronLauncher2019State state);

unsigned int addLauncherStateTypeTableData(OutputStream* outputStream, enum ElectronLauncher2019State state, int columnSize);

/**
 * Debug the launcher
 */
void electronLauncher2019Debug(ElectronLauncher2019* launcher, OutputStream* outputStream);


#endif
