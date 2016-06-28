#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include <abstractwidget.h>
#include <startwidget.h>
#include <gsolvewidget.h>
#include <gradientwidget.h>
#include <tonemappingwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void nextWidget();

private:
    Ui::MainWindow *ui;
    QList<AbstractWidget *> widgetList;
    unsigned int curWidget;
};

#endif // MAINWINDOW_H
