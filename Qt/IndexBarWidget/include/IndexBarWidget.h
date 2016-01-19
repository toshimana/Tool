#ifndef INDEXBARWIDGET_H
#define INDEXBARWIDGET_H

#include <QWidget>
#include "ui_IndexBarWidget.h"

class IndexBarWidget : public QWidget
{
	Q_OBJECT

public:
	IndexBarWidget(QWidget *parent = 0);
	~IndexBarWidget();

private:
	Ui::IndexBarWidget ui;
};

#endif // INDEXBARWIDGET_H
