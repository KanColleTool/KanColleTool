#include "KVTranslator.h"
#include <QMutex>
#include <QUrl>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "KVUtil.h"
#include "crc32.h"

KVTranslator* KVTranslator::m_instance = 0;

// -- Singleton Instance
KVTranslator* KVTranslator::instance()
{
	static QMutex mutex;
	if(!m_instance)
	{
		mutex.lock();
		if(!m_instance)
			m_instance = new KVTranslator;
		mutex.unlock();
	}
	
	return m_instance;
}
// --



KVTranslator::KVTranslator(QObject *parent):
	QObject(parent)
{
	
}

KVTranslator::~KVTranslator()
{
	
}

QString KVTranslator::translate(const QString &line) const
{
	QByteArray utf8 = unescape(line).toUtf8();
	uint32_t crc = crc32(0, utf8.constData(), utf8.size());
	
	QString key = QString::number(crc);
	QVariant value = translation.value(key);
	return (value.isValid() ? value.toString() : line);
}

void KVTranslator::loadTranslation(QString language)
{
	QNetworkReply *reply = manager.get(QNetworkRequest(QString("http://api.comeonandsl.am/translation/%1/").arg(language)));
	connect(reply, SIGNAL(finished()), this, SLOT(translationRequestFinished()));
}

void KVTranslator::translationRequestFinished()
{
	// Read the response body
	QNetworkReply *reply(qobject_cast<QNetworkReply*>(QObject::sender()));
	if(reply->error() != QNetworkReply::NoError)
	{
		qWarning() << "Network Error:" << reply->errorString();
		emit loadingFailed();
		return;
	}
	QByteArray body(reply->readAll());
	
	// Parse the JSON
	QJsonParseError error;
	QJsonDocument doc(QJsonDocument::fromJson(body, &error));
	if(error.error != QJsonParseError::NoError)
	{
		qWarning() << "JSON Error:" << error.errorString();
		emit loadingFailed();
		return;
	}
	QJsonObject root(doc.object());
	
	// Check the response
	int success = root.value("success").toInt();
	if(success != 1)
	{
		qWarning() << "API Error:" << success;
		emit loadingFailed();
		return;
	}
	
	// Parse the translation data
	translation = root.value("translation").toObject().toVariantMap();
	
	qDebug() << this->translate("\\u90A3\\u73C2");
}
