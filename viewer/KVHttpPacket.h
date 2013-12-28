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
	QByteArray toLatin1(bool headersOnly = false) const;
	QString toString(bool headersOnly = false) const;
	
	// Is this a response?
	bool isResponse;
	
	// For Requests
	QString method;
	QUrl url;
	
	// For Responses
	int statusCode;
	QString statusMessage;
	
	// Common to both
	QString httpVersion;
	QMap<QString,QString> headers;
	QByteArray body;
};

#endif
