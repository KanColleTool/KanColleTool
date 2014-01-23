#ifndef KVNETWORKACCESSMANAGER_H
#define KVNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QIODevice>

class KVNetworkAccessManager : public QNetworkAccessManager
{
public:
	KVNetworkAccessManager(QObject *parent = 0);
	~KVNetworkAccessManager();
	
	QNetworkReply* createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice *outgoingData = 0);
	
private slots:
	void innerRequestFinished();
	
private:
	QNetworkAccessManager innerManager;
};

#endif
