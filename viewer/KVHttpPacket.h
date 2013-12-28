#ifndef KVHTTPPACKET_H
#define KVHTTPPACKET_H

#include <QByteArray>
#include <QString>
#include <QMap>
#include <QUrl>

class KVHttpPacket
{
public:
	KVHttpPacket(QByteArray data = QByteArray());
	QByteArray toLatin1(bool headersOnly = false);
	QString toString(bool headersOnly = false);
	
	QString method;
	QUrl url;
	QString httpVersion;
	QMap<QString,QString> headers;
	QByteArray body;
};

#endif
