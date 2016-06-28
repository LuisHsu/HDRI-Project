#ifndef TONEMAPPINGWIDGET_H
#define TONEMAPPINGWIDGET_H

#include <QGraphicsScene>

#include <abstractwidget.h>
#include <tonemappingmodule.h>

namespace Ui {
class ToneMappingWidget;
}

class ToneMappingWidget : public AbstractWidget
{
    Q_OBJECT

public:
    explicit ToneMappingWidget(QWidget *parent = 0);
    ~ToneMappingWidget();
    void execute();
    void showEvent (QShowEvent *);
private:
    Ui::ToneMappingWidget *ui;
    ToneMappingModule module;
};

#endif // TONEMAPPINGWIDGET_H
