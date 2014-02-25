#ifndef KCTOOLSERVER_H
#define KCTOOLSERVER_H

#include <QTcpServer>

class QTcpSocket;
class KCClient;
class KCToolServer : public QTcpServer {
	Q_OBJECT

public:
	KCToolServer(QObject *parent = 0);
	virtual ~KCToolServer();

	void setClient(KCClient *c);

	bool enabled;

protected:
	void handleRequest(QTcpSocket *socket);

protected slots:
	void onNewConnection();
	void onSocketReadyRead();

protected:
	KCClient *client;
};

#endif
