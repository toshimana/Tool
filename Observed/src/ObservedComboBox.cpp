#include "ObservedComboBox.h"

#include <boost/signals2/signal.hpp>

struct ObservedComboBox::Impl
{
	boost::signals2::signal<void(int)> currentIndexChanged;
};

ObservedComboBox::ObservedComboBox( QWidget* parent )
	: QComboBox( parent )
	, mImpl( new ObservedComboBox::Impl() )
{
	connect( this, SIGNAL( currentIndexChanged(int) ), this, SLOT( on_currentIndexChanged(int) ) );
}


ObservedComboBox::~ObservedComboBox()
{
}

void
ObservedComboBox::connectCurrentIndexChanged( std::function<void(int)> func )
{
	mImpl->currentIndexChanged.connect( func );
}

void
ObservedComboBox::on_currentIndexChanged( int value )
{
	mImpl->currentIndexChanged( value );
}