#include "KCProxyServer.h"
#include "KCClient.h"
#include <QUrl>

KCProxyServer::KCProxyServer(KCClient *client, QObject *parent):
	QTcpServer(parent), client(client)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

KCProxyServer::~KCProxyServer()
{
	
}

void KCProxyServer::onNewConnection()
{
	qDebug() << "> New Connection!";
	QTcpSocket *socket = this->nextPendingConnection();
	connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

void KCProxyServer::onReadyRead()
{
	qDebug() << "- Ready Read!";
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	
	QTcpSocket *proxySocket = new QTcpSocket(this);
	connect(proxySocket, SIGNAL(readyRead()), this, SLOT(onProxySocketReadyRead()));
	connect(proxySocket, SIGNAL(connected()), this, SLOT(onProxySocketConnected()));
	connect(proxySocket, SIGNAL(disconnected()), this, SLOT(onProxySocketDisconnected()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
	
	KCHttpPacket request(socket->readAll());
	
	packetsByProxySocket.insert(proxySocket, request);
	socketsByProxySocket.insert(proxySocket, socket);
	
	proxySocket->connectToHost(client->server, 80);
}

void KCProxyServer::onError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "> Error:" << socketError;
	
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	
	socket->disconnectFromHost();
}

void KCProxyServer::onProxySocketConnected()
{
	qDebug() << "-> Proxy Socket Connected";
	
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	KCHttpPacket &request = packetsByProxySocket[socket];	//.value() doesn't give T&
	
	// Patch up the request to make it look right
	request.headers.insert("Host", client->server);
	qDebug() << "   -- Spoofed Host:" << request.headers.value("Host");
	if(request.headers.contains("Referer"))
	{
		QUrl referer(request.headers.value("Referer"));
		referer.setHost(client->server);
		request.headers.insert("Referer", referer.toString());
		qDebug() << "   -- Spoofed Referer:" << request.headers.value("Referer");
	}
	
	qDebug() << request.toLatin1();
	socket->write(request.toLatin1());
}

void KCProxyServer::onProxySocketDisconnected()
{
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	
	qDebug() << "<- Proxy Socket Disconnected";
	
	socketsByProxySocket.remove(proxySocket);
	packetsByProxySocket.remove(proxySocket);
}

void KCProxyServer::onProxySocketReadyRead()
{
	qDebug() << "  -> Proxy Socket Ready to Read!";
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	QTcpSocket *socket = socketsByProxySocket.value(proxySocket);
	
	QByteArray data = proxySocket->readAll();
	qDebug() << data.left(data.indexOf("\r\n\r\n"));
	socket->write(data);
	
	qDebug() << "  <- Response Delivered";
	
	proxySocket->disconnectFromHost();
	socket->disconnectFromHost();
}

void KCProxyServer::onProxySocketError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "  -> Error:" << socketError;
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	QTcpSocket *socket = socketsByProxySocket.value(proxySocket);
	
	proxySocket->disconnectFromHost();
	socket->disconnectFromHost();
}
