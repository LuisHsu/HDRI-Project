#ifndef CALWEIGHT_H
#define CALWEIGHT_H


class CalWeight
{
public:
    CalWeight(int zmin , int zmax);
    int *getWeight();
    int *weight;
};

#endif // CALWEIGHT_H
