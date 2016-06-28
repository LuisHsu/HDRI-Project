#include "gsolver.h"

#include <iostream>

GSolver::GSolver(vector<m_picture *> &pictures) : lamda_smooth(50), calc(0,255), pictures(pictures)
{
    numExposures = pictures.size();
    numSamples = ceil(255*2 / (numExposures- 1))*2;
}

vector<float> GSolver::xR = vector<float>();
vector<float> GSolver::xG = vector<float>();
vector<float> GSolver::xB = vector<float>();

void GSolver::solve(float B[])
{
    /*** Red Channel ***/
    // Init
    float A[numSamples*numExposures+255][256+numSamples], b[numSamples*numExposures+255];
    for(unsigned int i = 0; i < numSamples*numExposures+255; i++){
        for(unsigned int j=0; j<256+numSamples; j++)
            A[i][j] = 0;
        b[i] = 0;
    }
    // data-fitting equations
    int k = 0;
    for(unsigned int i=0; i<numSamples; i++){
        for(unsigned int j=0; j<numExposures; j++){
            int wij = calc.getWeight(pictures[j]->sample[i].r);
            A[k][(unsigned int)pictures[j]->sample[i].r] = wij;
            A[k][256+i] = -wij;
            b[k] = wij*B[j];
            k++;
        }
    }
    // Fix the curve by setting its middle value to 0
    A[k][129] = 1;
    k++;
    // Smoothness equations
    for(unsigned int i=0; i<254; i++){
        float w = lamda_smooth*calc.getWeight(i+1);
        A[k][i] = w;
        A[k][i+1] = -2*w;
        A[k][i+2] = w;
        k++;
    }
    Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> AA(numSamples*numExposures+256, 256+numSamples);
    Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> bb(numSamples*numExposures+256, 1);
    for(unsigned int i = 0; i < numSamples*numExposures+255; i++){
        for(unsigned int j=0; j<256+numSamples; j++)
            AA(i,j) = A[i][j];
        bb(i,0) = b[i];
    }
    {
        Eigen::JacobiSVD<Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>> solver(AA,Eigen::ComputeThinU | Eigen::ComputeThinV);
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic> x = solver.solve(bb);
        g_size = 256+numSamples;
        for(unsigned int i=0; i<x.rows(); ++i){
            xR.push_back(x(i,0));
        }
    }
    /*** Green Channel ***/
    // Init
    for(unsigned int i = 0; i < numSamples*numExposures+255; i++){
        for(unsigned int j=0; j<256+numSamples; j++)
            A[i][j] = 0;
        b[i] = 0;
    }
    // data-fitting equations
    k = 0;
    for(unsigned int i=0; i<numSamples; i++){
        for(unsigned int j=0; j<numExposures; j++){
            int wij = calc.getWeight(pictures[j]->sample[i].g);
            A[k][(unsigned int)pictures[j]->sample[i].g] = wij;
            A[k][256+i] = -wij;
            b[k] = wij*B[j];
            k++;
        }
    }
    // Fix the curve by setting its middle value to 0
    A[k][129] = 1;
    k++;
    // Smoothness equations
    for(unsigned int i=0; i<254; i++){
        float w = lamda_smooth*calc.getWeight(i+1);
        A[k][i] = w;
        A[k][i+1] = -2*w;
        A[k][i+2] = w;
        k++;
    }
    for(unsigned int i = 0; i < numSamples*numExposures+255; i++){
        for(unsigned int j=0; j<256+numSamples; j++)
            AA(i,j) = A[i][j];
        bb(i,0) = b[i];
    }
    {
        Eigen::JacobiSVD<Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>> solver(AA,Eigen::ComputeThinU | Eigen::ComputeThinV);
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic> x = solver.solve(bb);
        for(unsigned int i=0; i<x.rows(); ++i){
            xG.push_back(x(i,0));
        }
    }
    /*** Blue Channel ***/
    // Init
    for(unsigned int i = 0; i < numSamples*numExposures+255; i++){
        for(unsigned int j=0; j<256+numSamples; j++)
            A[i][j] = 0;
        b[i] = 0;
    }
    // data-fitting equations
    k = 0;
    for(unsigned int i=0; i<numSamples; i++){
        for(unsigned int j=0; j<numExposures; j++){
            int wij = calc.getWeight(pictures[j]->sample[i].b);
            A[k][(unsigned int)pictures[j]->sample[i].b] = wij;
            A[k][256+i] = -wij;
            b[k] = wij*B[j];
            k++;
        }
    }
    // Fix the curve by setting its middle value to 0
    A[k][129] = 1;
    k++;
    // Smoothness equations
    for(unsigned int i=0; i<254; i++){
        float w = lamda_smooth*calc.getWeight(i+1);
        A[k][i] = w;
        A[k][i+1] = -2*w;
        A[k][i+2] = w;
        k++;
    }
    for(unsigned int i = 0; i < numSamples*numExposures+255; i++){
        for(unsigned int j=0; j<256+numSamples; j++)
            AA(i,j) = A[i][j];
        bb(i,0) = b[i];
    }
    {
        Eigen::JacobiSVD<Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>> solver(AA,Eigen::ComputeThinU | Eigen::ComputeThinV);
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic> x = solver.solve(bb);
        for(unsigned int i=0; i<x.rows(); ++i){
            xB.push_back(x(i,0));
        }
    }
}
