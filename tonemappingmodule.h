#ifndef TONEMAPPINGMODULE_H
#define TONEMAPPINGMODULE_H

#include <hdrmodule.h>
#include <vector>
#include <cmath>
#include <QImage>
#include <string>

class ToneMappingModule : public HDRModule
{
public:
    ToneMappingModule();
    void mod_main();
    vector<m_pixel *> ldrPic;
    std::string outFilename;
    unsigned int p_width,p_height;
};

#endif // TONEMAPPINGMODULE_H
