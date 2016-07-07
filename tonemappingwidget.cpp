#include "tonemappingwidget.h"
#include "ui_tonemappingwidget.h"

ToneMappingWidget::ToneMappingWidget(QWidget *parent) :
    AbstractWidget(parent),
    ui(new Ui::ToneMappingWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(nextClick(bool)));
    hide();
}

ToneMappingWidget::~ToneMappingWidget()
{
    delete ui;
}

void ToneMappingWidget::execute()
{
    module.mod_main ();
    QImage ret(module.p_width,module.p_height,QImage::Format_RGBA8888);
    for(int i=0; i<ret.width(); ++i){
        for(int j=0; j<ret.height(); ++j){
            ret.setPixel(i,j,qRgba(0+module.ldrPic.at(i)[j].r,0+module.ldrPic.at(i)[j].g,0+module.ldrPic.at(i)[j].b,255));
        }
    }
    //ret.save(QString::fromStdString (module.outFilename),"JPG");
    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(ret));
    ui->graphicsView->scene()->update();
}

void ToneMappingWidget::showEvent(QShowEvent *)
{
    ui->graphicsView->setScene (new QGraphicsScene);
}
