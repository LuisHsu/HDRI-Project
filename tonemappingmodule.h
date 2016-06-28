#ifndef TONEMAPPINGMODULE_H
#define TONEMAPPINGMODULE_H

#include <hdrmodule.h>
#include <vector>
#include <cmath>

class ToneMappingModule : public HDRModule
{
public:
    ToneMappingModule();
    void mod_main();
    vector<m_pixel *> ldrPic;
    unsigned int p_width,p_height;
};

#endif // TONEMAPPINGMODULE_H
