#pragma once

#include <QComboBox>
#include <memory>
#include <functional>

class ObservedComboBox :
	public QComboBox
{
    Q_OBJECT

public:
	ObservedComboBox( QWidget* parent = 0 );
	virtual ~ObservedComboBox();

	void connectCurrentIndexChanged( std::function<void(int)> func );

private slots:
    void on_currentIndexChanged( int index );

private:
	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

