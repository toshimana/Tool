#include "PseudoColorWidget.h"

#include "ui_PseudoColorWidget.h"
#include "ColorTable.h"
#include <boost/signals2/signal.hpp>

namespace ph  = std::placeholders;
namespace sig = boost::signals2;

typedef std::shared_ptr<ColorTable> SpColorTable;

struct PseudoColorWidget::Impl
{
	PseudoColorWidget*const base;
	Ui::PseudoColorWidget ui;

	std::vector<SpColorTable> colorTables;
	sig::signal<void(double,double)> valuesChanged;

	Impl( PseudoColorWidget*const obj )
		: base( obj )
	{
		ui.setupUi( base );

		ui.minValueSpinBox->connectValueChanged( std::bind( &PseudoColorWidget::Impl::minValueChanged, this, ph::_1 ) );
		ui.maxValueSpinBox->connectValueChanged( std::bind( &PseudoColorWidget::Impl::maxValueChanged, this, ph::_1 ) );
	}

	void minValueChanged( double minValue )
	{
		double maxValue = ui.maxValueSpinBox->value();
		valuesChanged( minValue, maxValue );
	}

	void maxValueChanged( double maxValue )
	{
		double minValue = ui.minValueSpinBox->value();
		valuesChanged( minValue, maxValue );
	}
};

PseudoColorWidget::PseudoColorWidget(QWidget *parent)
	: QWidget(parent)
	, mImpl( new PseudoColorWidget::Impl( this ) )
{

}

PseudoColorWidget::~PseudoColorWidget()
{

}

void 
PseudoColorWidget::connectColorTableChanged( std::function<void(void)> func )
{
	mImpl->ui.colorTableWidget->connectColorTableChanged( func );
}

void
PseudoColorWidget::connectValuesChanged( std::function<void(double,double)> func )
{
	mImpl->valuesChanged.connect( func );
}

void 
PseudoColorWidget::connectAutoScalePressed( std::function<void(void)> func )
{
	mImpl->ui.autoScalePushButton->connectPressed( func );
}

cv::Mat
PseudoColorWidget::convert( cv::InputArray src ) const
{
	double minValue = mImpl->ui.minValueSpinBox->value();
	double maxValue = mImpl->ui.maxValueSpinBox->value();

	return mImpl->ui.colorTableWidget->convert( src, minValue, maxValue );
}

void
PseudoColorWidget::setAutoScale( cv::InputArray src )
{
	double minValue, maxValue;
	cv::minMaxLoc( src, &minValue, &maxValue );

	mImpl->ui.minValueSpinBox->setValue( minValue );
	mImpl->ui.maxValueSpinBox->setValue( maxValue );
}

