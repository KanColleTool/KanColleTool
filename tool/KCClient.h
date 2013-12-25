#ifndef KCCLIENT_H
#define KCCLIENT_H

#include <QObject>
#include <QJsonValue>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class KCClient : public QObject
{
	Q_OBJECT
public:
	typedef enum ErrorCode {
		JsonError = -1,
		Unknown = 0,
		NoError = 1,
		InvalidAPIVersion = 200,
		InvalidCredentials = 201
	} ErrorCode;
	
	explicit KCClient(QObject *parent = 0);
	virtual ~KCClient();
	
	QString server, apiToken;
	
	bool hasCredentials();
	
signals:
	void credentialsGained();
	void receivedMasterShips(QList<QVariant> data);
	void receivedPlayerShips(QList<QVariant> data);
	void requestError(KCClient::ErrorCode error);
	
public slots:
	void setCredentials(QString server, QString apiToken);
	
	void requestMasterShips();
	void requestPlayerShips();
	
protected slots:
	void onMasterShipsRequestFinished();
	void onPlayerShipsRequestFinished();
	
protected:
	QNetworkReply* call(QString endpoint, QUrlQuery params = QUrlQuery());
	QUrl urlForEndpoint(QString endpoint);
	QVariant dataFromReplyData(QString text, ErrorCode *error = 0);
	
protected:
	QNetworkAccessManager *manager;
};

#endif // KCCLIENT_H
