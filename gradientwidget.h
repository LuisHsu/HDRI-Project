#ifndef GRADIENTWIDGET_H
#define GRADIENTWIDGET_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <abstractwidget.h>
#include <gradientmodule.h>

namespace Ui {
class GradientWidget;
}

class GradientWidget : public AbstractWidget
{
    Q_OBJECT

public:
    explicit GradientWidget(QWidget *parent = 0);
    ~GradientWidget();
    void showEvent (QShowEvent *);
    void execute();
private:
    Ui::GradientWidget *ui;
    GradientModule module;
};

#endif // GRADIENTWIDGET_H
