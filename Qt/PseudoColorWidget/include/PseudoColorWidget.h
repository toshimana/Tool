#ifndef PSEUDOCOLORWIDGET_H
#define PSEUDOCOLORWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>

#include <functional>

class PseudoColorWidget : public QWidget
{
	Q_OBJECT

public:
	PseudoColorWidget(QWidget *parent = 0);
	~PseudoColorWidget();

	void connectColorTableChanged( std::function<void(void)> func );
	void connectValuesChanged( std::function<void(double,double)> func );
	void connectAutoScalePressed( std::function<void(void)> func );

	cv::Mat convert( cv::InputArray src ) const;
	void setAutoScale( cv::InputArray src );

private:
	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

#endif // PSEUDOCOLORWIDGET_H
