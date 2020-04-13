#ifndef LIGHT_HOUSE_2020_WORKFLOW_H
#define LIGHT_HOUSE_2020_WORKFLOW_H

#include "lightHouse2020.h"

void updateLightHouseState(LightHouse2020* lightHouse, enum LightHouse2020State newState);

// MAIN METHOD (WORKFLOW)

void handleLightHouseActions(LightHouse2020* lightHouse);

// RESET
void lightHouse2020ResetWorkflow(LightHouse2020* lightHouse);

#endif
