#ifndef KVPROXYWRAPPER_H
#define KVPROXYWRAPPER_H

#include <QObject>
#include <QTimer>
#include <proxy.hpp>

class KVProxy : public QObject
{
	Q_OBJECT
public:
	KVProxy(QObject *parent = 0, unsigned short port = 0);
	virtual ~KVProxy();
	
	int port();
	void run(bool async = true);
	
private slots:
	void poll();
	
private:
	HttpProxy p;
	QTimer pollTimer;
};

#endif
