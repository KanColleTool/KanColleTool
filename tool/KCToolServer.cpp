#include "KCToolServer.h"
#include <QTcpSocket>
#include "KCClient.h"

KCToolServer::KCToolServer(KCClient *client, QObject *parent):
	QTcpServer(parent), client(client)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

KCToolServer::~KCToolServer()
{
	
}

void KCToolServer::handleRequest(QTcpSocket *socket)
{
	QString path = socket->property("path").toString();
	QByteArray content = socket->property("buffer").toByteArray();
	
	QVariant data = client->dataFromRawResponse(content);
	if(path == "/api_get_member/ship")
		client->_processPlayerShipsData(data);
	else
	{
		qDebug() << "Dunno what to do about" << path;
		reply(socket, 404, "Not Found");
	}
	
	reply(socket, 200, "OK");
}

void KCToolServer::reply(QTcpSocket *socket, int code, QString message)
{
	socket->write(QString("HTTP/1.1 %1 %1\r\n").arg(QString::number(code), message).toUtf8());
	socket->write(QString("Date: %1\r\n").arg(QDateTime::currentDateTime().toString(Qt::RFC2822Date)).toUtf8());
	socket->write(QString("Content-Length: 0\r\n").toUtf8());
	socket->write(QString("\r\n").toUtf8());
}

void KCToolServer::onNewConnection()
{
	while(this->hasPendingConnections())
	{
		QTcpSocket *socket = this->nextPendingConnection();
		connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
	}
}

void KCToolServer::onSocketReadyRead()
{
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	
	// Parse the first line
	if(!socket->property("firstLineRead").toBool())
	{
		QString line(socket->readLine());
		int sepPos1(line.indexOf(" "));
		int sepPos2(line.indexOf(" ", sepPos1+1));
		QString method(line.left(sepPos1));
		QString path(line.mid(sepPos1+1, sepPos2 - sepPos1 - 1));
		socket->setProperty("method", method);
		socket->setProperty("path", path);
	}
	
	// Parse Headers!
	int contentLength = -1;
	if(!socket->property("headerRead").toBool())
	{
		QVariantMap headers(socket->property("headers").toMap());
		
		while(socket->canReadLine())
		{
			QString line = QString(socket->readLine()).trimmed();
			
			// The header section is terminated by an empty line
			if(line == "")
			{
				socket->setProperty("headerRead", true);
				break;
			}
			
			// Split it up
			int sepPos(line.indexOf(":"));
			QString key(line.left(sepPos).trimmed());
			QString val(line.mid(sepPos+1).trimmed());
			headers.insertMulti(key, val);
			
			// Check for the Content-Length header
			if(key == "Content-Length")
				contentLength = val.toInt();
		}
		
		socket->setProperty("headers", headers);
	}
	
	// Read the body into a buffer
	if(socket->bytesAvailable())
	{
		QByteArray buffer(socket->property("buffer").toByteArray());
		buffer.append(socket->readAll());
		socket->setProperty("buffer", buffer);
		
		// If this is a later chunk, check the old Content-Length header
		if(contentLength == -1)
			contentLength = socket->property("headers").toMap().value("Content-Length").toInt();
		
		// If we have a Content-Length (toLong() fails with 0), disconnect after that
		if(contentLength > 0 && buffer.size() >= contentLength)
		{
			qDebug() << "Content-Length hit!";
			this->handleRequest(socket);
			socket->close();
		}
	}
}
