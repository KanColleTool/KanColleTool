#include "KVNetworkAccessManager.h"
#include "KVNetworkReply.h"

KVNetworkAccessManager::KVNetworkAccessManager(QObject *parent):
	QNetworkAccessManager(parent)
{
	
}

KVNetworkAccessManager::~KVNetworkAccessManager()
{
	
}

QNetworkReply* KVNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice *outgoingData)
{
	if(op != QNetworkAccessManager::PostOperation)
	{
		qDebug() << "Ignoring:" << req.url();
		return QNetworkAccessManager::createRequest(op, req, outgoingData);
	}
	else
	{
		qDebug() << "Tampering:" << req.url();
		
		// Create a real reply using the superclass' implementation of this, then
		// wrap it up in our custom reply class that'll meddle with the response.
		QNetworkReply *innerReply = QNetworkAccessManager::createRequest(op, req, outgoingData);
		KVNetworkReply *substituteReply = new KVNetworkReply(innerReply, this);
		
		return substituteReply;
	}
}
