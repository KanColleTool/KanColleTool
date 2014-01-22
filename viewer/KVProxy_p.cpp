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
		con->async_get_remote(con->request_headers,
			[proxy](HttpProxy::Connection::Ptr con, HttpProxy::Response res) {
				proxyHandleResponse(proxy, con, res);
			});
	else
		con->forward();
}

void proxyHandleResponse(KVProxy *proxy, HttpProxy::Connection::Ptr con, HttpProxy::Response res)
{
	Q_UNUSED(proxy);
	
	std::cout << "IN:" << std::endl;
	std::cout << res.body << std::endl;
	
	// Regex that matches any JSON string-string key-value pairs
	QRegularExpression re("\"([^\"]+)\"\\s*:\\s*\"([^\"]+)\"");
	
	// Turn the response body into a QString and make an output buffer
	QString str = QString::fromStdString(res.body);
	QString outstr;
	
	// This holds where the last chunk we added ended, so we don't drop things
	int lastEnd = 0;
	
	// Iterate over all the matches!
	QRegularExpressionMatchIterator iter = re.globalMatch(str);
	while(iter.hasNext())
	{
		QRegularExpressionMatch match = iter.next();
		
		// Push the chunk between this match and the last, and update position
		outstr.append(str.mid(lastEnd, match.capturedStart() - lastEnd));
		lastEnd = match.capturedEnd();
		
		QString key = match.captured(1);
		QString value = match.captured(2);
		
		// Translate it!
		value = KVTranslator::instance()->translate(value);
		
		outstr.append(QString("\"%1\":\"%2\"").arg(key, value));
	}
	
	outstr.append(str.mid(lastEnd));
	qDebug() << "OUT:";
	qDebug() << outstr;
	
	con->reply(res.status_code, res.status_message, res.headers, outstr.toStdString());
}
