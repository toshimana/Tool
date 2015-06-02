#ifndef SELECTOPENFILEPATHWIDGET_H
#define SELECTOPENFILEPATHWIDGET_H

#include "SelectPathWidget.h"

class SelectOpenFilePathWidget : public SelectPathWidget
{
	Q_OBJECT

public:
	SelectOpenFilePathWidget(QWidget *parent);
	virtual ~SelectOpenFilePathWidget();

protected:

private slots:
	void on_selectButton_pressed( void );

private:
	
};

#endif // SELECTOPENFILEPATHWIDGET_H
