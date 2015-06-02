#ifndef COLORTABLEWIDGET_H
#define COLORTABLEWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <functional>

class ColorTableWidget : public QWidget
{
	Q_OBJECT

public:
	ColorTableWidget(QWidget *parent = 0);
	~ColorTableWidget();

	void connectColorTableChanged( std::function<void(void)> func );

	cv::Mat convert( cv::InputArray src, double minValue, double maxValue ) const;

private:
	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

#endif // COLORTABLEWIDGET_H
