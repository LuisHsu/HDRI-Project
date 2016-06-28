#include "gsolvemodule.h"

#include <QDebug>

GSolveModule::GSolveModule()
{
}

void GSolveModule::mod_main()
{
    m_picture *pict;
    // Calculate for every image sample + exposures matrix
    float exposureMat_B[pictures.size()];
    for(unsigned int i = 0 ; i < pictures.size(); i++){
        pict = pictures.at(i);
        sampleSource(pict,pictures.size(),pict->width*pict->height);
        // for exposures matrix B
        exposureMat_B[i] = log(pict->exposureTime);
    }
    // GSolver
    solver = new GSolver(pictures);
    solver->solve(exposureMat_B);
}

void GSolveModule::sampleSource(m_picture *src, unsigned int exposureNum, unsigned int pixelNum)
{
    /* Base on input source to calculate rgb's sample , return as sample array
     * exposureNum is the number of exposures image(same as number of images)
     * pixelNum is base on image's pixel , same as the number of row*col
     */
    int samplesNum = ceil(255*2 / (exposureNum - 1))*2;
    int step = floor((float)pixelNum / (float)samplesNum);
    // Initialize and Calculate the sampleIndeices array
    int pixel_index = 0;
    for(int i = 0 ; i < (int)src->width ; i++){
        for(int j = 0 ; j < (int)src->height ; j++){
            if(!(pixel_index % step)){
                // do the sample assignment
                m_pixel newSample;
                newSample.r = src->data[i][j].r;
                newSample.g = src->data[i][j].g;
                newSample.b = src->data[i][j].b;
                src->sample.push_back(newSample);
            }
            pixel_index++;
        }
    }
}

