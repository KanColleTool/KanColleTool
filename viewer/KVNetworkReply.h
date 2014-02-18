#ifndef KVNETWORKREPLY_H
#define KVNETWORKREPLY_H

#include <QNetworkReply>

class KVNetworkReply : public QNetworkReply
{
	Q_OBJECT

public:
	KVNetworkReply(QObject *parent, QNetworkReply *toCopy);
	~KVNetworkReply();

	void copyAttribute(QNetworkRequest::Attribute attr);

	qint64 bytesAvailable() const;
	bool isFinished() const;
	bool isRunning() const;

	void ignoreSslErrors(const QList<QSslError> &errors);
	QSslConfiguration sslConfiguration() const;
	void setSslConfiguration(const QSslConfiguration &config);
	QNetworkAccessManager* manager() const;
	bool event(QEvent *e);
	void close();

	void abort();
	void ignoreSslErrors();

	bool isSequential() const;

public slots:
	void translateRequest();

protected:
	void setFinished(bool finished);
	qint64 readData(char *data, qint64 maxSize);

private:
	struct KVNetworkReplyPrivate *d;
};

#endif // KVNETWORKREPLY_H
