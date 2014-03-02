#ifndef KCTRANSLATOR_H
#define KCTRANSLATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QVariant>
#include <QString>

class KCTranslator : public QObject
{
	Q_OBJECT

public:
	static KCTranslator* instance();

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
	static KCTranslator *m_instance;

	KCTranslator(QObject *parent = 0);
	KCTranslator(const KCTranslator&);
	virtual ~KCTranslator();

	KCTranslator& operator=(const KCTranslator&);
};

#define kcTranslate(_line) (KCTranslator::instance()->translate(_line))

#endif
