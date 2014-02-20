#ifndef KVTRANSLATOR_H
#define KVTRANSLATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QVariant>
#include <QString>
#include <QJsonValue>
#include <QTimeZone>

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
	bool enabled;

public slots:
	void loadTranslation(QString language = "en");

	QString translate(const QString &line) const;
	QString fixTime(const QString &time) const;
	QString translateJson(const QString &json) const;

protected:
	QJsonValue _walk(QJsonValue value, QString key="") const;

signals:
	void loadFinished();
	void loadFailed(QString error);

private slots:
	void translationRequestFinished();

private:
	bool isLoaded;
	QNetworkAccessManager manager;
	QVariantMap translation;
	QTimeZone JST;

private:
	// Singleton stuff
	static KVTranslator *m_instance;

	KVTranslator(QObject *parent = 0);
	KVTranslator(const KVTranslator&);
	virtual ~KVTranslator();

	KVTranslator& operator=(const KVTranslator&);
};

#endif
