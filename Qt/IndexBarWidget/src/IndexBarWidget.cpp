#include "IndexBarWidget.h"
#include "ui_IndexBarWidget.h"

#include <boost/signals2.hpp>

#include <qDebug>

struct IndexBarWidget::Impl
{
	IndexBarWidget* const base;
	Ui::IndexBarWidget ui;

	boost::signals2::signal<void(int)> changedIndex;

	Impl( IndexBarWidget*const obj )
		: base( obj )
	{
		ui.setupUi( base );

		setMaximum( 1 );
		connect( ui.slider,  SIGNAL( valueChanged( int ) ), ui.spinBox, SLOT( setValue( int ) ) );
		connect( ui.spinBox, SIGNAL( valueChanged( int ) ), ui.slider,  SLOT( setValue( int ) ) );
		connect( ui.spinBox, SIGNAL( valueChanged( int ) ), base,       SLOT( valueChanged( int ) ) );
	}

	void setMaximum( int maxSize )
	{
		int size = maxSize - 1; // 0始まりなので、maxSize-1を使用する
		ui.slider ->setMaximum( size );
		ui.spinBox->setMaximum( size );
	}
};

IndexBarWidget::IndexBarWidget(QWidget *parent)
	: QWidget(parent)
	, mImpl( new IndexBarWidget::Impl( this ) )
{
}

IndexBarWidget::~IndexBarWidget()
{

}

void 
IndexBarWidget::connectChangedIndex( std::function<void(int)> func )
{
	mImpl->changedIndex.connect( func );
}

void
IndexBarWidget::setMaximum( int maxSize )
{
	mImpl->setMaximum( maxSize );
}

void
IndexBarWidget::valueChanged( int value )
{
	mImpl->changedIndex( value );
}