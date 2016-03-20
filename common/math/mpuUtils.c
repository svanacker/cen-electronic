#include <math.h>

#include "mpuUtils.h"



//Fonction de convertion
float convertRadiansToDegre(float angleDegre)
      {
         return (angleDegre*180)/M_PI;
      }


float dist(int a,int b){
    return sqrt((a*a)+(b*b));
}

void getXRotation (Mpu* mpu){
    
    // init pointer
    MpuData* mpuData = &(mpu->mpuData);
    
   
    float radians = atan2(mpuData->accel_Y, dist(mpuData->accel_X,mpuData->accel_Z));
    
    
    mpuData->pitch = convertRadiansToDegre(radians);
}
