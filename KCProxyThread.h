#ifndef KCPROXYTHREAD_H
#define KCPROXYTHREAD_H

#include <QThread>
#include "KCClient.h"
#include "KCHttpRequest.h"

class KCProxyThread : public QThread
{
public:
	KCProxyThread(int handle, KCClient *client, QObject *parent = 0);
	virtual ~KCProxyThread();
	
	virtual void run();
	
protected:
	QByteArray fetchOriginal(KCHttpRequest originalRequest);
	
	int handle;
	KCClient *client;
};

#endif