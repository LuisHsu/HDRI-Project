#ifndef MATLABQT_H
#define MATLABQT_H

#include <math.h>

class MatlabQt
{
public:
    MatlabQt();
    static int **elementwiseMul(int **first , int **second , int row_size , int col_size);
};

#endif // MATLABQT_H
