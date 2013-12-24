#include "KCProxyThread.h"
#include <QTcpSocket>
#include <QDebug>

KCProxyThread::KCProxyThread(int handle, KCClient *client, QObject *parent):
	QThread(parent), handle(handle), client(client)
{
	
}

KCProxyThread::~KCProxyThread()
{
	
}

void KCProxyThread::run()
{
	QTcpSocket socket;
	if(!socket.setSocketDescriptor(handle))
	{
		qWarning() << "Couldn't set socket descriptor: " << socket.errorString();
		return;
	}
	
	// Wait for the client to send something
	socket.waitForReadyRead(-1);
	
	// Parse the response
	QByteArray data = socket.readAll();
	KCHttpRequest request(data);
	
	// Fetch the actual response
	QByteArray response = this->fetchOriginal(request);
	
	// Disconnect
	socket.disconnectFromHost();
}

QByteArray KCProxyThread::fetchOriginal(KCHttpRequest originalRequest)
{
	QTcpSocket socket;
	socket.connectToHost(client->server, 80);
	return QByteArray();
}
