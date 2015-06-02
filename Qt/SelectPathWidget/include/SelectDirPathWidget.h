#ifndef SELECTDIRPATHWIDGET_H
#define SELECTDIRPATHWIDGET_H

#include "SelectPathWidget.h"

class SelectDirPathWidget : public SelectPathWidget
{
	Q_OBJECT

public:
	SelectDirPathWidget(QWidget *parent);
	~SelectDirPathWidget();

protected:

private slots:
	void on_selectButton_pressed( void );

private:
	
};

#endif // SELECTDIRPATHWIDGET_H
