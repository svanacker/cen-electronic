#ifndef DISTRIBUTOR_DEBUG_2018_H
#define DISTRIBUTOR_DEBUG_2018_H

#include "../../common/color/color.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/colorSensor/colorSensor.h"

#include "distributor2018.h"

#include "../../robot/strategy/teamColor.h"

/**
 * Print the distributor square content
 * @param outputStream
 * @param squareContent
 */
void printDistributorSquareContent(OutputStream* outputStream, enum DistributorSquareContent squareContent);

/**
 * Print the content of the distributor
 * @param outputStream
 * @param distributor
 */
void printDistributor2018(OutputStream* outputStream, Distributor* distributor);

/**
 * Print the score linked to the distributor.
 */
void printDistributor2018Score(OutputStream* outputStream, Distributor* distributor);

#endif
