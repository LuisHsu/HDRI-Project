#ifndef HDRMODULE_H
#define HDRMODULE_H

#include <vector>
#include <string>

using namespace std;

// The structure of pixel
typedef struct{
    unsigned char r,g,b,a;
}m_pixel;

typedef struct{
    unsigned char r,g,b;
}m_sample;

// The class of each pixture
class m_picture{
public:
    // Data will be stored as a 2-dimentional array, format: data[x][y]
    m_pixel **data;
    m_sample *sample;
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
