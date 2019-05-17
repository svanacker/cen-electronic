#include "pathListTest.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../test/unity/unity.h"

static PathList pathList;
#define PATH_LIST_ARRAY_TEST        10
static PathData pathDataListArray[PATH_LIST_ARRAY_TEST];

// Forward Declaration
void pathListTest(void);

void pathListTestSuite(void) {
    RUN_TEST(pathListTest);
}

void pathListTest(void) {
    initPathList(&pathList, (PathData(*)[]) &pathDataListArray, PATH_LIST_ARRAY_TEST);

    Location locationA;
    Location locationB;
    Location locationC;
    Location locationD;
    Location locationE;

    PathData* pathDataAB;
    PathData* pathDataAC;
    PathData* pathDataBD;
    PathData* tmpPathData;

    initLocation(&locationA, "A", "A", 0, 0);
    initLocation(&locationB, "B", "B", 0, 0);
    initLocation(&locationC, "C", "C", 0, 0);
    initLocation(&locationD, "D", "D", 0, 0);
    initLocation(&locationE, "E", "E", 0, 0);

    pathDataAB = addPath(&pathList);
    initPathData(pathDataAB, &locationA, &locationB, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    pathDataAC = addPath(&pathList);
    initPathData(pathDataAC, &locationA, &locationC, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    pathDataBD = addPath(&pathList);
    initPathData(pathDataBD, &locationB, &locationD, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    // getPath
    tmpPathData = getPath(&pathList, 2);
    TEST_ASSERT_EQUAL(pathDataBD, tmpPathData);
    
    // getPathCount
    unsigned pathCount = getPathCount(&pathList);
    TEST_ASSERT_EQUAL(3, pathCount);

    // getPathOfLocations
    tmpPathData = getPathOfLocations(&pathList, &locationB, &locationE);
    TEST_ASSERT_EQUAL(NULL, tmpPathData);
    
    tmpPathData = getPathOfLocations(&pathList, &locationA, &locationC);
    TEST_ASSERT_EQUAL(pathDataAC, tmpPathData);
}
