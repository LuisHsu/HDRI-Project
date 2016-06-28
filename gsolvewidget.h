#ifndef GSOLVEWIDGET_H
#define GSOLVEWIDGET_H

#include <qcustomplot.h>
#include <abstractwidget.h>
#include <gsolvemodule.h>

namespace Ui {
class GSolveWidget;
}

class GSolveWidget : public AbstractWidget
{
public:
    explicit GSolveWidget(QWidget *parent = 0);
    ~GSolveWidget();
    void execute();

private:
    Ui::GSolveWidget *ui;
    GSolveModule module;
};

#endif
