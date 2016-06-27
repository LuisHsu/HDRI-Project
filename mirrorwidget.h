#ifndef MIRRORWIDGET_H
#define MIRRORWIDGET_H

#include <QGraphicsPixmapItem>

#include <abstractwidget.h>
#include <mirrormodule.h>

namespace Ui {
class MirrorWidget;
}

class MirrorWidget : public AbstractWidget
{
public:
    explicit MirrorWidget(QWidget *parent = 0);
    ~MirrorWidget();
    void showEvent(QShowEvent *);

private:
    Ui::MirrorWidget *ui;
    MirrorModule module;
    QGraphicsPixmapItem *pixmap;
};

#endif // MIRRORWIDGET_H
