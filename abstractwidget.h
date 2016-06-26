#ifndef ABSTWIDGET_H
#define ABSTWIDGET_H

#include <QWidget>
#include <hdrmodule.h>
#include <QImage>

class AbstractWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractWidget(QWidget *parent = 0);

signals:
    void nextWidget();

protected:
    QImage picToImg(m_picture pict);
};

#endif // ABSTWIDGET_H
