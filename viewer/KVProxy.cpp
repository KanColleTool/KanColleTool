#include "KVProxy.h"
#include "KVProxy_p.h"
#include <iostream>
#include <string>

KVProxy::KVProxy(QObject *parent, unsigned short port) :
	QObject(parent), p("127.0.0.1", port)
{
	// Make the poll timer tell the proxy to poll; this will be started with
	// a timeout of 0, so it will effectively poll on every event loop tick
	connect(&pollTimer, SIGNAL(timeout()), this, SLOT(poll()));
	
	// Pass on new connections to a function in KVProxy_p
	p.on_connection([this](HttpProxy::Connection::Ptr con) {
		proxyHandleConnection(this, con);
	});

	p.on_error([](std::string str, bool){
		qDebug() << "Proxy Error: " << str.c_str();
	});
}

KVProxy::~KVProxy()
{
	
}

int KVProxy::port()
{
	return p.get_local_port_number();
}

void KVProxy::run(bool async)
{
	if(async)
		pollTimer.start(20);
	else
		p.run();
}

void KVProxy::poll()
{
	p.poll();
}
