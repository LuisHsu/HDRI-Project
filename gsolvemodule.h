#ifndef GSOLVEMODULE_H
#define GSOLVEMODULE_H

#include <hdrmodule.h>
#include <gsolver.h>
#include <cmath>

class GSolveModule : public HDRModule
{
public:
    GSolveModule();
    void mod_main();
    void sampleSource(m_picture *src, unsigned int exposureNum, unsigned int pixelNum);
    GSolver *solver;
};

#endif
