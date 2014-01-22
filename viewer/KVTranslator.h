#ifndef KVTRANSLATOR_H
#define KVTRANSLATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QVariant>
#include <QString>

class KVTranslator : public QObject
{
	Q_OBJECT
	
public:
	static KVTranslator* instance();
	
public slots:
	QString translate(const QString &line) const;
	
	void loadTranslation(QString language = "en");
	
signals:
	void loadFinished();
	void loadFailed(QString error);
	
private slots:
	void translationRequestFinished();
	
private:
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
