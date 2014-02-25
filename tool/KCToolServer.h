#ifndef KCTOOLSERVER_H
#define KCTOOLSERVER_H

#include <QLocalServer>

class QLocalSocket;
class KCClient;
class KCToolServer : public QLocalServer
{
	Q_OBJECT

public:
	KCToolServer(QObject *parent = 0);
	virtual ~KCToolServer();

	void setClient(KCClient *c);

	bool enabled;

signals:
	void focusRequested();

protected:
	void handleRequest(QLocalSocket *socket);

protected slots:
	void onNewConnection();
	void onSocketReadyRead();

protected:
	KCClient *client;
};

#endif
