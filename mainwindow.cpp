#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),curWidget(0)
{
    ui->setupUi(this);
    widgetList.push_back(new StartWidget(this));
    widgetList.push_back(new MirrorWidget(this));
    setCentralWidget(widgetList.front());
    connect(widgetList.front(),SIGNAL(nextWidget()),this,SLOT(nextWidget()));
    widgetList.front()->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nextWidget()
{
    if(curWidget == widgetList.size()-1){
        QApplication::exit(0);
    }else{
        widgetList.at(curWidget)->hide();
        disconnect(widgetList.at(curWidget),SIGNAL(nextWidget()),this,SLOT(nextWidget()));
        curWidget++;
        setCentralWidget(widgetList.at(curWidget));
        connect(widgetList.at(curWidget),SIGNAL(nextWidget()),this,SLOT(nextWidget()));
        widgetList.at(curWidget)->show();
    }
}

