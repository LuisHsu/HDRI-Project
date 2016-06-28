#include "tonemappingmodule.h"

ToneMappingModule::ToneMappingModule()
{

}

void ToneMappingModule::mod_main()
{
    p_width = pictures.at(0)->width;
    p_height = pictures.at(0)->height;
    for(unsigned int i=0; i<pictures.size(); ++i){
        for(unsigned int j=0; j<p_width; ++j){
            delete [] pictures.at(i)->data[j];
        }
        delete [] pictures.at(i)->data;
    }
    float luminanceMap[p_width][p_height];
    float scaled_luminanceMap[p_width][p_height];
    float ldr_luminanceMap[p_width][p_height];
    // Init
    for(unsigned int i = 0; i < p_width ; i++){
        for(unsigned int j = 0; j < p_height ; j++){
            luminanceMap[i][j] = 0.0;
            scaled_luminanceMap[i][j] = 0.0;
            ldr_luminanceMap[i][j] = 0.0;
        }
        ldrPic.push_back (new m_pixel[p_height]);
    }


    float delta = 0.0001;
    float sum = 0;
    float key = exp((1.0/p_width*p_height)*sum);
    float a = 0.72, saturation = 0.6;
    for(unsigned int i = 0 ; i < p_width ; i++){
        for(unsigned int j = 0 ; j < p_height ; j++){
            luminanceMap[i][j] = 0.2125*HDR[i][j].r + 0.7154*HDR[i][j].g + 0.0721*HDR[i][j].b;
            sum += log(luminanceMap[i][j]+delta);
            scaled_luminanceMap[i][j] = luminanceMap[i][j] * (a/key);
            ldr_luminanceMap[i][j] = scaled_luminanceMap[i][j] / (scaled_luminanceMap[i][j] + 1);
            ldrPic[i][j].r = (pow((HDR[i][j].r / luminanceMap[i][j]), saturation)) * ldr_luminanceMap[i][j];
            ldrPic[i][j].g = (pow((HDR[i][j].g / luminanceMap[i][j]), saturation)) * ldr_luminanceMap[i][j];
            ldrPic[i][j].b = (pow((HDR[i][j].b / luminanceMap[i][j]), saturation)) * ldr_luminanceMap[i][j];
            // Compare value
            if(ldrPic[i][j].r>1)
                ldrPic[i][j].r = 1;
            else if(ldrPic[i][j].g>1)
                ldrPic[i][j].g = 1;
            else if(ldrPic[i][j].b>1)
                ldrPic[i][j].b = 1;
            // Remapping ldrPic from 0~1 to 0~255
            ldrPic[i][j].r = ldrPic[i][j].r * 255;
            ldrPic[i][j].g = ldrPic[i][j].g * 255;
            ldrPic[i][j].b = ldrPic[i][j].b * 255;
        }
    }
}
