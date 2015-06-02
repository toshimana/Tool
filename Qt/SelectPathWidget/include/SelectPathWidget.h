#ifndef SELECTPATHWIDGET_H
#define SELECTPATHWIDGET_H

#include <QWidget>

class SelectPathWidget : public QWidget
{
	Q_OBJECT

public:
	SelectPathWidget( QWidget *parent = 0);
	virtual ~SelectPathWidget();

	void
	setLabel( const std::string& label );

	std::string
	getPath( void ) const;

	void
	setPath( const std::string& path );

	void
	setPath( const QString& path );

protected:

private slots:
	virtual void on_selectButton_pressed( void ) = 0;

private:
	struct Impl;
	std::unique_ptr<Impl>  mImpl;
};

#endif // SELECTPATHWIDGET_H
