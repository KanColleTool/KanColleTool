#ifndef KVPROXYSERVER_H
#define KVPROXYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "KVHttpPacket.h"

class KVProxyServer : public QTcpServer
{
	Q_OBJECT
	
public:
	KVProxyServer(QObject *parent = 0);
	virtual ~KVProxyServer();
	
	QString server, apiToken;
	
protected slots:
	void onNewConnection();
	void onReadyRead();
	void onError(QAbstractSocket::SocketError socketError);
	
	void onProxySocketReadyRead();
	void onProxySocketConnected();
	void onProxySocketDisconnected();
	void onProxySocketError(QAbstractSocket::SocketError socketError);
	
private:
	QMap<QTcpSocket*, QTcpSocket*> socketsByProxySocket;
	QMap<QTcpSocket*, KVHttpPacket> packetsByProxySocket;
};

#endif
