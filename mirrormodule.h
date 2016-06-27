#ifndef MIRRORMODULE_H
#define MIRRORMODULE_H

#include <hdrmodule.h>
#include <calweight.h>

class MirrorModule : public HDRModule
{
public:
    MirrorModule();
    void mod_main();
    int *weight_func; // For size = 256
};

#endif // MIRRORMODULE_H
