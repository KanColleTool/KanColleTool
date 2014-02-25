#include "KVNetworkAccessManager.h"

#include <QDebug>

#include "KVNetworkReply.h"

KVNetworkAccessManager::KVNetworkAccessManager(QObject *parent) :
	QNetworkAccessManager(parent)
{

}

QNetworkReply *KVNetworkAccessManager::createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData)
{
	QNetworkRequest request = req;
	request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36");

	if(request.url().host() != "localhost" && request.url().host() != "127.0.0.1")
	{
		if(op == QNetworkAccessManager::PostOperation)
		{
			qDebug() << "POST" << request.url().path();
			QNetworkReply *r = QNetworkAccessManager::createRequest(op, request, outgoingData);
			KVNetworkReply *reply = new KVNetworkReply(r->parent(), r, this);
			return reply;
		}
	}

	QNetworkReply *reply = QNetworkAccessManager::createRequest(op, request, outgoingData);
	return reply;
}
