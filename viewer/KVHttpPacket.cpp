#include "KVHttpPacket.h"
#include <QUrl>
#include <QDebug>

KVHttpPacket::KVHttpPacket(QByteArray data)
{
	// The header ends with a blank line, which really just looks like "\r\n\r\n".
	int headerLength = data.indexOf("\r\n\r\n");
	
	// Parse the header part; every line is separated by "\r\n"
	QString header(data.left(headerLength));
	QList<QString> lines = header.split("\r\n");
	
	bool isFirstLine = true;
	foreach(QString line, lines)
	{
		// The first line is in the form of:
		// <METHOD> <url> HTTP/1.x
		if(isFirstLine)
		{
			// If it starts with "HTTP", it's a response
			isResponse = line.startsWith("HTTP");
			
			int spIndex1 = line.indexOf(' ');
			int spIndex2 = line.indexOf(' ', spIndex1 + 1);
			
			if(isResponse)
			{
				httpVersion = line.left(spIndex1);
				statusCode = line.mid(spIndex1 + 1, spIndex2 - spIndex1 - 1).toInt();
				statusMessage = line.mid(spIndex2 + 1);
			}
			else
			{
				method = line.left(spIndex1);
				url = QUrl(line.mid(spIndex1 + 1, spIndex2 - spIndex1 - 1));
				httpVersion = line.mid(spIndex2 + 1);
				
				// cURL does strange things with the path part, not sure if it's
				// a part of the HTTP spec I missed, but I'm not gonna reread it
				// to find out. Basically, it passes the full URL, not just path.
				if(!url.host().isEmpty())
				{
					headers.insert("Host", url.host());
					url = QUrl(url.path());
				}
			}
			
			isFirstLine = false;
		}
		// Every other line is just headers, in the form of
		// <Header>: <value>
		else
		{
			int separatorIndex = line.indexOf(": ");
			QString key = line.left(separatorIndex);
			QString value = line.mid(separatorIndex+2);
			this->headers.insert(key, value);
		}
	}
	
	// Save the body too (+4 for \r\n\r\n)
	body = data.mid(headerLength + 4);
}

QByteArray KVHttpPacket::toLatin1(bool headersOnly) const
{
	QByteArray data;
	
	// First Line
	if(isResponse)
	{
		data += httpVersion.toLatin1();
		data += " ";
		data += QString::number(statusCode).toLatin1();
		data += " ";
		data += statusMessage.toLatin1();
	}
	else
	{
		data += method.toLatin1();
		data += " ";
		data += url.toString().toLatin1();
		data += " ";
		data += httpVersion.toLatin1();
		data += "\r\n";
	}
	
	// Headers
	foreach(QString key, headers.keys())
	{
		data += key.toLatin1();
		data += ": ";
		data += headers.value(key).toLatin1();
		data += "\r\n";
	}
	
	if(!headersOnly)
	{
		// Body
		data += "\r\n";
		data += body;
	}
	
	return data;
}

QString KVHttpPacket::toString(bool headersOnly) const
{
	QString str(this->toLatin1(true));
	if(!headersOnly)
	{
		str += "\r\n";
		if(!this->headers.value("Content-Type").startsWith("text/"))
			str += this->body.toBase64();
		else
			str += this->body;
	}
	
	return str;
}
