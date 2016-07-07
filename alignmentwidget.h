#ifndef ALIGNMENTWIDGET_H
#define ALIGNMENTWIDGET_H

#include <abstractwidget.h>
#include <alignmentmodel.h>
#include <QTabWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFileInfo>
#include <QImage>

namespace Ui {
	class AlignmentWidget;
}

class AlignmentWidget : public AbstractWidget
{
	Q_OBJECT

public:
	explicit AlignmentWidget(QWidget *parent = 0);
	~AlignmentWidget();
	void execute();

private:
	Ui::AlignmentWidget *ui;
	AlignmentModel model;
};

#endif // ALIGNMENTWIDGET_H
