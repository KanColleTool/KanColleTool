#include "KCClient.h"
#include <QDebug>
#include <QSettings>
#include <QUrlQuery>
#include <QJsonDocument>

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
	QVariant data = this->dataFromReplyData(reply->readAll(), &error);
	if(data.isValid())
		emit receivedMasterShips(data.toList());
	else
		emit requestError(error);
}

void KCClient::onPlayerShipsRequestFinished()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
	ErrorCode error;
	QVariant data = this->dataFromReplyData(reply->readAll(), &error);
	if(data.isValid())
		emit receivedPlayerShips(data.toList());
	else
		emit requestError(error);
}

QNetworkReply* KCClient::call(QString endpoint, QUrlQuery params)
{
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

QVariant KCClient::dataFromReplyData(QString text, ErrorCode *error)
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
