#ifndef KCCLIENT_H
#define KCCLIENT_H

#include <QObject>
#include <QJsonValue>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class KCShip;
class KCShipMaster;
class KCFleet;
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
	
	QMap<int, KCShipMaster*> masterShips;
	QMap<int, KCShip*> ships;
	QMap<int, KCFleet*> fleets;
	
	bool hasCredentials();
	
signals:
	void credentialsGained();
	void receivedMasterShips();
	void receivedPlayerShips();
	void receivedPlayerFleets();
	void requestError(KCClient::ErrorCode error);
	
public slots:
	void setCredentials(QString server, QString apiToken);
	
	void requestMasterShips();
	void requestPlayerShips();
	void requestPlayerFleets();
	
protected slots:
	void onMasterShipsRequestFinished();
	void onPlayerShipsRequestFinished();
	void onPlayerFleetsRequestFinished();
	
	void processMasterShipsData(QVariant data);
	void processPlayerShipsData(QVariant data);
	void processPlayerFleetsData(QVariant data);
	
protected:
	QNetworkReply* call(QString endpoint, QUrlQuery params = QUrlQuery());
	QUrl urlForEndpoint(QString endpoint);
	QVariant dataFromRawResponse(QString text, ErrorCode *error = 0);
	
protected:
	QNetworkAccessManager *manager;
};

#endif // KCCLIENT_H
