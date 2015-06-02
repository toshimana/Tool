#pragma once

#include <QDoubleSpinBox>
#include <memory>
#include <functional>

class ObservedDoubleSpinBox :
	public QDoubleSpinBox
{
    Q_OBJECT

public:
	ObservedDoubleSpinBox( QWidget* parent = 0 );
	virtual ~ObservedDoubleSpinBox();

	void connectValueChanged( std::function<void(double)> func );

private slots:
    void on_valueChanged( double value );

private:
	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

