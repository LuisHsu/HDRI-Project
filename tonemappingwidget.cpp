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
    m_picture renPic;
    renPic.width = module.p_width;
    renPic.height = module.p_height;
    renPic.data = module.ldrPic;
    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(picToImg(renPic)));
    ui->graphicsView->scene()->update();
}

void ToneMappingWidget::showEvent(QShowEvent *)
{
    ui->graphicsView->setScene (new QGraphicsScene);
}
