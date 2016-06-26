#ifndef MIRRORWIDGET_H
#define MIRRORWIDGET_H

#include <abstractwidget.h>

#include <mirrormodule.h>
#include <QGraphicsPixmapItem>

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
private slots:
    void on_pushButton_clicked(bool);
};

#endif // MIRRORWIDGET_H
