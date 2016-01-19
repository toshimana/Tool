#ifndef INDEXBARWIDGET_H
#define INDEXBARWIDGET_H

#include <QWidget>
#include <memory>
#include <functional>

class IndexBarWidget : public QWidget
{
	Q_OBJECT

public:
	IndexBarWidget(QWidget *parent = 0);
	~IndexBarWidget();

	void setMaximum( int maxSize );

	void connectChangedIndex( std::function<void(int)> func );

private slots:
	void valueChanged( int value );

private:
	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

#endif // INDEXBARWIDGET_H
