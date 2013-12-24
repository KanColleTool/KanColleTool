#ifndef KCPROXYSERVER_H
#define KCPROXYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "KCHttpRequest.h"

// TODO: Thread pooling.

class KCClient;
class KCProxyServer : public QTcpServer
{
	Q_OBJECT
	
public:
	KCProxyServer(KCClient *client, QObject *parent = 0);
	virtual ~KCProxyServer();
	
protected slots:
	void onNewConnection();
	void onReadyRead();
	void onError(QAbstractSocket::SocketError socketError);
	
	void onProxySocketReadyRead();
	void onProxySocketConnected();
	void onProxySocketDisconnected();
	void onProxySocketError(QAbstractSocket::SocketError socketError);
	
protected:
	//virtual void incomingConnection(qintptr handle);
	
private:
	QMap<QTcpSocket*, QTcpSocket*> socketsByProxySocket;
	QMap<QTcpSocket*, KCHttpRequest> requestsByProxySocket;
	
	KCClient *client;
};

#endif