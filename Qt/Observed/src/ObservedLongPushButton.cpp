#include "ObservedLongPushButton.h"

#include <boost/signals2/signal.hpp>
#include <QTimer>

namespace
{
	const int defaultIntervalMS = 3000; // 3sec
}

struct ObservedLongPushButton::Impl
{
	QTimer timer;
	boost::signals2::signal<void( void )> shortPressed;
	boost::signals2::signal<void( void )> longPressed;
};

ObservedLongPushButton::ObservedLongPushButton( QWidget* parent )
	: QPushButton( parent )
	, mImpl( new ObservedLongPushButton::Impl() )
{
	mImpl->timer.setInterval( defaultIntervalMS );
	mImpl->timer.setSingleShot( true );
	connect( &(mImpl->timer), SIGNAL( timeout( void ) ), this, SLOT( on_longPressed( void ) ) );

	connect( this, SIGNAL( pressed ( void ) ), &(mImpl->timer), SLOT( start( void ) ) );
	connect( this, SIGNAL( released( void ) ), this, SLOT( on_released( void ) ) );
}


ObservedLongPushButton::~ObservedLongPushButton()
{
}

void
ObservedLongPushButton::connectShortPressed( std::function<void( void )> func )
{
	mImpl->shortPressed.connect( func );
}

void
ObservedLongPushButton::connectLongPressed( std::function<void( void )> func )
{
	mImpl->longPressed.connect( func );
}

void
ObservedLongPushButton::setInterval( int msec )
{
	mImpl->timer.setInterval( msec );
}

void 
ObservedLongPushButton::on_released( void )
{
	if ( mImpl->timer.isActive() ) {
		mImpl->timer.stop();
		mImpl->shortPressed();
	}
}

void
ObservedLongPushButton::on_longPressed( void )
{
	mImpl->longPressed();
}