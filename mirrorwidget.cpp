#include "mirrorwidget.h"
#include "ui_mirrorwidget.h"

MirrorWidget::MirrorWidget(QWidget *parent) :
    AbstractWidget(parent),
    ui(new Ui::MirrorWidget)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene);
    pixmap = new QGraphicsPixmapItem;
    ui->graphicsView->scene()->addItem(pixmap);
    connect (ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(nextClick(bool)));
    hide();
}

MirrorWidget::~MirrorWidget()
{
    delete ui;
}

void MirrorWidget::showEvent(QShowEvent *)
{
    module.mod_main();
    pixmap->setPixmap(QPixmap::fromImage(picToImg(*(module.pictures.front()))));
    ui->graphicsView->scene()->update();
}
