#include "navigationTest.h"

/**
 * Navigation Location and Path tests from book :
 * Introduction a l'algorithmique : Thomas Cormen, Charles Leiserson, Ronald Rivest
 * http://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
 * The test is not the same because graph is oriented in the book, but not in the implementation.
 */

#include "location.h"
#include "locationList.h"
#include "path.h"
#include "pathList.h"
#include "navigation.h"

#include "../common/string/cenString.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

static Location locationS;
static Location locationU;
static Location locationX;
static Location locationV;
static Location locationY;

static Path pathSU;
static Path pathUV;
static Path pathVY;
static Path pathYV;
static Path pathXY;
static Path pathXU;
static Path pathUX;
static Path pathSX;
static Path pathXV;
static Path pathYS;


static LocationList locationList;
static LocationList resultLocationList;

int addNavigationLocationsTest2() {
    // locations
    addNavigationLocation(&locationS, "S", 0, 0);
    addNavigationLocation(&locationU, "U", 0, 0);
    addNavigationLocation(&locationX, "X", 0, 0);
    addNavigationLocation(&locationV, "V", 0, 0);
    addNavigationLocation(&locationY, "Y", 0, 0);
    
    // paths
    addNavigationPath(&pathSU, "SU", &locationS, &locationU, 10, 0, 0, 0, 0, 0);
    addNavigationPath(&pathUV, "UV", &locationU, &locationV, 1, 0, 0, 0, 0, 0);
    addNavigationPath(&pathVY, "VY", &locationV, &locationY, 4, 0, 0, 0, 0, 0);
    addNavigationPath(&pathYV, "YV", &locationY, &locationV, 6, 0, 0, 0, 0, 0);
    addNavigationPath(&pathXY, "XY", &locationX, &locationY, 2, 0, 0, 0, 0, 0);
    addNavigationPath(&pathXU, "XU", &locationX, &locationU, 3, 0, 0, 0, 0, 0);
    addNavigationPath(&pathUX, "UX", &locationU, &locationX, 2, 0, 0, 0, 0, 0);
    addNavigationPath(&pathSX, "SX", &locationS, &locationX, 5, 0, 0, 0, 0, 0);
    addNavigationPath(&pathXV, "XV", &locationX, &locationV, 9, 0, 0, 0, 0, 0);
    addNavigationPath(&pathYS, "YS", &locationY, &locationS, 7, 0, 0, 0, 0, 0);

    int cost = computeBestPath(&resultLocationList, &locationS, &locationS);

    printLocationList(getInfoOutputStreamLogger(), "Result=", &resultLocationList);

    return cost;
}
