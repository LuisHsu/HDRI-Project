#ifndef ALIGNMENTMODEL_H
#define ALIGNMENTMODEL_H

#include <hdrmodule.h>
#include <vector>
#include <cmath>

#define EXC_N 2
#define ITERATION_N 4

class AlignmentModel : public HDRModule
{
public:
	AlignmentModel();
	void mod_main();
	vector<unsigned char**> greyPic;
	unsigned int m_width, m_height;
private:
	unsigned char **picScale(unsigned char **pic, unsigned int w, unsigned int h);
	unsigned char toMTB(unsigned char **pic, unsigned int w, unsigned int h);
	void alignment();
	int xorAlign(unsigned char **pic0, unsigned char **pic1, unsigned int w, unsigned int h, int rx, int ry);
	void movePic(unsigned char **pic, unsigned int w, unsigned int h, int rx, int ry);
};

#endif // ALIGNMENTMODEL_H
