#ifndef KCHTTPPACKET_H
#define KCHTTPPACKET_H

#include <QByteArray>
#include <QString>
#include <QMap>
#include <QUrl>

class KCHttpPacket
{
public:
	KCHttpPacket(QByteArray data = QByteArray());
	QByteArray toLatin1();
	
	QString method;
	QUrl url;
	QString httpVersion;
	QMap<QString,QString> headers;
	QByteArray body;
};

#endif
