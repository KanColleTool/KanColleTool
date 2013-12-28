#include "KVProxyServer.h"
#include <QUrl>

// Debug level!
// 0 = Quiet
// 1 = Log Events
// 2 =   + HTTP Headers
// 3 =   + Body Data
#define kProxyVerboseLevel 0

KVProxyServer::KVProxyServer(QObject *parent):
	QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

KVProxyServer::~KVProxyServer()
{
	
}

void KVProxyServer::onNewConnection()
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "> New Connection!";
	
	QTcpSocket *socket = this->nextPendingConnection();
	connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

void KVProxyServer::onReadyRead()
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "- Ready Read!";
	
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	
	QTcpSocket *proxySocket = new QTcpSocket(this);
	connect(proxySocket, SIGNAL(readyRead()), this, SLOT(onProxySocketReadyRead()));
	connect(proxySocket, SIGNAL(connected()), this, SLOT(onProxySocketConnected()));
	connect(proxySocket, SIGNAL(disconnected()), this, SLOT(onProxySocketDisconnected()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
	
	KVHttpPacket request(socket->readAll());
	
	packetsByProxySocket.insert(proxySocket, request);
	socketsByProxySocket.insert(proxySocket, socket);
	
	proxySocket->connectToHost(request.headers.value("Host"), 80);
}

void KVProxyServer::onError(QAbstractSocket::SocketError socketError)
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "> Error:" << socketError;
	
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	
	socket->disconnectFromHost();
}

void KVProxyServer::onProxySocketConnected()
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "-> Proxy Socket Connected";
	
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
	KVHttpPacket &request = packetsByProxySocket[socket];	//.value() doesn't give T&
	
	qDebug() << request.toLatin1();
	socket->write(request.toLatin1());
}

void KVProxyServer::onProxySocketDisconnected()
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "<- Proxy Socket Disconnected";
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	
	socketsByProxySocket.remove(proxySocket);
	packetsByProxySocket.remove(proxySocket);
}

void KVProxyServer::onProxySocketReadyRead()
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "  -> Proxy Socket Ready to Read!";
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	QTcpSocket *socket = socketsByProxySocket.value(proxySocket);
	
	QByteArray data = proxySocket->readAll();
	if(kProxyVerboseLevel >= 2)
	{
		qDebug() << data.left(data.indexOf("\r\n\r\n"));
		
		if(kProxyVerboseLevel >= 3)
		{
			KVHttpPacket packet(data);
			if(packet.headers.value("Content-Type").startsWith("text/"))
				qDebug() << packet.body;
			else
				qDebug() << packet.body.toBase64();
		}
	}
	socket->write(data);
	
	if(kProxyVerboseLevel >= 2)
		qDebug() << "  <- Response Delivered";
	
	proxySocket->disconnectFromHost();
	socket->disconnectFromHost();
}

void KVProxyServer::onProxySocketError(QAbstractSocket::SocketError socketError)
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "  -> Error:" << socketError;
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	QTcpSocket *socket = socketsByProxySocket.value(proxySocket);
	
	proxySocket->disconnectFromHost();
	socket->disconnectFromHost();
}
