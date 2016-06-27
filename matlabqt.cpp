#include "matlabqt.h"

MatlabQt::MatlabQt()
{

}

int **MatlabQt::elementwiseMul(int **first, int **second, int row_size, int col_size)
{
    // result array allocate
    int **result = new int*[row_size];
    for(int i = 0; i < row_size; ++i)
        result[i] = new int[col_size];
    // do every element multiply in first and second
    for(int i = 0 ; i < row_size ; i++){
        for(int j = 0 ; j < col_size ; j++){
            result[i][j] = first[i][j]*second[i][j];
        }
    }
    // return with an 2D array
    return result;
}


