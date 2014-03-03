#include "KVTranslator.h"
#include <QMutex>
#include <QUrl>
#include <QStandardPaths>
#include <QDir>
#include <QByteArray>
#include <QStack>
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
	QObject(parent), isLoaded(false)
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

	if(parseTranslationData(body)) {
		qDebug() << "Network translation loaded!";
		cacheFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
		cacheFile.write(body);
		cacheFile.close();
	}
}

bool KVTranslator::parseTranslationData(const QByteArray &data)
{
	// Parse the JSON
	QJsonParseError error;
	QJsonDocument doc(QJsonDocument::fromJson(data, &error));
	if(error.error != QJsonParseError::NoError)
	{
		emit loadFailed(QString("JSON Error: %1").arg(error.errorString()));
		return false;
	}
	QJsonObject root(doc.object());

	// Check the response
	int success = (int) root.value("success").toDouble();
	if(success != 1)
	{
		emit loadFailed(QString("API Error %1").arg(success));
		return false;
	}

	// Parse the translation data
	translation = root.value("translation").toObject().toVariantMap();

	isLoaded = true;
	emit loadFinished();
	return true;
}

QString KVTranslator::translate(const QString &line) const {
	QString realLine = unescape(line);
	QByteArray utf8 = realLine.toUtf8();
	quint32 crc = crc32(0, utf8.constData(), utf8.size());

	QString key = QString::number(crc);
	QVariant value = translation.value(key);
	if(value.isValid()) {
		//qDebug() << "TL:" << realLine << "->" << value.toString();
		return jsonEscape(value.toString());
	} else {
		//qDebug() << "No TL:" << realLine;
		return line;
	}
}

QString KVTranslator::fixTime(const QString &time) const
{
	QDateTime realTime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
	if(!realTime.isValid()) return time;
	realTime.addSecs(-32400);
	realTime = realTime.toLocalTime();
	//qDebug() << "fix time" << time << "to" << realTime.toString("yyyy-MM-dd hh:mm:ss");
	return realTime.toString("yyyy-MM-dd hh:mm:ss");
}

inline void copyData(QByteArray &target, const QByteArray &data, int &s, int e) {
	target.append(data.mid(s, e-s+1));
	s = e+1;
}

QByteArray KVTranslator::translateJson(const QByteArray &json) const {
	QStack<jsonState> state;
	state.reserve(5);
	state.push(Start);
	int s = 0;

	QByteArray ret = "";
	ret.reserve(json.size());
	for(int i = 0; i < json.size(); i++) {
		if(isspace(json.at(i))) continue;

		switch(state.top()) {
		case Start:
			if(json.at(i) == '{') {
				copyData(ret, json, s, i);
				state.push(Object);
			}
			continue;
		case Object:
			switch(json.at(i)) {
			case '"':
				copyData(ret, json, s, i);
				state.push(Key);
				continue;
			case '}':
				state.pop();
				continue;
			default:
				qDebug() << "Unexpected character" << json.at(i) << "in object";
				break;
			}
			break;
		case Array:
			switch(json.at(i)) {
			case '"':
				copyData(ret, json, s, i);
				state.push(String);
				break;
			case '{':
				state.push(Object);
				break;
			case '[':
				state.push(Array);
				break;
			case ']':
				state.top() = AfterValue;
				break;
			case ',':
				break;
			default:
				state.push(NonString);
				break;
			}
			continue;
		case Key:
			switch(json.at(i)) {
			case '\\':
				i++;
				break;
			case '"':
				state.top() = AfterKey;
				break;
			}
			continue;
		case AfterKey:
			if(json.at(i) == ':') {
				state.top() = Value;
				continue;
			}
			qDebug() << "Character after key not ':'";
			break;
		case Value:
			switch(json.at(i)) {
			case '"':
				copyData(ret, json, s, i);
				state.top() = String;
				continue;
			case '{':
				state.top() = Object;
				continue;
			case '[':
				state.top() = Array;
				continue;
			case ',':
				qDebug() << "Empty value";
				break;
			default:
				state.top() = NonString;
				continue;
			}
			break;
		case NonString:
			switch(json.at(i)) {
			case ']':
			case '}':
				i--;
			case ',':
				state.pop();
				break;
			}
			continue;
		case String:
			switch(json.at(i)) {
			case '\\':
				i++;
				break;
			case '"':
				ret.append(translate(json.mid(s, i-s)));
				s = i;
				state.top() = AfterValue;
				break;
			}
			continue;
		case AfterValue:
			switch(json.at(i)) {
			case ']':
			case '}':
				i--;
			case ',':
				state.pop();
				continue;
			}
			qDebug() << "No ',', ']', or '}' after string";
			break;
		}

		qDebug() << "Failed to parse json at index" << i;
		qDebug() << "Context:" << json.mid(i-50, 100);
		qDebug() << "                                                            ^";
		qDebug() << "State:" << state << "\n";
		return json;
	}

	ret.append(json.mid(s));
	return ret;
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
