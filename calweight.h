#ifndef CALWEIGHT_H
#define CALWEIGHT_H

class CalWeight
{
public:
    CalWeight(int zmin , int zmax);
    int getWeight(int index);
    int weight[256];
};

#endif // CALWEIGHT_H
