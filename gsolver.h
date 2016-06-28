#ifndef GSOLVER_H
#define GSOLVER_H

#include <hdrmodule.h>
#include <QObject>
#include <eigen3/Eigen/Eigen>
#include <calweight.h>

class GSolver : public QObject{
    Q_OBJECT
public:
    GSolver(vector<m_picture *> &pictures);
    void solve(float B[]);
    int lamda_smooth;
    int g_size;
    static vector<float> xR, xG, xB;
private:
    unsigned int numSamples;
    unsigned int numExposures;
    CalWeight calc;
    vector<m_picture *> &pictures;
};

#endif // GSOLVER_H
