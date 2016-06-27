#ifndef MAKEIMAGEMAT_H
#define MAKEIMAGEMAT_H

#include <hdrmodule.h>
#include <matlabqt.h>

class MakeImageMat
{
public:
    MakeImageMat();
    // Fetch sample
    static m_picture *sampleSource(m_picture* src, int exposureNum , int pixelNum);
};

#endif // MAKEIMAGEMAT_H
