#include "SelectPathWidget.h"
#include "ui_SelectPathWidget.h"

#include <QFileDialog>

#include <qtsjis.hpp>

struct SelectPathWidget::Impl
{
	Impl( SelectPathWidget* obj );
	~Impl( void );

	SelectPathWidget* base;
	Ui::SelectPathWidget ui;

	QString caption;
	QString dir;
	QFileDialog::Options options;
};


SelectPathWidget::Impl::Impl( SelectPathWidget* obj )
	: base( obj )
{
	ui.setupUi( base );
}

SelectPathWidget::Impl::~Impl( void )
{
}

SelectPathWidget::SelectPathWidget( QWidget *parent )
	: QWidget(parent)
	, mImpl( new SelectPathWidget::Impl( this ) )
{
}

SelectPathWidget::~SelectPathWidget()
{
}

void
SelectPathWidget::setLabel( const std::string& label )
{
	mImpl->ui.pathLabel->setText( qtsjis::toQString( label ) );
}

std::string
SelectPathWidget::getPath( void ) const
{
	return qtsjis::toString( mImpl->ui.pathEdit->text() ); 
}

void
SelectPathWidget::setPath( const std::string& path )
{
	mImpl->ui.pathEdit->setText( qtsjis::toQString( path ) );
}

void
SelectPathWidget::setPath( const QString& path )
{
	mImpl->ui.pathEdit->setText( path );
}

void 
SelectPathWidget::on_selectButton_pressed( void )
{
	QString path = QFileDialog::getExistingDirectory( this, mImpl->caption, mImpl->dir, mImpl->options );
	if ( path.length() == 0 ) {
		return;
	} 

	setPath( path );
}

