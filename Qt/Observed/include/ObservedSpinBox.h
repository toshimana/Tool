#pragma once

#include <QSpinBox>
#include <memory>
#include <functional>

class ObservedSpinBox :
	public QSpinBox
{
    Q_OBJECT

public:
	ObservedSpinBox( QWidget* parent = 0 );
	virtual ~ObservedSpinBox();

	void connectValueChanged( std::function<void(int)> func );

private slots:
    void on_valueChanged( int value );

private:
	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

