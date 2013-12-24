#include "KCHttpRequest.h"
#include <QUrl>
#include <QDebug>

KCHttpRequest::KCHttpRequest(QByteArray data)
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
			int spIndex1 = line.indexOf(' ');
			int spIndex2 = line.indexOf(' ', spIndex1 + 1);
			method = line.left(spIndex1);
			url = QUrl(line.mid(spIndex1 + 1, spIndex2 - spIndex1 - 1));
			httpVersion = line.mid(spIndex2 + 1);
			
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

QByteArray KCHttpRequest::toLatin1()
{
	QByteArray data;
	
	// First Line
	data += method.toLatin1();
	data += " ";
	data += url.toString().toLatin1();
	data += " ";
	data += httpVersion.toLatin1();
	data += "\r\n";
	
	// Headers
	foreach(QString key, headers.keys())
	{
		data += key.toLatin1();
		data += ": ";
		data += headers.value(key).toLatin1();
		data += "\r\n";
	}
	
	// Body
	data += "\r\n";
	data += body;
	
	return data;
}
