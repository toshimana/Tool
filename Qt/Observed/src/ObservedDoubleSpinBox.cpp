#include "ObservedDoubleSpinBox.h"

#include <boost/signals2/signal.hpp>

struct ObservedDoubleSpinBox::Impl
{
	boost::signals2::signal<void(double)> valueChanged;
};

ObservedDoubleSpinBox::ObservedDoubleSpinBox( QWidget* parent )
	: QDoubleSpinBox( parent )
	, mImpl( new ObservedDoubleSpinBox::Impl() )
{
	connect( this, SIGNAL( valueChanged(double) ), this, SLOT( on_valueChanged(double) ) );
}


ObservedDoubleSpinBox::~ObservedDoubleSpinBox()
{
}

void
ObservedDoubleSpinBox::connectValueChanged( std::function<void(double)> func )
{
	mImpl->valueChanged.connect( func );
}

void
ObservedDoubleSpinBox::on_valueChanged( double value )
{
	mImpl->valueChanged( value );
}