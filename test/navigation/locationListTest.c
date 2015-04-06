#include "locationListTest.h"

#include "../../navigation/locationList.h"
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

    locationA = addLocation(&locationList, "A", 20, 20);
    locationB = addLocation(&locationList, "B", 10, 30);
    locationC = addLocation(&locationList, "C", -1, 2);
    locationD = addLocation(&locationList, "D", -100, 200);
    locationE = addLocation(&locationList, "E", -10, -50);

    isEmpty = isEmptyLocationList(&locationList);
    TEST_ASSERT_FALSE(isEmpty);


    // getLocationCount
    unsigned locationCount = getLocationCount(&locationList);
    TEST_ASSERT_EQUAL(5, locationCount);

    // findLocationByName
    tmpLocation = findLocationByName(&locationList, "C");
    TEST_ASSERT_EQUAL(locationC, tmpLocation);

    // locationEquals
    bool actual = locationEquals(locationA, locationA);
    TEST_ASSERT_TRUE(actual);
    actual = locationEquals(locationA, locationC);
    TEST_ASSERT_FALSE(actual);

    // getNearestLocation
    tmpLocation = getNearestLocation(&locationList, -120, 180);
    TEST_ASSERT_EQUAL(locationD, tmpLocation);
}
