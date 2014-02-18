#include <QDebug>

#include "KVNetworkAccessManager.h"

KVNetworkAccessManager::KVNetworkAccessManager(QObject *parent) :
	QNetworkAccessManager(parent) {}

QNetworkReply *KVNetworkAccessManager::createRequest(Operation op,
                                                     const QNetworkRequest &req,
                                                     QIODevice *outgoingData)
{
	switch(op)
	{
	case QNetworkAccessManager::PostOperation:
		qDebug() << "POST" << req.url().toString();
		break;
	case QNetworkAccessManager::GetOperation:
		qDebug() << "GET" << req.url().toString();
		break;
	default:
		break;
	}

	QNetworkReply *reply = QNetworkAccessManager::createRequest( op, req, outgoingData );
	return reply;
}
