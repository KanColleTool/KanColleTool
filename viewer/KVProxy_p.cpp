#include "KVProxy_p.h"
#include <iostream>
#include <QString>
#include <QRegularExpression>
#include <QPointer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include "KVTranslator.h"

static QPointer<QNetworkAccessManager> manager;

void proxyHandleConnection(KVProxy *proxy, HttpProxy::Connection::Ptr con)
{
	std::cout << con->request_method << " " << con->request_path << std::endl;
	
	// Spoof the User-Agent to make us look like Google Chrome
	con->request_headers["User-Agent"].clear();
	con->request_headers["User-Agent"].push_back("Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36");
	
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
	QString body = QString::fromStdString(res.body);
	QString tlBody = KVTranslator::instance()->translateJson(body);
	con->reply(res.status_code, res.status_message, res.headers, tlBody.toStdString());
	
	QUrl toolUrl("http://localhost:54321/");
	QUrl url(QString::fromStdString(con->request_path));
	QNetworkRequest request(toolUrl.resolved(url));
	request.setRawHeader("Content-Type", "text/json");
	
	if(!manager)
		manager = new QNetworkAccessManager(proxy);
	manager->post(request, body.toUtf8());
}
