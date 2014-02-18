#include "KVNetworkAccessManager.h"

#include <QDebug>

#include "KVNetworkReply.h"

KVNetworkAccessManager::KVNetworkAccessManager(QObject *parent) :
	QNetworkAccessManager(parent) {}

QNetworkReply *KVNetworkAccessManager::createRequest(Operation op,
                                                     const QNetworkRequest &req,
                                                     QIODevice *outgoingData)
{
	if(op == QNetworkAccessManager::PostOperation)
	{
		qDebug() << "POST" << req.url().toString();
		QNetworkReply *r = QNetworkAccessManager::createRequest(op, req, outgoingData);
		KVNetworkReply *reply = new KVNetworkReply(r->parent(), r);
		return reply;
	} else if(op == QNetworkAccessManager::GetOperation) {
		qDebug() << "GET" << req.url().toString();
	}

	QNetworkReply *reply = QNetworkAccessManager::createRequest(op, req, outgoingData);
	return reply;
}
