#include "KCClient.h"
#include <QDebug>
#include <QSettings>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QFile>
#include "KCShip.h"
#include "KCShipMaster.h"

#define kClientUseCache 1

KCClient::KCClient(QObject *parent) :
	QObject(parent)
{
	manager = new QNetworkAccessManager(this);
	
	QSettings settings;
	this->server = settings.value("server").toString();
	this->apiToken = settings.value("apiToken").toString();
}

KCClient::~KCClient()
{
	
}

bool KCClient::hasCredentials()
{
	return (!this->server.isEmpty() && !this->server.isEmpty());
}

void KCClient::setCredentials(QString server, QString apiToken)
{
	this->server = server;
	this->apiToken = apiToken;
	
	if(this->hasCredentials())
	{
		QSettings settings;
		settings.setValue("server", server);
		settings.setValue("apiToken", apiToken);
		settings.sync();
		
		emit credentialsGained();
	}
}

void KCClient::requestMasterShips()
{
	QNetworkReply *reply = this->call("/api_get_master/ship");
	connect(reply, SIGNAL(finished()), this, SLOT(onMasterShipsRequestFinished()));
}

void KCClient::requestPlayerShips()
{
	QNetworkReply *reply = this->call("/api_get_member/ship");
	connect(reply, SIGNAL(finished()), this, SLOT(onPlayerShipsRequestFinished()));
}

void KCClient::onMasterShipsRequestFinished()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
	ErrorCode error;
	QVariant data = this->dataFromRawResponse(reply->readAll(), &error);
	if(data.isValid())
	{
		this->processMasterShipsData(data);
		emit receivedMasterShips();
	}
	else
		emit requestError(error);
}

void KCClient::onPlayerShipsRequestFinished()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
	ErrorCode error;
	QVariant data = this->dataFromRawResponse(reply->readAll(), &error);
	if(data.isValid())
	{
		this->processPlayerShipsData(data);
		emit receivedPlayerShips();
	}
	else
		emit requestError(error);
}

void KCClient::processMasterShipsData(QVariant data)
{
	QList<QVariant> dataList = data.toList();
	foreach(QVariant item, dataList)
	{
		QVariantMap itemMap = item.toMap();
		KCShipMaster *ship = masterShips.value(itemMap.value("api_id").toInt());
		
		if(!ship)
			masterShips.insert(itemMap.value("api_id").toInt(), new KCShipMaster(itemMap));
		else
			ship->loadFrom(itemMap);
	}
}

void KCClient::processPlayerShipsData(QVariant data)
{
	QList<QVariant> dataList = data.toList();
	foreach(QVariant item, dataList)
	{
		QVariantMap itemMap = item.toMap();
		KCShip *ship = ships.value(itemMap.value("api_id").toInt());
		
		if(!ship)
			ships.insert(itemMap.value("api_id").toInt(), new KCShip(itemMap));
		else
			ship->loadFrom(itemMap);
	}
}

QNetworkReply* KCClient::call(QString endpoint, QUrlQuery params)
{
#if kClientUseCache
	qDebug() << endpoint;
	if(endpoint == "/api_get_master/ship")
	{
		qDebug() << "Loading Stored Master Ships";
		QFile file("cache/api_get_master/ship.json");
		if(file.open(QIODevice::ReadOnly))
		{
			this->processMasterShipsData(this->dataFromRawResponse(file.readAll()));
			return 0;
		}
		else qWarning() << "--> Failed!" << file.errorString();
	}
	else if(endpoint == "/api_get_member/ship")
	{
		qDebug() << "Loading Stored Player Ships";
		QFile file("cache/api_get_member/ship.json");
		if(file.open(QIODevice::ReadOnly))
		{
			this->processPlayerShipsData(this->dataFromRawResponse(file.readAll()));
			return 0;
		}
		else qWarning() << "--> Failed!" << file.errorString();
	}
#endif
	QNetworkRequest request(this->urlForEndpoint(endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setRawHeader("Referer", QString("http://%1/kcs/mainD2.swf").arg(this->server).toUtf8());
	
	params.addQueryItem("api_verno", "1");
	params.addQueryItem("api_token", this->apiToken);
	QString query = params.toString(QUrl::FullyEncoded);
	
	return this->manager->post(request, query.toUtf8());
}

QUrl KCClient::urlForEndpoint(QString endpoint)
{
	return QUrl(QString("http://%1/kcsapi%2").arg(server, endpoint));
}

QVariant KCClient::dataFromRawResponse(QString text, ErrorCode *error)
{
	if(text.startsWith("svdata="))
		text = text.mid(7);
	
	QJsonParseError jsonErr;
	QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &jsonErr);
	if(jsonErr.error != QJsonParseError::NoError)
	{
		if(error) *error = JsonError;
		return QVariant();
	}
	
	QMap<QString, QVariant> data = doc.toVariant().toMap();
	if(data.value("api_result").toInt() != 1)
	{
		if(error) *error = (ErrorCode)data.value("api_result").toInt();
		return QVariant();
	}
	
	return data.value("api_data");
}
