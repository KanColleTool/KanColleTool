#ifndef KVNETWORKACCESSMANAGER_H
#define KVNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

class QNetworkReply;
class KVNetworkAccessManager : public QNetworkAccessManager {
	Q_OBJECT

public:
	explicit KVNetworkAccessManager(QObject *parent = 0);

protected:
	QNetworkReply *createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData);
};

#endif // KVNETWORKACCESSMANAGER_H
