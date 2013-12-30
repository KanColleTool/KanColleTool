#include "KVProxyServer.h"
#include <QUrl>
#include <QMap>
/*#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>*/
#include <QJSValue>
#include <QJSValueList>
#include <QFile>

// Debug level!
// 0 = Quiet
// 1 = Log Events
// 2 =   + HTTP Headers
// 3 =   + Body Data
#define kProxyVerboseLevel 0

// Be really verbose and print how much has been read and how much is expected
#define kProxyPrintTransferProgress 0

// Print request URLs
#define kProxyPrintRequestURLs 1

#define PERCENT(part, whole) ((int)(part/(float)whole))

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
	
	if(kProxyPrintRequestURLs)
		qDebug() << "->" << request.url.toString();
	
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
	
	qDebug() << "<-" << request->url.toString();
	
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
		qDebug() << "  -> (" << PERCENT(response->body.length(), response->headers.value("Content-Length").toInt()) << "Percent )";
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
	return;
	// Only handle text-based packets with the API's path prefix, and the "svdata=" body prefix.
	if(!request->url.path().startsWith("/kcsapi") ||
		!response->headers.value("Content-Type").startsWith("text/") ||
		!response->body.startsWith("svdata="))
		return;
	
	qDebug() << response->body;
	
	QJSValue data = jsEngine.evaluate(response->body);
	
	QJSValue func = this->loadJSFile(":/test.js");
	QJSValueList args;
	args.append(data);
	QJSValue val = func.call(args);
	
	if(!val.isError())
		response->body = QString("svdata=%1").arg(val.toString().replace("\\\\u", "\\u")).toLatin1();
	else
		qWarning() << "ERROR:" << val.toString();
	qDebug() << response->body;
}

QJSValue KVProxyServer::loadJSFile(QString path)
{
	QFile file(path);
	if(!file.open(QIODevice::ReadOnly))
	{
		qWarning() << "Can't open" << path << "for reading";
		return QJSValue();
	}
	
	return jsEngine.evaluate(file.readAll(), path);
}
