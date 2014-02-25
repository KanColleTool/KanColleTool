#ifndef KVNETWORKREPLY_H
#define KVNETWORKREPLY_H

#include <QNetworkReply>

class QSslConfiguration;

class KVNetworkAccessManager;
class KVNetworkReply : public QNetworkReply
{
	Q_OBJECT

public:
	KVNetworkReply(QObject *parent, QNetworkReply *toCopy, KVNetworkAccessManager *mgr);
	~KVNetworkReply();

	void copyAttribute(QNetworkRequest::Attribute attr);

	qint64 bytesAvailable() const;

	void ignoreSslErrors(const QList<QSslError> &errors);
	QSslConfiguration sslConfiguration() const;
	void setSslConfiguration(const QSslConfiguration &config);
	QNetworkAccessManager* manager() const;
	bool event(QEvent *e);

	void abort();
	void ignoreSslErrors();

	bool isSequential() const;

protected slots:
	void handleResponse();

protected:
	qint64 readData(char *data, qint64 maxSize);

private:
	struct KVNetworkReplyPrivate *d;
};

#endif // KVNETWORKREPLY_H
