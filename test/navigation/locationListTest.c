#include "locationListTest.h"

#include "../../navigation/locationList.h"
#include "../../navigation/locationListComputer.h"
#include "../../navigation/location.h"

#include "../../test/unity/unity.h"

static LocationList locationList;
#define LOCATION_LIST_ARRAY_TEST        10
static Location locationListArray[LOCATION_LIST_ARRAY_TEST];

// Forward Declaration
void locationListTest(void);

void locationListTestSuite(void) {
    RUN_TEST(locationListTest);
}

void locationListTest(void) {
    initLocationList(&locationList, (Location(*)[]) &locationListArray, LOCATION_LIST_ARRAY_TEST);

    Location* locationA;
    Location* locationB;
    Location* locationC;
    Location* locationD;
    Location* locationE;
    Location* tmpLocation;
    // Location* tmpLocation2;

    // Emtpy Test
    bool isEmpty = isEmptyLocationList(&locationList);
    TEST_ASSERT_TRUE(isEmpty);

    locationA = addNamedLocation(&locationList, "A", "A", 20, 20);
    locationB = addNamedLocation(&locationList, "B", "B", 10, 30);
    locationC = addNamedLocation(&locationList, "C", "C", -1, 2);
    locationD = addNamedLocation(&locationList, "D", "D", -100, 200);
    locationE = addNamedLocation(&locationList, "E", "E", -10, -50);

    isEmpty = isEmptyLocationList(&locationList);
    TEST_ASSERT_FALSE(isEmpty);


    // getLocationCount
    unsigned locationCount = getLocationCount(&locationList);
    TEST_ASSERT_EQUAL(5, locationCount);

    // findLocationByName
    tmpLocation = findLocationByStringName(&locationList, "C");
    TEST_ASSERT_EQUAL(locationC, tmpLocation);

    // locationEquals
    bool actual = locationEquals(locationA, locationA);
    TEST_ASSERT_TRUE(actual);
    actual = locationEquals(locationA, locationC);
    TEST_ASSERT_FALSE(actual);

    // getNearestLocation
    tmpLocation = getNearestLocation(&locationList, -120.0f, 180.0f, 100.0f);
    TEST_ASSERT_EQUAL(locationD, tmpLocation);
}
