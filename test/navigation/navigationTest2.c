#include "navigationTest2.h"

/**
 * Navigation Location and Path tests from book :
 * Introduction a l'algorithmique : Thomas Cormen, Charles Leiserson, Ronald Rivest
 * http://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
 * The test is not the same because graph is oriented in the book, but not in the implementation.
 */

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/navigation.h"

#include "../../common/string/cenString.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

static Location* locationS;
static Location* locationU;
static Location* locationX;
static Location* locationV;
static Location* locationY;

static PathData* pathSU;
static PathData* pathUV;
static PathData* pathVY;
static PathData* pathYV;
static PathData* pathXY;
static PathData* pathXU;
static PathData* pathUX;
static PathData* pathSX;
static PathData* pathXV;
static PathData* pathYS;


static LocationList locationList;
static LocationList resultLocationList;

int addNavigationLocationsTest2() {
    // locations
    locationS = addNavigationLocation("S", 0, 0);
    locationU = addNavigationLocation("U", 0, 0);
    locationX = addNavigationLocation("X", 0, 0);
    locationV = addNavigationLocation("V", 0, 0);
    locationY = addNavigationLocation("Y", 0, 0);
    
    // paths
    pathSU = addNavigationPath(locationS, locationU, 10, 0, 0, 0, 0, 0, 0);
    pathUV = addNavigationPath(locationU, locationV, 1, 0, 0, 0, 0, 0, 0);
    pathVY = addNavigationPath(locationV, locationY, 4, 0, 0, 0, 0, 0, 0);
    pathYV = addNavigationPath(locationY, locationV, 6, 0, 0, 0, 0, 0, 0);
    pathXY = addNavigationPath(locationX, locationY, 2, 0, 0, 0, 0, 0, 0);
    pathXU = addNavigationPath(locationX, locationU, 3, 0, 0, 0, 0, 0, 0);
    pathUX = addNavigationPath(locationU, locationX, 2, 0, 0, 0, 0, 0, 0);
    pathSX = addNavigationPath(locationS, locationX, 5, 0, 0, 0, 0, 0, 0);
    pathXV = addNavigationPath(locationX, locationV, 9, 0, 0, 0, 0, 0, 0);
    pathYS = addNavigationPath(locationY, locationS, 7, 0, 0, 0, 0, 0, 0);

    int cost = computeBestPath(locationS, locationS);

    printLocationList(getInfoOutputStreamLogger(), "Result=", &resultLocationList);

    return cost;
}