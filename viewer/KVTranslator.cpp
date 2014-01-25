#include "KVTranslator.h"
#include <QMutex>
#include <QUrl>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
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

void KVTranslator::loadTranslation(QString language)
{
	QNetworkReply *reply = manager.get(QNetworkRequest(QString("http://api.comeonandsl.am/translation/%1/").arg(language)));
	connect(reply, SIGNAL(finished()), this, SLOT(translationRequestFinished()));
}

QString KVTranslator::translate(const QString &line) const
{
	QString realLine = unescape(line);
	QByteArray utf8 = realLine.toUtf8();
	uint32_t crc = crc32(0, utf8.constData(), utf8.size());
	
	QString key = QString::number(crc);
	QVariant value = translation.value(key);
	if(value.isValid())
	{
		qDebug() << "TL:" << realLine << "->" << value.toString();
		return value.toString();
	}
	else
	{
		qDebug() << "No TL:" << realLine;
		return line;
	}
}

QString KVTranslator::translateJson(const QString &json) const
{
	bool hasPrefix = json.startsWith("svdata=");
	QJsonDocument doc = QJsonDocument::fromJson(json.mid(hasPrefix ? 7 : 0).toUtf8());
	QJsonValue val = this->_walk(QJsonValue(doc.object()));
	//qDebug() << val;
	QString str = QString::fromUtf8(QJsonDocument(val.toObject()).toJson(QJsonDocument::Compact));
	return (hasPrefix ? "svdata=" + str : str);
}

QJsonValue KVTranslator::_walk(QJsonValue value) const
{
	switch(value.type())
	{
		case QJsonValue::Object:
		{
			QJsonObject obj = value.toObject();
			for(QJsonObject::iterator it = obj.begin(); it != obj.end(); it++)
				*it = this->_walk(*it);
			return obj;
		}
		case QJsonValue::Array:
		{
			QJsonArray arr = value.toArray();
			for(QJsonArray::iterator it = arr.begin(); it != arr.end(); it++)
				*it = this->_walk(*it);
			return arr;
		}
		case QJsonValue::String:
			return this->translate(value.toString());
		default:
			return value;
	}
}

void KVTranslator::translationRequestFinished()
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
	int success = (int) root.value("success").toDouble();
	if(success != 1)
	{
		emit loadFailed(QString("API Error %1").arg(success));
		return;
	}
	
	// Parse the translation data
	translation = root.value("translation").toObject().toVariantMap();
	
	emit loadFinished();
}
