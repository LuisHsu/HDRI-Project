#include "abstractwidget.h"

AbstractWidget::AbstractWidget(QWidget *parent) : QWidget(parent)
{

}

void AbstractWidget::showEvent(QShowEvent *)
{

}

QImage AbstractWidget::picToImg(m_picture pict)
{
    QImage ret(pict.width,pict.height,QImage::Format_RGBA8888);
    for(int i=0; i<ret.width(); ++i){
        for(int j=0; j<ret.height(); ++j){
            ret.setPixel(i,j,qRgba(0+pict.data[i][j].r,0+pict.data[i][j].g,0+pict.data[i][j].b,255));
        }
    }
    return ret;
}

void AbstractWidget::nextClick(bool)
{
    emit nextWidget ();
}
