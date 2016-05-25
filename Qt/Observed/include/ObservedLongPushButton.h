#pragma once

#include <QPushButton>
#include <memory>
#include <functional>

class ObservedLongPushButton :
	public QPushButton
{
    Q_OBJECT

public:
	ObservedLongPushButton( QWidget* parent = 0 );
	virtual ~ObservedLongPushButton();

	void connectShortPressed( std::function<void( void )> func );
	void connectLongPressed ( std::function<void( void )> func );
	void setInterval( int msec );

private slots:
	void on_released( void );
	void on_longPressed( void );

private:
	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

