#include "KCTranslator.h"
#include <QMutex>
#include <QUrl>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "KCUtil.h"
#include "crc32.h"

KCTranslator* KCTranslator::m_instance = 0;

// -- Singleton Instance
KCTranslator* KCTranslator::instance()
{
	static QMutex mutex;
	if(!m_instance)
	{
		mutex.lock();
		if(!m_instance)
			m_instance = new KCTranslator;
		mutex.unlock();
	}
	
	return m_instance;
}
// --



KCTranslator::KCTranslator(QObject *parent):
	QObject(parent)
{
	
}

KCTranslator::~KCTranslator()
{
	
}

QString KCTranslator::translate(const QString &line) const
{
	QString realLine = unescape(line);
	QByteArray utf8 = realLine.toUtf8();
	uint32_t crc = crc32(0, utf8.constData(), utf8.size());
	
	QString key = QString::number(crc);
	QVariant value = translation.value(key);
	if(value.isValid())
	{
		//qDebug() << "TL:" << realLine << "->" << value.toString();
		return value.toString();
	}
	else
	{
		//qDebug() << "No TL:" << realLine;
		return line;
	}
}

void KCTranslator::loadTranslation(QString language)
{
	QNetworkReply *reply = manager.get(QNetworkRequest(QString("http://api.comeonandsl.am/translation/%1/").arg(language)));
	connect(reply, SIGNAL(finished()), this, SLOT(translationRequestFinished()));
}

void KCTranslator::translationRequestFinished()
{
	// Read the response body
	QNetworkReply *reply(qobject_cast<QNetworkReply*>(QObject::sender()));
	if(reply->error() != QNetworkReply::NoError)
	{
		emit loadFailed(QString("Network Error: %1").arg(reply->errorString()));
		return;
	}
	QByteArray body(reply->readAll());
	
	// Parse the JSON
	QJsonParseError error;
	QJsonDocument doc(QJsonDocument::fromJson(body, &error));
	if(error.error != QJsonParseError::NoError)
	{
		emit loadFailed(QString("JSON Error: %1").arg(error.errorString()));
		return;
	}
	QJsonObject root(doc.object());
	
	// Check the response
	int success = root.value("success").toInt();
	if(success != 1)
	{
		emit loadFailed(QString("API Error %1").arg(success));
		return;
	}
	
	// Parse the translation data
	translation = root.value("translation").toObject().toVariantMap();
	
	emit loadFinished();
}
