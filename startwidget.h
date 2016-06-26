#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <abstractwidget.h>
#include <QFileDialog>
#include <QDebug>
#include <QList>
#include <QImage>
#include <QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <QFile>
#include <vector>

#include <hdrmodule.h>
#include <exif.h>

namespace Ui {
class StartWidget;
}

class StartWidget : public AbstractWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();

public slots:
    void browseFile(bool);
    void nextStep(bool);

private:
    Ui::StartWidget *ui;
    QStringList fileNames;
    QList<QImage> imageList;
    QStringList nameList;
    m_picture *imgToPic(QImage &img, QString name);
};

#endif // STARTWIDGET_H
