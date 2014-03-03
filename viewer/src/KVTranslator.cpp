#include "KVTranslator.h"
#include <QMutex>
#include <QUrl>
#include <QStandardPaths>
#include <QDir>
#include <QEventLoop>
#include <QByteArray>
#include <QStack>
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
	if(cacheFile.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
		parseTranslationData(cacheFile.readAll());
		cacheFile.close();
	} else {
		qDebug() << "Couldn't read from translation cache";
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
		if(cacheFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			cacheFile.write(body);
			cacheFile.close();
		} else {
			qDebug() << "Couldn't write to cache file";
		}
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
	if(!isLoaded) {
		QEventLoop loop;
		loop.connect(this, SIGNAL(loadFinished()), SLOT(quit()));
		loop.connect(this, SIGNAL(loadFailed(QString)), SLOT(quit()));
		loop.exec();
	}

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

QByteArray KVTranslator::translateJson(QByteArray json) const {
	Reader r(json);
	QStack<JsonState> state;
	state.reserve(5);
	state.push(JsonState(End, 0));
	state.push(JsonState(Start, 0));

	QByteArray ret;
	ret.reserve(json.size()*2);
	for(int i = 0; i < json.size(); i++) {
		if(state.top().context != Key && state.top().context != String
		   && isspace(json.at(i))) continue;

		switch(state.top().context) {
		case Start:
			if(json.at(i) == '{')
				state.top() = JsonState(Object, i);
			continue;
		case End:
			qDebug() << "Unmatched '[' or '{' in JSON";
			break;
		case Object:
			switch(json.at(i)) {
			case '"':
				state.push(JsonState(Key, i));
				continue;
			case '}':
				state.top() = JsonState(AfterValue, i);
				continue;
			default:
				qDebug() << "Unexpected character" << json.at(i) << "in object";
				break;
			}
			break;
		case Array:
			switch(json.at(i)) {
			case '"':
				ret.append(r.readTo(i+1));
				state.push(JsonState(String, i));
				break;
			case '{':
				state.push(JsonState(Object, i));
				break;
			case '[':
				state.push(JsonState(Array, i));
				break;
			case ']':
				state.top() = JsonState(AfterValue, i);
				break;
			case ',':
				break;
			default:
				state.push(JsonState(NonString, i));
				break;
			}
			continue;
		case Key:
			switch(json.at(i)) {
			case '\\':
				i++;
				break;
			case '"':
				state.top() = JsonState(AfterKey, i);
				break;
			}
			continue;
		case AfterKey:
			if(json.at(i) == ':') {
				state.top() = JsonState(Value, i);
				continue;
			}
			qDebug() << "Character after key not ':'";
			break;
		case Value:
			switch(json.at(i)) {
			case '"':
				ret.append(r.readTo(i+1));
				state.top() = JsonState(String, i);
				continue;
			case '{':
				state.top() = JsonState(Object, i);
				continue;
			case '[':
				state.top() = JsonState(Array, i);
				continue;
			case ',':
				qDebug() << "Empty value";
				break;
			default:
				state.top() = JsonState(NonString, i);
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
				ret.append(translate(r.readTo(i)));
				state.top() = JsonState(AfterValue, i);
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
		case Invalid:
			qDebug() << "Invalid state!";
			break;
		}

		qDebug() << "Failed to parse json at index" << i;
		int ds = state.isEmpty() ? i-50 : state.top().start;
		qDebug() << "Context:" << json.mid(ds, i+50-ds);
		qDebug() << "Near:" << json.mid(i-5, 10);
		//qDebug() << QByteArray(i-ds-10, ' ').constData() << "^";
		qDebug() << "State:" << state << "\n";
		return json;
	}

	if(state.top().context == AfterValue) state.pop();
	if(state.top().context != End) {
		qDebug() << "Unexpected end of input reached while parsing JSON";
		return json;
	}

	ret.append(r.readAll());
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
