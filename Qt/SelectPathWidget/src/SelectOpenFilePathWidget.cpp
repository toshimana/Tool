#include "SelectOpenFilePathWidget.h"

#include <QFileDialog>

SelectOpenFilePathWidget::SelectOpenFilePathWidget(QWidget *parent)
	: SelectPathWidget(parent)
{

}

SelectOpenFilePathWidget::~SelectOpenFilePathWidget()
{

}

void 
SelectOpenFilePathWidget::on_selectButton_pressed( void )
{
	QString path = QFileDialog::getOpenFileName();
	if ( path.length() == 0 ) return;

	setPath( path );
}
