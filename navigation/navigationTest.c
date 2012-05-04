#include "navigationTest.h"

/**
 * Navigation Location and Path tests from wikipedia
 * http://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
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

static Location locationA;
static Location locationB;
static Location locationC;
static Location locationD;
static Location locationE;
static Location locationF;
static Location locationG;
static Location locationH;
static Location locationI;
static Location locationJ;

static Path pathAB;
static Path pathBF;
static Path pathFI;
static Path pathIJ;
static Path pathAC;
static Path pathCG;
static Path pathCH;
static Path pathHD;
static Path pathHJ;
static Path pathAE;
static Path pathEJ;

static LocationList locationList;
static LocationList resultLocationList;

int addNavigationLocations() {
	// locations
	addNavigationLocation(&locationA, "A", 0, 0);
	addNavigationLocation(&locationB, "B", 0, 0);
	addNavigationLocation(&locationC, "C", 0, 0);
	addNavigationLocation(&locationD, "D", 0, 0);
	addNavigationLocation(&locationE, "E", 0, 0);
	addNavigationLocation(&locationF, "F", 0, 0);
	addNavigationLocation(&locationG, "G", 0, 0);
	addNavigationLocation(&locationH, "H", 0, 0);
	addNavigationLocation(&locationI, "I", 0, 0);
	addNavigationLocation(&locationJ, "J", 0, 0);

	// paths
	addNavigationPath(&pathAB, "AB", &locationA, &locationB, 85, 0, 0, 0, 0, 0);
	addNavigationPath(&pathBF, "BF", &locationB, &locationF, 80, 0, 0, 0, 0, 0);
	addNavigationPath(&pathFI, "FI", &locationF, &locationI, 250, 0, 0, 0, 0, 0);
	addNavigationPath(&pathIJ, "IJ", &locationI, &locationJ, 84, 0, 0, 0, 0, 0);

	addNavigationPath(&pathAC, "AC", &locationA, &locationC, 217, 0, 0, 0, 0, 0);
	addNavigationPath(&pathCG, "CG", &locationC, &locationG, 186, 0, 0, 0, 0, 0);

	addNavigationPath(&pathCH, "CH", &locationC, &locationH, 103, 0, 0, 0, 0, 0);
	addNavigationPath(&pathHD, "HD", &locationH, &locationD, 183, 0, 0, 0, 0, 0);	
	addNavigationPath(&pathHJ, "HJ", &locationH, &locationJ, 167, 0, 0, 0, 0, 0);

	addNavigationPath(&pathAE, "AE", &locationA, &locationE, 173, 0, 0, 0, 0, 0);
	addNavigationPath(&pathEJ, "EJ", &locationE, &locationJ, 502, 0, 0, 0, 0, 0);

	int cost = computeBestPath(&resultLocationList, &locationA, &locationJ);

	printLocationList(getOutputStreamLogger(INFO), "Result=", &resultLocationList);

	return cost;
}
