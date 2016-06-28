#include "gradientmodule.h"

GradientModule::GradientModule():calc(0,255)
{

}

void GradientModule::mod_main()
{
    // For number of picture (number of exposures)
    unsigned int numExpo = pictures.size();
    p_width = pictures.at(0)->width;
    p_height = pictures.at(0)->height;
    // Allocate the HDR and sum
    m_pixel **sum, **wij , **saturatedPixel , **m;
    m_picture *pict = pictures.at(0);
    HDR = new m_pixel*[pict->width];
    sum = new m_pixel*[pict->width];
    m = new m_pixel*[pict->width];
    wij = new m_pixel*[pict->width];
    saturatedPixel = new m_pixel*[pict->width];
    for(unsigned int i = 0 ; i < pict->width;i++){
        HDR[i] = new m_pixel[pict->height];
        sum[i] = new m_pixel[pict->height];
        m[i] = new m_pixel[pict->height];
        wij[i] = new m_pixel[pict->height];
        saturatedPixel[i] = new m_pixel[pict->height];
        for(unsigned int j = 0 ; j < pict->height; ++j){
            HDR[i][j].r = 0;
            sum[i][j].r = 0;
            m[i][j].r = 0;
            wij[i][j].r = 0;
            saturatedPixel[i][j].r = 0;
            HDR[i][j].g = 0;
            sum[i][j].g = 0;
            m[i][j].g = 0;
            wij[i][j].g = 0;
            saturatedPixel[i][j].g = 0;
            HDR[i][j].b = 0;
            sum[i][j].b = 0;
            m[i][j].b = 0;
            wij[i][j].b = 0;
            saturatedPixel[i][j].b = 0;
        }
    }
    // In images loop
    for(unsigned int k = 0 ; k < numExpo ; k++){
        pict = pictures.at(k);
        // Assign the image's info with index in weight function , and store value in wij ; Then do the summation
        for(unsigned int i = 0 ; i < pictures.at(0)->width; i++){
            for(unsigned int j = 0 ; j < pictures.at(0)->height ; j++){
                // Assign
                wij[i][j].r = calc.getWeight(pict->data[i][j].r);
                wij[i][j].g = calc.getWeight(pict->data[i][j].g);
                wij[i][j].b = calc.getWeight(pict->data[i][j].b);
                // Sum
                sum[i][j].r += wij[i][j].r;
                sum[i][j].g += wij[i][j].g;
                sum[i][j].b += wij[i][j].b;
                // Initialize the SaturatedPixel array with 1
                saturatedPixel[i][j].r = 1;
                saturatedPixel[i][j].g = 1;
                saturatedPixel[i][j].b = 1;
                // Initialize m
                m[i][j].r = GSolver::xR.at(pict->data[i][j].r + 1) - log(pictures.at(k)->exposureTime);
                m[i][j].g = GSolver::xG.at(pict->data[i][j].g + 1) - log(pictures.at(k)->exposureTime);
                m[i][j].b = GSolver::xB.at(pict->data[i][j].b + 1) - log(pictures.at(k)->exposureTime);
                // Search rgb
                if((pict->data[i][j].r == 255)||(pict->data[i][j].g == 255)||(pict->data[i][j].b == 255)){
                    saturatedPixel[i][j].r = 0;
                    saturatedPixel[i][j].g = 0;
                    saturatedPixel[i][j].b = 0;
                }
                // Do the elementwise operation - multiply (wij * m)
                HDR[i][j].r += wij[i][j].r * m[i][j].r;
                HDR[i][j].g += wij[i][j].g * m[i][j].g;
                HDR[i][j].b += wij[i][j].b * m[i][j].b;
                // For HDR
                HDR[i][j].r = HDR[i][j].r * saturatedPixel[i][j].r;
                HDR[i][j].g = HDR[i][j].g * saturatedPixel[i][j].g;
                HDR[i][j].b = HDR[i][j].b * saturatedPixel[i][j].b;
                // For SUM
                sum[i][j].r = sum[i][j].r * saturatedPixel[i][j].r;
                sum[i][j].g = sum[i][j].g * saturatedPixel[i][j].g;
                sum[i][j].b = sum[i][j].b * saturatedPixel[i][j].b;
                // Search hdr
                if((HDR[i][j].r == 0)||(HDR[i][j].g == 0)||(HDR[i][j].b == 0)){
                    HDR[i][j].r = 0;
                    HDR[i][j].g = 0;
                    HDR[i][j].b = 0;
                }
            }
        }
    }
    for(unsigned int i = 0 ; i < pictures.at(0)->width ; i++){
        for(unsigned int j = 0 ; j < pictures.at(0)->height; j++){
            if((HDR[i][j].r == 0)||(HDR[i][j].g == 0)||(HDR[i][j].b == 0)){
                HDR[i][j].r = m[i][j].r;
                HDR[i][j].g = m[i][j].g;
                HDR[i][j].b = m[i][j].b;
                sum[i][j].r = 1;
                sum[i][j].g = 1;
                sum[i][j].b = 1;
            }
            HDR[i][j].r = exp(HDR[i][j].r / sum[i][j].r);
            HDR[i][j].g = exp(HDR[i][j].g / sum[i][j].g);
            HDR[i][j].b = exp(HDR[i][j].b / sum[i][j].b);
        }
    }
    for(unsigned int i = 0; i<p_width; ++i){
        delete [] sum[i];
        delete [] wij[i];
        delete [] saturatedPixel[i];
        delete [] m[i];
    }
    delete [] sum;
    delete [] wij;
    delete [] saturatedPixel;
    delete [] m;
}
