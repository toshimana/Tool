#include "ObservedPushButton.h"

#include <boost/signals2/signal.hpp>

struct ObservedPushButton::Impl
{
	boost::signals2::signal<void( void )> pressed;
	boost::signals2::signal<void( void )> released;
};

ObservedPushButton::ObservedPushButton( QWidget* parent )
	: QPushButton( parent )
	, mImpl( new ObservedPushButton::Impl() )
{
	connect( this, SIGNAL( pressed ( void ) ), this, SLOT( on_pressed ( void ) ) );
	connect( this, SIGNAL( released( void ) ), this, SLOT( on_released( void ) ) );
}


ObservedPushButton::~ObservedPushButton()
{
}

void
ObservedPushButton::connectPressed( std::function<void( void )> func )
{
	mImpl->pressed.connect( func );
}

void
ObservedPushButton::on_pressed( void )
{
	mImpl->pressed();
}

void
ObservedPushButton::connectReleased( std::function<void( void )> func )
{
	mImpl->released.connect( func );
}

void 
ObservedPushButton::on_released( void )
{
	mImpl->released();
}
