#include "calweight.h"

CalWeight::CalWeight(int zmin, int zmax)
{
    // Initialize the weight
    weight = new int[256];
    for(int i = 0 ; i < 255 ; i++){
        if(i < 0.5*(zmin+zmax)){
            weight[i] = (i-zmin)+1;
        }
        else{
            weight[i] = (zmax-i)+1;
        }
    }
}

int *CalWeight::getWeight()
{
    return weight;
}



