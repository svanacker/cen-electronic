#ifndef DISTRIBUTOR_DEBUG_2019_H
#define DISTRIBUTOR_DEBUG_2019_H

#include "../../common/color/color.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/colorSensor/colorSensor.h"

#include "distributor2019.h"

#include "../../robot/strategy/teamColor.h"

/**
 * Print the distributor square content
 * @param outputStream
 * @param squareContent
 */
void printDistributor2019SquareContent(OutputStream* outputStream, enum PuckPlaceHolder puckPlaceHolder);

/**
 * Print the content of the distributor 2019
 * @param outputStream
 * @param distributor
 */
void printDistributor2019(OutputStream* outputStream, BigDistributor* bigDistributor);

/**
 * Print the score linked to the distributor.
 */
void printDistributor2019Score(OutputStream* outputStream, BigDistributor* bigDistributor);

#endif
