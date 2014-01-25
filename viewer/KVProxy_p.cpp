#include "KVProxy_p.h"
#include <iostream>
#include <QString>
#include <QRegularExpression>
#include <QDebug>
#include "KVTranslator.h"

void proxyHandleConnection(KVProxy *proxy, HttpProxy::Connection::Ptr con)
{
	std::cout << con->request_method << " " << con->request_path << std::endl;
	
	if(con->request_method == "POST")
	{
		std::cout << "> " << con->request_path << std::endl;
		con->async_get_remote(con->request_headers,
			[proxy](HttpProxy::Connection::Ptr con, HttpProxy::Response res) {
				proxyHandleResponse(proxy, con, res);
			});
	}
	else
	{
		std::cout << "= " << con->request_path << std::endl;
		con->forward();
	}
}

void proxyHandleResponse(KVProxy *proxy, HttpProxy::Connection::Ptr con, HttpProxy::Response res)
{
	Q_UNUSED(proxy);
	
	QString body = QString::fromStdString(res.body);
	body = KVTranslator::instance()->translateJson(body);
	con->reply(res.status_code, res.status_message, res.headers, body.toStdString());
}
