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
	typedef std::function<void(KCClient *client, const QVariant&)> processFunc;

	void callPFunc(const QString &path, const QVariant &data);

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

signals:
	void focusRequested();

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

	void safeMasterShips();
	void requestMasterShips();
	void requestPlayerShips();
	void requestPlayerFleets();
	void requestPlayerRepairs();
	void requestPlayerConstructions();

protected slots:
	void onRequestFinished();

	void onDockCompleted();
	void onMissionCompleted();

protected:
	QNetworkReply* call(QString endpoint, QUrlQuery params = QUrlQuery());
	QUrl urlForEndpoint(QString endpoint);
	QVariant dataFromRawResponse(QString text, ErrorCode *error = 0);

	QNetworkAccessManager *manager;

private:
	static const std::map<QString, processFunc> processFuncs;
};

#endif // KCCLIENT_H
