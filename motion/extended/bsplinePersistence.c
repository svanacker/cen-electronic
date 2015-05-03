#include "bsplinePersistence.h"

#define POINT_PERSISTENCE_SIZE_BLOCK        5
#define BSPLINE_PERSISTENCE_SIZE_BLOCK      20

/**
 * Load a point from the eeprom.
 * @private
 */
void loadPointFromEeprom(Point* point, Eeprom* eeprom, unsigned long startIndex) {
    float x = (float) eepromReadInt(eeprom, startIndex);
    float y = (float) eepromReadInt(eeprom, startIndex + 2);
    
    point->x = x;
    point->y = y;
}

void loadBSplineFromEeprom(BSplineCurve* curve, Eeprom* eeprom, unsigned long startIndex) {
    loadPointFromEeprom(&(curve->p0), eeprom, startIndex);
    loadPointFromEeprom(&(curve->p1), eeprom, startIndex + POINT_PERSISTENCE_SIZE_BLOCK);
    loadPointFromEeprom(&(curve->p2), eeprom, startIndex + POINT_PERSISTENCE_SIZE_BLOCK * 2);
    loadPointFromEeprom(&(curve->p3), eeprom, startIndex + POINT_PERSISTENCE_SIZE_BLOCK * 3);
}

/**
 * Save a point to the eeprom.
 * @private
 */
void savePointFromEeprom(Point* point, Eeprom* eeprom, unsigned long startIndex) {
    eepromWriteInt(eeprom, startIndex, (int) point->x);
    eepromWriteInt(eeprom, startIndex + 2, (int) point->y);
}

void saveBSplineToEeprom(BSplineCurve* curve, Eeprom* eeprom, unsigned long startIndex) {
    savePointFromEeprom(&(curve->p0), eeprom, startIndex);
    savePointFromEeprom(&(curve->p1), eeprom, startIndex + POINT_PERSISTENCE_SIZE_BLOCK);
    savePointFromEeprom(&(curve->p2), eeprom, startIndex + POINT_PERSISTENCE_SIZE_BLOCK * 2);
    savePointFromEeprom(&(curve->p3), eeprom, startIndex + POINT_PERSISTENCE_SIZE_BLOCK * 3);
}
