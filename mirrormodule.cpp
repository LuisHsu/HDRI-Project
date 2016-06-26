#include "mirrormodule.h"

MirrorModule::MirrorModule()
{

}

void MirrorModule::mod_main()
{
    m_picture *pict = pictures.at(0);
    for(int i=0; i<pict->width; ++i){
        for(int j=0; j<pict->height; ++j){
            pict->data[i][j].r = 255 - pict->data[i][j].r;
            pict->data[i][j].g = 255 - pict->data[i][j].g;
            pict->data[i][j].b = 255 - pict->data[i][j].b;
        }
    }
}

