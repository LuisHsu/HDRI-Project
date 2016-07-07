#include "alignmentmodel.h"

#include <iostream>

AlignmentModel::AlignmentModel()
{

}

void AlignmentModel::mod_main()
{
	// Get grey image
	for(unsigned int k = 0; k< pictures.size(); ++k){
		m_picture *pic = pictures.at(k);
		unsigned int pWidth = pic->width, pHeight = pic->height;
		unsigned char **grey = new unsigned char*[pWidth];
		for(int i=0; (unsigned int)i<pWidth; ++i){
			grey[i] = new unsigned char[pHeight];
			for(int j=0; (unsigned int)j<pHeight; ++j){
				m_pixel pix = pic->data[i][j];
				grey[i][j] = pix.r*0.2126 + pix.g*0.7152 + pix.b*0.0722;
				grey[i][j] = pix.r*0.2126 + pix.g*0.7152 + pix.b*0.0722;
			}
		}
		greyPic.push_back(grey);
	}
	m_width = pictures.at(0)->width;
	m_height = pictures.at(0)->height;
	// Alignment
	alignment();
}

unsigned char **AlignmentModel::picScale(unsigned char **pic, unsigned int w, unsigned int h)
{
	unsigned char **ret = new unsigned char*[w/2];
	for(int i=0; (unsigned int)i<w/2; ++i){
		ret[i] = new unsigned char[h/2];
		for(int j=0; (unsigned int)j<h/2; ++j){
			float res = 0.0f;
			res += pic[i*2][j*2];
			res += pic[i*2+1][j*2];
			res += pic[i*2][j*2+1];
			res += pic[i*2+1][j*2+1];
			res /= 4;
			ret[i][j] = res;
		}
	}
	return ret;
}

unsigned char AlignmentModel::toMTB(unsigned char **pic, unsigned int w, unsigned int h)
{
	unsigned int count[256];
	for(int i=0; i<256; ++i){
		count[i] = 0;
	}
	for(int i=0; (unsigned int)i<w; ++i){
		for(int j=0; (unsigned int)j<h; ++j){

			count[(int)pic[i][j]]+=1;
		}
	}
	int medCount = w*h/2, medIndex = -1;
	while (medCount > 0) {
		medIndex++;
		medCount -= count[medIndex];
	}
	for(int i=0; (unsigned int)i<w; ++i){
		for(int j=0; (unsigned int)j<h; ++j){
			pic[i][j] = (pic[i][j] > medIndex) ? 255 : 0;
		}
	}
	return medIndex;
}

void AlignmentModel::alignment()
{
	for(unsigned int e=1; e<greyPic.size(); ++e){
		// Prepare MTB
		unsigned char** pic[2][ITERATION_N];
		pic[0][0] = greyPic.at(e-1);
		pic[1][0] = greyPic.at(e);
		for(int ite = 1; ite < ITERATION_N; ++ite){
			unsigned int p_width = m_width/pow(2,ite-1);
			unsigned int p_height = m_height/pow(2,ite-1);
			pic[0][ite] = picScale(pic[0][ite-1],p_width,p_height);
			pic[1][ite] = picScale(pic[1][ite-1],p_width,p_height);
		}
		// Prepare direction
		int dirX = 0, dirY = 0;
		// Count xor
		for(int ite = ITERATION_N-1; ite >=0 ; --ite){
			int loc_Max = 0, mX, mY;
			for(int i=0; i<3; ++i){
				for(int j=0; j<3; ++j){
					int res = xorAlign(pic[0][ite], pic[1][ite], m_width/pow(2,ite), m_height/pow(2,ite), i-1+dirX, j-1+dirY);
					if(res > loc_Max){
						loc_Max = res;
						mX = i;
						mY = j;
					}
				}
			}
			dirX += mX-1;
			dirY += mY-1;
			if(ite > 0){
				movePic(pic[1][ite-1], m_width/pow(2,ite-1), m_height/pow(2,ite-1), dirX, dirY);
			}
		}
		std::cout << "X: " << dirX << " , Y:" << dirY << std::endl;
		movePic(greyPic.at(e), m_width, m_height, dirX, dirY);
	}
}

int AlignmentModel::xorAlign(unsigned char **pic0, unsigned char **pic1, unsigned int w, unsigned int h, int rx, int ry)
{
	int ret = 0;
	unsigned char **mtb0, **mtb1;
	mtb0 = new unsigned char*[w];
	mtb1 = new unsigned char*[w];
	for(unsigned int i=0; i<w; ++i){
		mtb0[i] = new unsigned char[h];
		mtb1[i] = new unsigned char[h];
		for(unsigned int j=0; j<h; ++j){
			mtb0[i][j] = pic0[i][j];
			mtb1[i][j] = pic1[i][j];
		}
	}
	unsigned char med[2];
	med[0] = toMTB(mtb0,w,h);
	med[1] = toMTB(mtb1,w,h);
	for(unsigned int i=0; i<w; ++i){
		int tx = i+rx;
		if((tx < 0)||(tx > (int)w-1)) continue;
		for(unsigned int j=0; j<h; ++j){
			int ty = j+ry;
			if((ty < 0)||(ty > (int)h-1)) continue;
			if((abs(pic0[i][j] - med[0]) < EXC_N) || (abs(pic1[i][j] - med[1]) < EXC_N)) continue;
			if(!(mtb1[i][j] ^ mtb0[tx][ty])){
				ret+=1;
			}
		}
	}
	return ret;
}

void AlignmentModel::movePic(unsigned char **pic, unsigned int w, unsigned int h, int rx, int ry)
{
	if(rx > 0){
		for(unsigned int i=w-1; i>0; --i){
			for(unsigned int j=0; j<h; ++j){
				pic[i][j] = pic[i-1][j];
			}
		}
	}else{
		if(rx < 0){
			for(unsigned int i=0; i<w-1; ++i){
				for(unsigned int j=0; j<h; ++j){
					pic[i][j] = pic[i+1][j];
				}
			}
		}
	}
	if(ry > 0){
		for(unsigned int i=0; i<w; ++i){
			for(unsigned int j=h-1; j>0; --j){
				pic[i][j] = pic[i][j-1];
			}
		}
	}else{
		if(ry < 0){
			for(unsigned int i=0; i<w; ++i){
				for(unsigned int j=0; j<h-1; ++j){
					pic[i][j] = pic[i][j+1];
				}
			}
		}
	}
}
