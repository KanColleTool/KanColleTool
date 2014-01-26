#include "KCToolServer.h"
#include <QTcpSocket>

KCToolServer::KCToolServer(QObject *parent):
	QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

KCToolServer::~KCToolServer()
{
	
}

void KCToolServer::onNewConnection()
{
	while(this->hasPendingConnections())
	{
		QTcpSocket *socket = this->nextPendingConnection();
		connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
	}
}

void KCToolServer::onSocketReadyRead()
{
	
}
