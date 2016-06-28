#include "gradientwidget.h"
#include "ui_gradientwidget.h"

GradientWidget::GradientWidget(QWidget *parent) :
    AbstractWidget(parent),
    ui(new Ui::GradientWidget)
{
    ui->setupUi(this);
    connect(ui->nextButton,SIGNAL(clicked(bool)),this,SLOT(nextClick(bool)));
    hide();
}

GradientWidget::~GradientWidget()
{
    delete ui;
}

void GradientWidget::showEvent(QShowEvent *)
{
    ui->graphicsView->setScene(new QGraphicsScene);
}

void GradientWidget::execute()
{
    module.mod_main();
    m_picture renPic;
    renPic.width = module.p_width;
    renPic.height = module.p_height;
    renPic.data = module.HDR;
    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(picToImg(renPic)));
    ui->graphicsView->scene()->update();
}
