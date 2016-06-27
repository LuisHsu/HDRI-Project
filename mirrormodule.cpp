#include "mirrormodule.h"

#include <QDebug>

MirrorModule::MirrorModule()
{

}

void MirrorModule::mod_main()
{
    m_picture *pict;
    // Calculate for every image sample
    for(unsigned int i = 0 ; i < pictures.size(); i++){
        pict = pictures.at(i);
        sampleSource(pict,pictures.size(),pict->width*pict->height);
        pictures[i] = pict;
    }

}

void MirrorModule::sampleSource(m_picture *src, unsigned int exposureNum, unsigned int pixelNum)
{
    /* Base on input source to calculate rgb's sample , return as sample array
     * exposureNum is the number of exposures image(same as number of images)
     * pixelNum is base on image's pixel , same as the number of row*col
     */
    int samplesNum = ceil(255*2 / (exposureNum - 1))*2;
    int step = floor(float(pixelNum / samplesNum));
    // allocate zValue of rgb
    src->sample = new m_pixel[samplesNum];
    // Initialize and Calculate the sampleIndeices array
    int pixel_index = 0;
    int count = 0;
    for(int i = 0 ; i < (int)src->width ; i++){
        for(int j = 0 ; j < (int)src->height ; j++){
            if((i+j) == pixel_index){
                // do the sample assignment
                src->sample[count].r = src->data[i][j].r;
                src->sample[count].g = src->data[i][j].g;
                src->sample[count].b = src->data[i][j].b;
                count++;
                pixel_index += step;
            }
        }
    }
}

