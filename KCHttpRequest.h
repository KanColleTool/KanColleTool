#ifndef KCHTTPREQUEST_H
#define KCHTTPREQUEST_H

#include <QByteArray>
#include <QString>
#include <QMap>
#include <QUrl>

class KCHttpRequest
{
public:
	KCHttpRequest(QByteArray data = QByteArray());
	QByteArray toLatin1();
	
	QString method;
	QUrl url;
	QString httpVersion;
	QMap<QString,QString> headers;
	QByteArray body;
};

#endif
