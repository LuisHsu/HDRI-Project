#ifndef HDRMODULE_H
#define HDRMODULE_H

#include <vector>
#include <string>

using namespace std;

// The structure of pixel
typedef struct{
    float r,g,b;
}m_pixel;

// The class of each pixture
class m_picture{
public:
    // Data will be stored as a 2-dimentional array, format: data[x][y]
    m_pixel **data, *sample;
    unsigned int width,height;
    float exposureTime;
    string fileName;
};

class HDRModule{
public:
    // The pictures will be stored here
    static vector<m_picture *> pictures;
    // Your program starts here
    virtual void mod_main()=0;
};

#endif // HDRMODULE_H
