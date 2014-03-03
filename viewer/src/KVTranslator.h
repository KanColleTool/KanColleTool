#ifndef KVTRANSLATOR_H
#define KVTRANSLATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QVariant>
#include <QString>
#include <QFile>
#include <QJsonValue>

/*
 * I had to copypaste this into the tool as "KCTranslator", because sharing the
 * same source file between two projects seems to break everything for some
 * reason.
 *
 * Please keep the two classes synchronized!
 */

class KVTranslator : public QObject
{
	Q_OBJECT

public:
	static KVTranslator* instance();
	bool loaded();

public slots:
	void loadTranslation(QString language = "en");

	QString translate(const QString &line) const;
	QString fixTime(const QString &time) const;
	QByteArray translateJson(QByteArray json) const;

protected:
	bool parseTranslationData(const QByteArray &data);
	QJsonValue _walk(QJsonValue value, QString key="") const;
	static QString jsonEscape(const QString &str);

signals:
	void loadFinished();
	void loadFailed(QString error);

private slots:
	void translationRequestFinished();

private:
	enum JsonContext {
		Start, End,
		Object, Array,
		Key, AfterKey,
		Value, NonString, String, AfterValue,
		Invalid
	};

	struct JsonState {
		JsonContext context;
		int start, arri;
		JsonState();
		JsonState(JsonContext c, int s, int ai=-1);
		operator QString() const;
	};

	struct Reader {
		int i;
		const QByteArray &data;
		Reader(const QByteArray &json);

		const QByteArray readTo(int e);
		const QByteArray readAll();
	};

	bool isLoaded;
	QFile cacheFile;
	QNetworkAccessManager manager;
	QVariantMap translation;

private:
	// Singleton stuff
	static KVTranslator *m_instance;

	KVTranslator(QObject *parent = 0);
	KVTranslator(const KVTranslator&);
	virtual ~KVTranslator();

	KVTranslator& operator=(const KVTranslator&);
};

#endif
