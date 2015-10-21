#ifndef QTSJIS_H
#define QTSJIS_H

#include <QTextCodec>

namespace qtsjis
{ 
	// QString( SJIS )��std::string( UNICODE )�̑��ݕϊ��c�[��

	static std::string
	toString( const QString& qstr )
	{
		return QTextCodec::codecForName("SJIS")->fromUnicode( qstr ).constData();
	}

	static QString
	toQString( const std::string& str )
	{
		return QTextCodec::codecForName("SJIS")->toUnicode( str.c_str(), str.length() );
	}
};

#endif // QTSJIS_H