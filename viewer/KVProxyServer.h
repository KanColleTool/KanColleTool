#ifndef KVPROXYSERVER_H
#define KVPROXYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJSEngine>
#include "KVHttpPacket.h"

class KVProxyServer : public QTcpServer
{
	Q_OBJECT
	
public:
	enum APIStatus {
		OK = 1,
		ExpiredAPIToken = 100,
		InvalidVersion = 200,
		Unauthorized = 201
	};
	
	KVProxyServer(QObject *parent = 0);
	virtual ~KVProxyServer();
	
	QString server, apiToken;
	
signals:
	void apiError(KVProxyServer::APIStatus error, QString message);
	
protected slots:
	void onNewConnection();
	void onReadyRead();
	void onError(QAbstractSocket::SocketError socketError);
	
	void onProxySocketReadyRead();
	void onProxySocketConnected();
	void onProxySocketDisconnected();
	void onProxySocketError(QAbstractSocket::SocketError socketError);
	
	void handleResponse(KVHttpPacket *response, const KVHttpPacket *request);
	
private:
	QMap<QTcpSocket*, QTcpSocket*> socketsByProxySocket;
	QMap<QTcpSocket*, KVHttpPacket> requestsByProxySocket;
	QMap<QTcpSocket*, KVHttpPacket> responsesByProxySocket;
	
	QJSEngine jsEngine;
	QJSValue loadJSFile(QString path);
};

#endif
