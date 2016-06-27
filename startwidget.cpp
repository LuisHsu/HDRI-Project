#include "startwidget.h"
#include "ui_startwidget.h"

StartWidget::StartWidget(QWidget *parent) :
    AbstractWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    connect(ui->browseButton,SIGNAL(clicked(bool)),this,SLOT(browseFile(bool)));
    connect(ui->nextButton,SIGNAL(clicked(bool)),this,SLOT(nextStep(bool)));
}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::browseFile(bool)
{
    QLayoutItem *item;
    while((item = ui->scrollLayout->layout()->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
    nameList = QFileDialog::getOpenFileNames(this,"Open Image files");
    for(QStringList::iterator it = nameList.begin(); it != nameList.end(); ++it){
        imageList.push_back(QImage(*it));
        QLabel *label = new QLabel(this);
        int scaledSize = ui->scrollArea->size().height()/2-20;
        QPixmap filePixmap = QPixmap::fromImage(imageList.last()).scaled(scaledSize,scaledSize,Qt::KeepAspectRatio);
        label->setPixmap(filePixmap);
        QGridLayout *grid = static_cast<QGridLayout *>(ui->scrollLayout->layout());
        grid->addWidget(label,(imageList.size()-1)/2,imageList.size()%2,Qt::AlignHCenter);
    }
}

void StartWidget::nextStep(bool)
{
    for(int i=0; i<nameList.size(); ++i){
        HDRModule::pictures.push_back(imgToPic(imageList[i],nameList[i]));
    }
    emit nextWidget();
}

m_picture* StartWidget::imgToPic(QImage &img, QString name)
{
    m_picture *ret = new m_picture;
    ret->fileName = name.toStdString();
    ret->width = img.width();
    ret->height = img.height();
    ret->data = new m_pixel*[ret->width];
    for(int i=0; i<(int)ret->width; ++i){
        ret->data[i] = new m_pixel[ret->height];
    }
    for(int i=0; i<(int)ret->height; ++i){
        QRgb *line = (QRgb *)img.scanLine(i);
        for(int j=0; j<(int)ret->width; ++j){
            ret->data[j][i].r = qRed(line[j]);
            ret->data[j][i].g = qGreen(line[j]);
            ret->data[j][i].b = qBlue(line[j]);
        }
    }
    // Get metadata
    QFile fileIn(name);
    fileIn.open(QFile::ReadOnly);
    EXIFInfo info;
    ParseEXIF((unsigned char*)fileIn.readAll().data(),fileIn.size (),info);
    ret->exposureTime= info.exposureTime;
    fileIn.close();
    return ret;
}
