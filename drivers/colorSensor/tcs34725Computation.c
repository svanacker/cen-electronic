#include "tcs34725Computation.h"

#include <stdint.h>
#include <math.h>

/**
 * @private 
 * Implements missing powf function.
 */
float powf(const float x, const float y) {
    return (float) (pow((double) x, (double) y));
}

/**
 * Converts the raw R/G/B values to lux
 */
uint16_t tcs34725_calculateLux(uint16_t r, uint16_t g, uint16_t b) {
    float illuminance;

    /* This only uses RGB ... how can we integrate clear or calculate lux */
    /* based exclusively on clear since this might be more reliable?      */
    illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

    return (uint16_t) illuminance;
}

/**
 *Converts the raw R/G/B values to color temperature in degrees Kelvin
 */
uint16_t tcs34725_calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b) {
    float X, Y, Z; /* RGB to XYZ correlation      */
    float xc, yc; /* Chromaticity co-ordinates   */
    float n; /* McCamy's formula            */
    float cct;

    /* 1. Map RGB values to their XYZ counterparts.    */
    /* Based on 6500K fluorescent, 3000K fluorescent   */
    /* and 60W incandescent values for a wide range.   */
    /* Note: Y = Illuminance or lux                    */
    X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
    Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
    Z = (-0.68202F * r) + (0.77073F * g) + (0.56332F * b);

    /* 2. Calculate the chromaticity co-ordinates      */
    xc = (X) / (X + Y + Z);
    yc = (Y) / (X + Y + Z);

    /* 3. Use McCamy's formula to determine the CCT    */
    n = (xc - 0.3320F) / (0.1858F - yc);

    /* Calculate the final CCT */
    cct = (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;

    /* Return the results in degrees Kelvin */
    return (uint16_t) cct;
}

