#ifndef B_SPLINE_PERSISTENCE_H
#define B_SPLINE_PERSISTENCE_H

#include "bspline.h"
#include "../../common/eeprom/eeprom.h"

/**
 * Load the bspline from the eeprom.
 * @param curve the curve which must be filled from eeprom data
 * @param eeprom the eeprom from which we load curve data
 * @param startIndex the index in which we store the curve.
 */
void loadBSplineFromEeprom(BSplineCurve* curve, Eeprom* eeprom, unsigned long startIndex);

/**
 * Save the bspline to the eeprom.
 * @param curve the curve which must be stored into the eeprom
 * @param eeprom the eeprom in which we store curve data
 * @param startIndex the index in which the curve is stored.
 */
void saveBSplineToEeprom(BSplineCurve* curve, Eeprom* eeprom, unsigned long startIndex);

#endif

