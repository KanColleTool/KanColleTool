#ifndef KCTOOLSERVER_H
#define KCTOOLSERVER_H

#include <QTcpServer>

class KCToolServer : public QTcpServer
{
	Q_OBJECT
	
public:
	KCToolServer(QObject *parent = 0);
	virtual ~KCToolServer();
	
private slots:
	void onNewConnection();
	void onSocketReadyRead();
};

#endif
