#ifndef ABSTWIDGET_H
#define ABSTWIDGET_H

#include <QWidget>
#include <QImage>

#include <QDebug>

#include <hdrmodule.h>

class AbstractWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractWidget(QWidget *parent = 0);
    virtual void showEvent (QShowEvent *);
signals:
    void nextWidget();
protected:
    QImage picToImg(m_picture pict);
protected slots:
    void nextClick(bool);
};

#endif // ABSTWIDGET_H
