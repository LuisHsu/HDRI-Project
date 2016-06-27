#ifndef MIRRORMODULE_H
#define MIRRORMODULE_H

#include <hdrmodule.h>
#include <calweight.h>
#include <matlabqt.h>

class MirrorModule : public HDRModule
{
public:
    MirrorModule();
    void mod_main();
    void sampleSource(m_picture *src, unsigned int exposureNum, unsigned int pixelNum);
    int *weight_func; // For size = 256
};

#endif // MIRRORMODULE_H
