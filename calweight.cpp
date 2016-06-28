#include "calweight.h"

#include <iostream>

CalWeight::CalWeight(int zmin, int zmax)
{
    // Initialize the weight
    for(int i = 0 ; i < 255 ; i++){
        if(i < 0.5*(zmin+zmax)){
            weight[i] = (i-zmin)+1;
        }
        else{
            weight[i] = (zmax-i)+1;
        }
    }
}

int CalWeight::getWeight(int index)
{
    return weight[index];
}



