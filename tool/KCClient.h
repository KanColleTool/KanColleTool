#ifndef KCCLIENT_H
#define KCCLIENT_H

#include <QObject>
#include <QJsonValue>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "KCWrapperUtils.h"
#include "KCShipMaster.h"
#include "KCShip.h"
#include "KCFleet.h"
#include "KCDock.h"

class KCToolServer;
class KCClient : public QObject
{
	Q_OBJECT
	friend class KCToolServer;

public:
	typedef enum ErrorCode {
		JsonError = -1,
		Unknown = 0,
		NoError = 1,
		InvalidAPIVersion = 200,
		InvalidCredentials = 201,
		ExpiredAPIToken = 202
	} ErrorCode;

	explicit KCClient(QObject *parent = 0);
	virtual ~KCClient();

	QString server, apiToken;

	QMap<int, KCShipMaster*> masterShips;
	QMap<int, KCShip*> ships;
	QMap<int, KCFleet*> fleets;
	QMap<int, KCDock*> repairDocks;
	QMap<int, KCDock*> constructionDocks;

	bool hasCredentials();

	typedef void (KCClient::*processFunc)(const QVariant&);
	std::map<QString, processFunc> processFuncs;

signals:
	void credentialsGained();
	void receivedMasterShips();
	void receivedPlayerShips();
	void receivedPlayerFleets();
	void receivedPlayerRepairs();
	void receivedPlayerConstructions();
	void requestError(KCClient::ErrorCode error);

	void dockCompleted(KCDock *dock);
	void missionCompleted(KCFleet *fleet);

public slots:
	void setCredentials(QString server, QString apiToken);

	void requestMasterShips();
	void requestPlayerShips();
	void requestPlayerFleets();
	void requestPlayerRepairs();
	void requestPlayerConstructions();

protected slots:
	void onMasterShipsRequestFinished();
	void onPlayerShipsRequestFinished();
	void onPlayerFleetsRequestFinished();
	void onPlayerRepairsRequestFinished();
	void onPlayerConstructionsRequestFinished();

	void onDockCompleted();
	void onMissionCompleted();

protected:
	void _processMasterShipsData(const QVariant &data);
	void _processPlayerShipsData(const QVariant &data);
	void _processPlayerFleetsData(const QVariant &data);
	void _processPlayerRepairsData(const QVariant &data);
	void _processPlayerConstructionsData(const QVariant &data);

	QNetworkReply* call(QString endpoint, QUrlQuery params = QUrlQuery());
	QUrl urlForEndpoint(QString endpoint);
	QVariant dataFromRawResponse(QString text, ErrorCode *error = 0);

	QNetworkAccessManager *manager;
};

#endif // KCCLIENT_H
