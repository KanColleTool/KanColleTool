#include "KVProxy.h"
#include <iostream>

KVProxy::KVProxy(QObject *parent) :
	QObject(parent), p("127.0.0.1", 0)
{
	// Set up the poll timer
	connect(&pollTimer, SIGNAL(timeout()), this, SLOT(poll()));
	
	// Set up the proxy
	p.on_connection([](HttpProxy::Connection::Ptr c) {
		std::cout << c->request_method << " " << c->request_path << std::endl;
		c->forward();
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
		pollTimer.start(0);
	else
		p.run();
}

void KVProxy::poll()
{
	p.poll();
}
