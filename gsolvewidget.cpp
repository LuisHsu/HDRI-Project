#include "gsolvewidget.h"
#include "ui_gsolvewidget.h"

GSolveWidget::GSolveWidget(QWidget *parent) :
    AbstractWidget(parent),
    ui(new Ui::GSolveWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(nextClick(bool)));

    ui->tabR->addGraph();
    ui->tabR->xAxis->setLabel("log exposure (X)");
    ui->tabR->yAxis->setLabel("pixel value (Z)");
    ui->tabR->repaint();

    ui->tabG->addGraph();
    ui->tabG->xAxis->setLabel("log exposure (X)");
    ui->tabG->yAxis->setLabel("pixel value (Z)");
    ui->tabG->repaint();

    ui->tabB->addGraph();
    ui->tabB->xAxis->setLabel("log exposure (X)");
    ui->tabB->yAxis->setLabel("pixel value (Z)");
    ui->tabB->repaint();
    hide();
}

GSolveWidget::~GSolveWidget()
{
    delete ui;
}

void GSolveWidget::execute()
{
    module.mod_main();
    QVector<double> xR,xG,xB,y;
    double rM = (double)module.solver->xR.at(0),rm = (double)module.solver->xR.at(0);
    double gM = (double)module.solver->xG.at(0),gm = (double)module.solver->xG.at(0);
    double bM = (double)module.solver->xB.at(0),bm = (double)module.solver->xB.at(0);
    for(int i=0; i<256; ++i){
        xR.push_back((double)module.solver->xR.at(i));
        if((double)module.solver->xR.at(i)>rM){
            rM = (double)module.solver->xR.at(i);
        }else{
            if((double)module.solver->xR.at(i) < rm){
                rm = (double)module.solver->xR.at(i);
            }
        }
        xG.push_back((double)module.solver->xG.at(i));
        if((double)module.solver->xG.at(i)>gM){
            gM = (double)module.solver->xG.at(i);
        }else{
            if((double)module.solver->xG.at(i) < gm){
                gm = (double)module.solver->xG.at(i);
            }
        }
        xB.push_back((double)module.solver->xB.at(i));
        if((double)module.solver->xB.at(i)>bM){
            bM = (double)module.solver->xB.at(i);
        }else{
            if((double)module.solver->xB.at(i) < bm){
                bm = (double)module.solver->xB.at(i);
            }
        }
        y.push_back(i);
    }
    ui->tabR->graph(0)->setData(xR,y);
    ui->tabR->xAxis->setRange(rM, rm);
    ui->tabR->yAxis->setRange(0, 255);
    ui->tabR->graph()->setPen(QPen(Qt::red,2));
    ui->tabR->replot();
    ui->tabG->graph(0)->setData(xG,y);
    ui->tabG->xAxis->setRange(gM, gm);
    ui->tabG->yAxis->setRange(0, 255);
    ui->tabG->graph()->setPen(QPen(Qt::green,2));
    ui->tabG->replot();
    ui->tabB->graph(0)->setData(xB,y);
    ui->tabB->xAxis->setRange(bM, bm);
    ui->tabB->yAxis->setRange(0, 255);
    ui->tabB->graph()->setPen(QPen(Qt::blue,2));
    ui->tabB->replot();
}
