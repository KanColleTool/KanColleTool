#ifndef KVPROXY_P_H
#define KVPROXY_P_H

#include "KVProxy.h"
#include <proxy.hpp>

void proxyHandleConnection(KVProxy *proxy, HttpProxy::Connection::Ptr con);
void proxyHandleResponse(KVProxy *proxy, HttpProxy::Connection::Ptr con, HttpProxy::Response res);

#endif
