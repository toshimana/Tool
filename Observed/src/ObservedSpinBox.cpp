#include "ObservedSpinBox.h"

#include <boost/signals2/signal.hpp>

struct ObservedSpinBox::Impl
{
	boost::signals2::signal<void(int)> valueChanged;
};

ObservedSpinBox::ObservedSpinBox( QWidget* parent )
	: QSpinBox( parent )
	, mImpl( new ObservedSpinBox::Impl() )
{
	connect( this, SIGNAL( valueChanged(int) ), this, SLOT( on_valueChanged(int) ) );
}


ObservedSpinBox::~ObservedSpinBox()
{
}

void
ObservedSpinBox::connectValueChanged( std::function<void(int)> func )
{
	mImpl->valueChanged.connect( func );
}

void
ObservedSpinBox::on_valueChanged( int value )
{
	mImpl->valueChanged( value );
}