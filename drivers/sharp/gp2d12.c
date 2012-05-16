#include <math.h>


#include "gp2d12.h"

float gp2d12GetCentimerDistanceForTension(float milliVolt) {
	// This value are based on Excel logarithmique regression!
	return -40.0f * log(milliVolt) + 300.65f;
}
