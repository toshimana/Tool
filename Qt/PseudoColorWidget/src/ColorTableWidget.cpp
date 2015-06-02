#include "ColorTableWidget.h"

#include "ui_ColorTableWidget.h"
#include "ColorTableGrayScale.h"
#include "ColorTableColor.h"
#include "ColorTableStepColor.h"

#include <boost/signals2/signal.hpp>

namespace ph = std::placeholders;
namespace sig = boost::signals2;

typedef std::shared_ptr<ColorTable> SpColorTable;

struct ColorTableWidget::Impl
{
	ColorTableWidget*const base;
	Ui::ColorTableWidget ui;

	std::vector<SpColorTable> colorTables;
	sig::signal<void(void)> colorTableChanged;


	Impl( ColorTableWidget*const obj )
		: base( obj )
	{
		ui.setupUi( base );

		// カラーテーブルの登録
		addColorTable( SpColorTable( new ColorTableGrayScale() ) );
		addColorTable( SpColorTable( new ColorTableColor() ) );
		addColorTable( SpColorTable( new ColorTableStepColor() ) );

		// カラーテーブルの種類が変化した時の処理を登録
		ui.colorTableComboBox->connectCurrentIndexChanged( std::bind( &ColorTableWidget::Impl::currentIndexChanged, this, ph::_1 ) );
	}

	void addColorTable( SpColorTable ct )
	{
		colorTables.push_back( ct );
		ui.colorTableComboBox->addItem( tr( ct->getName().c_str() ) );
	}

	void currentIndexChanged( int index )
	{
		colorTableChanged();
	}
};

ColorTableWidget::ColorTableWidget(QWidget *parent)
	: QWidget(parent)
	, mImpl( new ColorTableWidget::Impl( this ) )
{
}

ColorTableWidget::~ColorTableWidget()
{

}

void 
ColorTableWidget::connectColorTableChanged( std::function<void(void)> func )
{
	mImpl->colorTableChanged.connect( func );
}

cv::Mat 
ColorTableWidget::convert( cv::InputArray src, double minValue, double maxValue ) const
{
	SpColorTable spCT = mImpl->colorTables[ mImpl->ui.colorTableComboBox->currentIndex() ];

	return spCT->convert( src, minValue, maxValue );
}
