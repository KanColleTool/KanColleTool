#include "KVNetworkReply.h"

#include <QNetworkAccessManager>
#include <QBuffer>
#include <QTimer>

#include "KVTranslator.h"

struct KVNetworkReplyPrivate
{
	QNetworkReply *copied;

	QByteArray content;
	qint64 offset;
	bool finished;
};

KVNetworkReply::KVNetworkReply(QObject *parent, QNetworkReply *toCopy)
	: QNetworkReply(parent)
{
	d = new KVNetworkReplyPrivate;
	d->copied = toCopy;

	// Translate reply when it's complete
	connect(d->copied, SIGNAL(finished()), this, SLOT(translateRequest()));

	connect(d->copied, SIGNAL(encrypted()), this, SIGNAL(encrypted()));
}

KVNetworkReply::~KVNetworkReply()
{
	delete d;
}

void KVNetworkReply::translateRequest()
{
	if(d->finished) return;

	QString data = d->copied->readAll();

	KVTranslator *translator = KVTranslator::instance();
	data = translator->translateJson(data);
	d->content = data.toUtf8();
	d->offset = 0;

	open(ReadOnly | Unbuffered);
	qDebug() << "translated:" << d->content.constData();

	d->finished = true;

	emit finished();
	emit readChannelFinished();
	emit readyRead();
}

// Whether this reply has finished loading
bool KVNetworkReply::isFinished() const { return d->finished; }
bool KVNetworkReply::isRunning() const { return !d->finished; }

qint64 KVNetworkReply::bytesAvailable() const
{
	return d->content.size() - d->offset;
}

qint64 KVNetworkReply::peek(char *data, qint64 maxSize)
{
	if (d->offset >= d->content.size())
		return -1;

	qint64 numBytes = qMin(maxSize, d->content.size() - d->offset);
	memcpy(data, d->content.constData() + d->offset, numBytes);

	return numBytes;
}

QByteArray KVNetworkReply::peek(qint64 maxSize)
{
	char *data = new char[maxSize];
	qint64 size = peek(data, maxSize);

	return QByteArray(data, size);
}

qint64 KVNetworkReply::readData(char *data, qint64 maxSize)
{
	if (d->offset >= d->content.size())
		return -1;

	qint64 numBytes = qMin(maxSize, d->content.size() - d->offset);
	memcpy(data, d->content.constData() + d->offset, numBytes);
	d->offset += numBytes;

	return numBytes;
}

/*
 * Pass all these through to the underlying 'copied' QNetworkRequest because
 * There isn't a copy constructor. I now understand why everything in the
 * standard libraries has a copy constructor...
 */
QVariant KVNetworkReply::attribute(QNetworkRequest::Attribute code) const
{ return d->copied->attribute(code); }
QNetworkReply::NetworkError KVNetworkReply::error() const
{ return d->copied->error(); }
bool KVNetworkReply::hasRawHeader(const QByteArray &headerName) const
{ return d->copied->hasRawHeader(headerName); }
QVariant KVNetworkReply::header(QNetworkRequest::KnownHeaders header) const
{ return d->copied->header(header); }
void KVNetworkReply::ignoreSslErrors(const QList<QSslError> &errors)
{ d->copied->ignoreSslErrors(errors); }
QNetworkAccessManager* KVNetworkReply::manager() const
{ return d->copied->manager(); }
QNetworkAccessManager::Operation KVNetworkReply::operation() const
{ return d->copied->operation(); }
QByteArray KVNetworkReply::rawHeader(const QByteArray &headerName) const
{ return d->copied->rawHeader(headerName); }
QList<QByteArray> KVNetworkReply::rawHeaderList() const
{ return d->copied->rawHeaderList(); }
const QList<QNetworkReply::RawHeaderPair>& KVNetworkReply::rawHeaderPairs() const
{ return d->copied->rawHeaderPairs(); }
qint64 KVNetworkReply::readBufferSize() const
{ return d->copied->readBufferSize(); }
QNetworkRequest KVNetworkReply::request() const
{ return d->copied->request(); }
void KVNetworkReply::setReadBufferSize(qint64 size)
{ d->copied->setReadBufferSize(size); }
void KVNetworkReply::setSslConfiguration(const QSslConfiguration &config)
{ d->copied->setSslConfiguration(config); }
QSslConfiguration KVNetworkReply::sslConfiguration() const
{ return d->copied->sslConfiguration(); }
QUrl KVNetworkReply::url() const
{ return d->copied->url(); }
bool KVNetworkReply::event(QEvent *e)
{ return d->copied->event(e); }
void KVNetworkReply::close()
{ d->copied->close(); }

void KVNetworkReply::abort()
{ d->copied->abort(); }
void KVNetworkReply::ignoreSslErrors()
{ d->copied->ignoreSslErrors(); }
bool KVNetworkReply::isSequential() const
{	return true; }
