#include "KVProxyServer.h"
#include <QUrl>
#include <QMap>
#include <QJsonDocument>
#include <QJsonValue>

// Debug level!
// 0 = Quiet
// 1 = Log Events
// 2 =   + HTTP Headers
// 3 =   + Body Data
#define kProxyVerboseLevel 0

// Be really verbose and print how much has been read and how much is expected
#define kProxyPrintTransferProgress 0

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
	request.headers.insert("Connection", "close");
	
	requestsByProxySocket.insert(proxySocket, request);
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
	KVHttpPacket &request = requestsByProxySocket[socket];	//.value() doesn't give T&
	
	if(kProxyVerboseLevel >= 3)
		qDebug() << request.toLatin1();
	socket->write(request.toLatin1());
}

void KVProxyServer::onProxySocketDisconnected()
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "<- Proxy Socket Disconnected";
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	QTcpSocket *socket = socketsByProxySocket.value(proxySocket);
	
	KVHttpPacket *request = &(requestsByProxySocket[proxySocket]);
	KVHttpPacket *response = &(responsesByProxySocket[proxySocket]);
	
	this->handleResponse(response, request);
	socket->write(response->toLatin1());
	socket->disconnectFromHost();
	
	socketsByProxySocket.remove(proxySocket);
	requestsByProxySocket.remove(proxySocket);
}

void KVProxyServer::onProxySocketReadyRead()
{
	if(kProxyVerboseLevel >= 1)
		qDebug() << "  -> Proxy Socket Ready to Read!";
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	KVHttpPacket *response = &(responsesByProxySocket[proxySocket]);
	
	response->dataReceived(proxySocket->readAll());
	if(response->headers.contains("Content-Length") &&
		response->headers.value("Content-Length").toInt() <= response->body.length())
		proxySocket->disconnectFromHost();
	
	if(kProxyPrintTransferProgress)
		qDebug() << response->body.length() << "Read," << response->headers.value("Content-Length").toInt() << "Expected";
}

void KVProxyServer::onProxySocketError(QAbstractSocket::SocketError error)
{
	if(error == QAbstractSocket::RemoteHostClosedError)
	{
		this->onProxySocketDisconnected();
		return;
	}
	
	if(kProxyVerboseLevel >= 1)
		qDebug() << "  -> Error:" << error;
	
	QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(QObject::sender());
	QTcpSocket *socket = socketsByProxySocket.value(proxySocket);
	
	proxySocket->disconnectFromHost();
	socket->disconnectFromHost();
}

void KVProxyServer::handleResponse(KVHttpPacket *response, const KVHttpPacket *request)
{
	// Only handle text-based packets with the API's path prefix, and the "svdata=" body prefix.
	if(!request->url.path().startsWith("/kcsapi") ||
		!response->headers.value("Content-Type").startsWith("text/") ||
		!response->body.startsWith("svdata="))
		return;
	
	// Make a JSON Document out of everything after the "svdata="
	// Ignore invalid responses, we may have been wrong...
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(response->body.mid(7), &error);
	if(error.error != QJsonParseError::NoError || !doc.isObject())
		return;
	
	// Check for API Error codes
	QMap<QString,QVariant> data = doc.toVariant().toMap();
	APIStatus status = (APIStatus)data.value("api_result").toInt();
	QString msg = data.value("api_result_msg").toString();
	if(status != OK)
		emit apiError(status, msg);
}
