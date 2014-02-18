#ifndef KVNETWORKREPLY_H
#define KVNETWORKREPLY_H

#include <QNetworkReply>

class KVNetworkReply : public QNetworkReply
{
	Q_OBJECT

public:
	KVNetworkReply(QObject *parent, QNetworkReply *toCopy);
	~KVNetworkReply();

	QVariant attribute(QNetworkRequest::Attribute code) const;
	QNetworkReply::NetworkError error() const;
	bool hasRawHeader(const QByteArray &headerName) const;
	QVariant header(QNetworkRequest::KnownHeaders header) const;
	void ignoreSslErrors(const QList<QSslError> &errors);
	bool isFinished() const;
	bool isRunning() const;
	QNetworkAccessManager* manager() const;
	QNetworkAccessManager::Operation operation() const;
	QByteArray rawHeader(const QByteArray &headerName) const;
	QList<QByteArray> rawHeaderList() const;
	const QList<QNetworkReply::RawHeaderPair>& rawHeaderPairs() const;
	qint64 readBufferSize() const;
	QNetworkRequest request() const;
	void setReadBufferSize(qint64 size);
	void setSslConfiguration(const QSslConfiguration &config);
	QSslConfiguration sslConfiguration() const;
	QUrl url() const;
	bool event(QEvent *e);
	void close();

	void abort();
	void ignoreSslErrors();

	qint64 bytesAvailable() const;
	bool isSequential() const;

	qint64 peek(char *data, qint64 maxSize);
	QByteArray peek(qint64 maxSize);

public slots:
	void translateRequest();

protected:
	qint64 readData(char *data, qint64 maxSize);

private:
	struct KVNetworkReplyPrivate *d;
};

#endif // KVNETWORKREPLY_H
