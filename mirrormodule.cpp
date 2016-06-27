#include "mirrormodule.h"

MirrorModule::MirrorModule()
{

}

void MirrorModule::mod_main()
{
    m_picture *pict = pictures.at(0);
    float sumPic[pict->width][pict->height];
    for(int i=0; i<(int)pict->width; ++i){
        for(int j=0; j<(int)pict->height; ++j){
            sumPic[i][j] = 0;
        }
    }
    for(int p = 0; p<(int)pictures.size(); ++p){
        pict = pictures.at(p);
        for(int i=0; i<(int)pict->width; ++i){
            for(int j=0; j<(int)pict->height; ++j){
                sumPic[i][j] += pict->data[i][j].r;
            }
        }
    }
    pict = pictures.at(0);
    for(int i=0; i<(int)pict->width; ++i){
        for(int j=0; j<(int)pict->height; ++j){
           pict->data[i][j].r = sumPic[i][j] / pictures.size();
           sumPic[i][j] = 0;
        }
    }
    for(int p = 0; p<(int)pictures.size(); ++p){
        pict = pictures.at(p);
        for(int i=0; i<(int)pict->width; ++i){
            for(int j=0; j<(int)pict->height; ++j){
                sumPic[i][j] += pict->data[i][j].g;
            }
        }
    }
    pict = pictures.at(0);
    for(int i=0; i<(int)pict->width; ++i){
        for(int j=0; j<(int)pict->height; ++j){
           pict->data[i][j].g = sumPic[i][j] / pictures.size();
           sumPic[i][j] = 0;
        }
    }
    for(int p = 0; p<(int)pictures.size(); ++p){
        pict = pictures.at(p);
        for(int i=0; i<(int)pict->width; ++i){
            for(int j=0; j<(int)pict->height; ++j){
                sumPic[i][j] += pict->data[i][j].b;
            }
        }
    }
    pict = pictures.at(0);
    for(int i=0; i<(int)pict->width; ++i){
        for(int j=0; j<(int)pict->height; ++j){
           pict->data[i][j].b = sumPic[i][j] / pictures.size();
        }
    }
}

