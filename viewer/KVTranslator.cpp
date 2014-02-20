#include "KVTranslator.h"
#include <QMutex>
#include <QUrl>
#include <QStandardPaths>
#include <QDir>
#include <QByteArray>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDateTime>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "KVUtil.h"

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
	QObject(parent), isLoaded(false), JST(32400)
{
	cacheFile.setFileName(QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)).filePath("translation.json"));
}

KVTranslator::~KVTranslator()
{

}

bool KVTranslator::loaded()
{
	return isLoaded;
}

void KVTranslator::loadTranslation(QString language)
{
	if(cacheFile.exists()) {
		cacheFile.open(QIODevice::ReadOnly | QIODevice::Unbuffered);
		parseTranslationData(cacheFile.readAll());
		cacheFile.close();
	}

	QNetworkReply *reply = manager.get(QNetworkRequest(QString("http://api.comeonandsl.am/translation/%1/").arg(language)));
	connect(reply, SIGNAL(finished()), this, SLOT(translationRequestFinished()));
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

	parseTranslationData(body);
	qDebug() << "Network translation loaded!";

	cacheFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
	cacheFile.write(body);
	cacheFile.close();
}

void KVTranslator::parseTranslationData(const QByteArray &data)
{
	// Parse the JSON
	QJsonParseError error;
	QJsonDocument doc(QJsonDocument::fromJson(data, &error));
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

	isLoaded = true;
	emit loadFinished();
}

QString KVTranslator::translate(const QString &line) const
{
	if(!enabled) return line;

	QString realLine = unescape(line);
	QByteArray utf8 = realLine.toUtf8();
	quint32 crc = crc32(0, utf8.constData(), utf8.size());

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

QString KVTranslator::fixTime(const QString &time) const
{
	QDateTime realTime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
	if(!realTime.isValid()) return time;
	realTime.setTimeZone(JST);
	realTime = realTime.toLocalTime();
	//qDebug() << "fix time" << time << "to" << realTime.toString("yyyy-MM-dd hh:mm:ss");
	return realTime.toString("yyyy-MM-dd hh:mm:ss");
}

QString KVTranslator::translateJson(const QString &json) const
{
	if(!enabled) return json;

	// Block until translation is loaded
	if(!isLoaded) {
		QEventLoop loop;
		loop.connect(this, SIGNAL(translationLoaded()), SLOT(quit()));
		loop.connect(this, SIGNAL(loadFailed()), SLOT(quit()));
		loop.exec();
	}

	bool hasPrefix = json.startsWith("svdata=");
	QJsonDocument doc = QJsonDocument::fromJson(json.mid(hasPrefix ? 7 : 0).toUtf8());
	QJsonValue val = this->_walk(QJsonValue(doc.object()));
	//qDebug() << val;
	doc = QJsonDocument(val.toObject());
#if QT_VERSION >= 0x050100
	QString str = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
#else
	QString str = QString::fromUtf8(doc.toJson());
#endif
	return (hasPrefix ? "svdata=" + str : str);
}

QJsonValue KVTranslator::_walk(QJsonValue value, QString key) const
{
	switch(value.type())
	{
		case QJsonValue::Object:
		{
			QJsonObject obj = value.toObject();
			for(QJsonObject::iterator it = obj.begin(); it != obj.end(); it++)
				*it = this->_walk(*it, it.key());
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
			if(key == "api_complete_time_str")
				return this->fixTime(value.toString());
			return this->translate(value.toString());
		default:
			return value;
	}
}
