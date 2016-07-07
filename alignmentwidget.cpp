#include "alignmentwidget.h"
#include "ui_alignmentwidget.h"

AlignmentWidget::AlignmentWidget(QWidget *parent) :
	AbstractWidget(parent),
	ui(new Ui::AlignmentWidget)
{
	ui->setupUi(this);
	connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(nextClick(bool)));
	hide();
}

AlignmentWidget::~AlignmentWidget()
{
	delete ui;
}

void AlignmentWidget::execute()
{
	model.mod_main();
	QTabWidget *newTab = new QTabWidget;
	for(unsigned int i=0; i<HDRModule::pictures.size(); ++i){
		QGraphicsView *newView = new QGraphicsView(new QGraphicsScene);
		newTab->addTab(newView,QFileInfo(QString(HDRModule::pictures.at(i)->fileName.c_str())).fileName());
		QImage img(model.m_width,model.m_height,QImage::Format_RGBA8888);
		for(int x=0; x<img.width(); ++x){
			for(int y=0; y<img.height(); ++y){
				img.setPixel(x,y,qRgba((int)model.greyPic.at(i)[x][y],(int)model.greyPic.at(i)[x][y],(int)model.greyPic.at(i)[x][y],255));
			}
		}
		newView->scene()->addPixmap(QPixmap::fromImage(img));
	}
	ui->verticalLayout->insertWidget(0,newTab);
}
