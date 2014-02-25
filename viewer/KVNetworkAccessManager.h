#ifndef KVNETWORKACCESSMANAGER_H
#define KVNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QLocalSocket>

class QNetworkReply;

class KVNetworkAccessManager : public QNetworkAccessManager {
	Q_OBJECT

public:
	explicit KVNetworkAccessManager(QObject *parent = 0);
	void sendToTool(const QByteArray &data, const QString &path);

protected:
	QNetworkReply *createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData);
	QLocalSocket toolSock;
};

#endif // KVNETWORKACCESSMANAGER_H
