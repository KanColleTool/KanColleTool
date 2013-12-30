#ifndef KVPROXYSERVER_H
#define KVPROXYSERVER_H

#include <QTcpServer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class KVProxyServer : public QTcpServer
{
	Q_OBJECT
	
public:
	KVProxyServer(QObject *parent = 0);
	
private slots:
	void onNewConnection();
	void onReadyRead();
	
	void sendProxyRequest(QTcpSocket *requestSocket);
	void writeBackResponse(QNetworkReply *reply, QTcpSocket *socket);
	void onProxyRequestFinished();
	void onProxyRequestError(QNetworkReply::NetworkError error);
	
private:
	QNetworkAccessManager netManager;
};

#endif
