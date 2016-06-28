#ifndef GRADIENTMODULE_H
#define GRADIENTMODULE_H

#include <hdrmodule.h>
#include <gsolver.h>
#include <calweight.h>

class GradientModule : public HDRModule
{
public:
    GradientModule();
    void mod_main();
    unsigned int p_width,p_height;
private:
    CalWeight calc;
};

#endif // GRADIENTMODULE_H
