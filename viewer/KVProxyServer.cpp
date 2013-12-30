#include "KVProxyServer.h"
#include <QUrl>
#include <QBuffer>
#include <QTcpSocket>
#include <QDebug>

#define kProxyDebug 0

KVProxyServer::KVProxyServer(QObject *parent):
	QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void KVProxyServer::onNewConnection()
{
	if(kProxyDebug)	qDebug() << "-> New Connection";
	
	QTcpSocket *socket = this->nextPendingConnection();
	connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	
	socket->setProperty("firstLineRead", false);
	socket->setProperty("headersRead", false);
	
	socket->setProperty("method", QString());
	socket->setProperty("url", QUrl());
	socket->setProperty("headers", QVariantMap());
	socket->setProperty("body", QByteArray());
}

void KVProxyServer::onReadyRead()
{
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	if(socket->bytesAvailable() && !socket->property("firstLineRead").toBool())
	{
		if(kProxyDebug)	qDebug() << "  -- Reading First Line...";
		QString line = socket->readLine();
		int spIndex1 = line.indexOf(" ");
		int spIndex2 = line.indexOf(" ", spIndex1+1);
		socket->setProperty("method", line.left(spIndex1));
		socket->setProperty("url", QUrl(line.mid(spIndex1 + 1, spIndex2 - spIndex1 - 1)));
		if(kProxyDebug)	qDebug() << socket->property("method");
		if(kProxyDebug)	qDebug() << socket->property("url");
		socket->setProperty("firstLineRead", true);
	}
	if(socket->bytesAvailable() && !socket->property("headersRead").toBool())
	{
		if(kProxyDebug)	qDebug() << "  -- Reading Headers...";
		QVariantMap headers = socket->property("headers").toMap();
		while(socket->canReadLine())
		{
			QString line = socket->readLine().trimmed();
			if(!line.isEmpty())
			{
				int sepIndex = line.indexOf(": ");
				QString key = line.left(sepIndex);
				QString value = line.mid(sepIndex + 2);
				headers.insert(key, value);
			}
			else
			{
				socket->setProperty("headersRead", true);
				break;
			}
		}
		
		socket->setProperty("headers", headers);
		if(kProxyDebug)	qDebug() << socket->property("headers");
	}
	
	if(socket->property("headersRead").toBool())
	{
		if(socket->bytesAvailable())
		{
			if(kProxyDebug)	qDebug() << "  -- Reading" << socket->bytesAvailable() << "bytes of body data...";
			
			QByteArray body = socket->property("body").toByteArray();
			body.append(socket->readAll());
			socket->setProperty("body", body);
			
			if(kProxyDebug)	qDebug() << "  -- Complete!";
			int contentLength = socket->property("headers").toMap().value("Content-Length").toInt();
			if(body.size() >= contentLength)
				this->sendProxyRequest(socket);
		}
		else
		{
			if(kProxyDebug)	qDebug() << "    -- No Body";
			this->sendProxyRequest(socket);
		}
	}
}

void KVProxyServer::sendProxyRequest(QTcpSocket *requestSocket)
{
	QNetworkRequest request(requestSocket->property("url").toUrl());
	request.setOriginatingObject(requestSocket);
	
	QVariantMap headers = requestSocket->property("headers").toMap();
	foreach(QString key, headers.keys())
		request.setRawHeader(key.toLatin1(), headers.value(key).toString().toLatin1());
	
	// Unset default headers
	request.setRawHeader("Connection", QByteArray());
	request.setRawHeader("Accept-Encoding", QByteArray());
	request.setRawHeader("Accept-Language", QByteArray());
	request.setRawHeader("User-Agent", QByteArray());
	
    //QByteArray body = requestSocket->property("body").toByteArray();
    //QBuffer buffer(&body);
    QBuffer *buffer = new QBuffer(this);
    buffer->setData(requestSocket->property("body").toByteArray());
    
    QNetworkReply *reply = netManager.sendCustomRequest(request, requestSocket->property("method").toString().toLatin1(), buffer);
    connect(reply, SIGNAL(finished()), this, SLOT(onProxyRequestFinished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onProxyRequestError(QNetworkReply::NetworkError)));
    
    connect(reply, SIGNAL(finished()), buffer, SLOT(deleteLater()));
	
	if(kProxyDebug)	qDebug() << "  -> Proxy Request Sent";
}

void KVProxyServer::writeBackResponse(QNetworkReply *reply, QTcpSocket *socket)
{
	socket->write("HTTP/1.1 ");
	socket->write(QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()).toLatin1());
	socket->write(" ");
	socket->write(reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString().toLatin1());
	socket->write("\r\n");
	
	foreach(QNetworkReply::RawHeaderPair header, reply->rawHeaderPairs())
	{
		if(header.first == "Content-Encoding")
			continue;
		else if(header.first == "Transfer-Encoding")
			continue;
		else if(header.first == "Connection")
			continue;
		else
		{
			socket->write(header.first);
			socket->write(": ");
			socket->write(header.second);
			socket->write("\r\n");
		}
	}
	socket->write("Connection: close\r\n");
	socket->write("\r\n");
	socket->write(reply->readAll());
	socket->disconnectFromHost();
	
	if(kProxyDebug)	qDebug() << "<- Response Written";
}

void KVProxyServer::onProxyRequestFinished()
{
	if(kProxyDebug)	qDebug() << "    -- Finished";
	
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(reply->request().originatingObject());
	
	writeBackResponse(reply, socket);
}

void KVProxyServer::onProxyRequestError(QNetworkReply::NetworkError error)
{
	if(kProxyDebug)	qDebug() << "    -x Error:" << error;
	
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(reply->request().originatingObject());
	
	writeBackResponse(reply, socket);
}
