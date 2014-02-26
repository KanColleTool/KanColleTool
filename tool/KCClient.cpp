#include "KCClient.h"
#include <stdexcept>
#include <QDebug>
#include <QSettings>
#include <QEventLoop>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QFile>
#include "KCShip.h"
#include "KCShipMaster.h"
#include "KCFleet.h"

#define kClientUseCache 0

void KCClient::callPFunc(const QString &path, const QVariant &data)
{
	try {
		processFunc func = processFuncs.at(path);
		if(func) func(this, data);
	} catch (std::out_of_range e) {
		qDebug() << "Unknown path:" << path;
	}
}

KCClient::KCClient(QObject *parent) :
	QObject(parent)
{
	manager = new QNetworkAccessManager(this);
	logger = new KCLogger(this);

	QSettings settings;
	server = settings.value("server").toString();
	apiToken = settings.value("apiToken").toString();
}

KCClient::~KCClient()
{

}

bool KCClient::hasCredentials()
{
	return (!server.isEmpty() && !server.isEmpty());
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

void KCClient::safeMasterShips() {
	QNetworkRequest request(QString("http://kancolletool.github.io/kctool/mastership.json"));
	QNetworkReply *reply = manager->get(request);
	connect(reply, SIGNAL(finished()), SLOT(onRequestFinished()));
}

void KCClient::requestMasterShips() {
	QNetworkReply *reply = this->call("/api_get_master/ship");
	if(reply) connect(reply, SIGNAL(finished()), SLOT(onRequestFinished()));
}

void KCClient::requestPlayerShips() {
	QNetworkReply *reply = this->call("/api_get_member/ship");
	if(reply) connect(reply, SIGNAL(finished()), SLOT(onRequestFinished()));
}

void KCClient::requestPlayerFleets() {
	QNetworkReply *reply = this->call("/api_get_member/deck");
	if(reply) connect(reply, SIGNAL(finished()), SLOT(onRequestFinished()));
}

void KCClient::requestPlayerRepairs() {
	QNetworkReply *reply = this->call("/api_get_member/ndock");
	if(reply) connect(reply, SIGNAL(finished()), SLOT(onRequestFinished()));
}

void KCClient::requestPlayerConstructions() {
	QNetworkReply *reply = this->call("/api_get_member/kdock");
	if(reply) connect(reply, SIGNAL(finished()), SLOT(onRequestFinished()));
}

void KCClient::onDockCompleted() {
	emit dockCompleted(qobject_cast<KCDock*>(QObject::sender()));
}

void KCClient::onMissionCompleted() {
	emit missionCompleted(qobject_cast<KCFleet*>(QObject::sender()));
}

QNetworkReply* KCClient::call(QString endpoint, QUrlQuery params) {
#if kClientUseCache
	QFile file(QString("cache%1.json").arg(endpoint));
	if(file.open(QIODevice::ReadOnly)) {
		qDebug() << "Loading Fixture:" << endpoint;
		QVariant response = this->dataFromRawResponse(file.readAll());

		callPFunc(endpoint, response);

		return 0;
	}
#endif
	QNetworkRequest request(this->urlForEndpoint(endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setRawHeader("Referer", QString("http://%1/kcs/mainD2.swf").arg(server).toUtf8());
	request.setRawHeader("User-Agent", QString("Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36").toUtf8());

	params.addQueryItem("api_verno", "1");
	params.addQueryItem("api_token", apiToken);
	QString query = params.toString(QUrl::FullyEncoded);

	return manager->post(request, query.toUtf8());
}

void KCClient::onRequestFinished() {
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
	if(reply->error() == QNetworkReply::NoError) {
		ErrorCode error;
		QVariant data = this->dataFromRawResponse(reply->readAll(), &error);
		if(data.isValid()) callPFunc(reply->url().path(), data);
		else { qDebug() << error; emit requestError(error); }
	} else if(reply->error() == QNetworkReply::UnknownNetworkError) {
		qWarning() << "Connection Failed:" << reply->errorString();
	}
}

QUrl KCClient::urlForEndpoint(QString endpoint) {
	return QUrl(QString("http://%1/kcsapi%2").arg(server, endpoint));
}

QVariant KCClient::dataFromRawResponse(QString text, ErrorCode *error) {
	if(text.startsWith("svdata="))
		text = text.mid(7);

	QJsonParseError jsonErr;
	QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &jsonErr);
	if(jsonErr.error != QJsonParseError::NoError) {
		if(error) *error = JsonError;
		return QVariant();
	}

	QMap<QString, QVariant> data = doc.toVariant().toMap();
	if(data.value("api_result").toInt() != NoError) {
		if(error) *error = (ErrorCode)data.value("api_result").toInt();
		return QVariant();
	}

	if(error) *error = NoError;
	return data.value("api_data");
}
