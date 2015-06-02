#include "SelectDirPathWidget.h"

#include <QFileDialog>

SelectDirPathWidget::SelectDirPathWidget(QWidget *parent)
	: SelectPathWidget(parent)
{

}

SelectDirPathWidget::~SelectDirPathWidget()
{

}

void 
SelectDirPathWidget::on_selectButton_pressed( void )
{
	QString path = QFileDialog::getExistingDirectory();
	if ( path.length() == 0 ) return;

	setPath( path );
}
